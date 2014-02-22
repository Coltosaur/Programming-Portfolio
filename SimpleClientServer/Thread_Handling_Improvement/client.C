/* 
    File: client.C

	Author: Colt Campbell
		CSCE 313 - Section 504
    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2013/01/31

    client main program for MP3 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <cstring>
#include <iostream>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/time.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <vector>

#include "reqchannel.H"
#include "semaphore.H"
#include "boundedbuffer.h"

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

BoundedBuffer* request_buffer;
BoundedBuffer* response_Joe_stats;
BoundedBuffer* response_Jane_stats;
BoundedBuffer* response_John_stats;

struct timeval t0, t1; 
Semaphore done_stat_threads = Semaphore(-2);

int request_num;
int buff_size;
int workers_amount;

int joe_sent_count = 0;
int jane_sent_count = 0;
int john_sent_count = 0;

vector<int> joe_stats = vector<int>(10);
vector<int> jane_stats = vector<int>(10);
vector<int> john_stats = vector<int>(10);

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* HELPER FUNCTIONS */
/*--------------------------------------------------------------------------*/

void print_histogram()
{
	string person_name = " ";
	//vector<int> data;
	cout << "-----------------------------------------\n";
	cout << "Data\tJoe\tJane\tJohn" << endl;
	for (int i = 0; i < 10; i++)
	{
		cout << i*10 << "-" << i*10+9 << "\t" << joe_stats[i] << "\t" << jane_stats[i] << "\t" << john_stats[i] << endl;
	}
	cout << "-----------------------------------------\n";
}

//----- main worker thread function ----------------
//----- EVENT HANDLER THREAD        ----------------
void* event_handler_thread(void* c) 
{
  
  int persons[workers_amount];
  RequestChannel * channels[workers_amount];
  fd_set readset;
  int max = 0;
  int result;
  Data request = Data("", 0,0);
  int icount = 0; // count items
  int rcount = 0; // count reads
  struct timeval tv = {0,10};

  cout << "Establishing control channel...";
  RequestChannel chan("control", RequestChannel::CLIENT_SIDE);

  // create channels 
  for(int i = 0; i < workers_amount; i++) 
  {
    string reply = chan.send_request("newthread");
    channels[i] = new RequestChannel(reply,
        RequestChannel::CLIENT_SIDE);
    persons[i] = -1;
  }


  // send initial requests to channels
  for(int i = 0; i < workers_amount; i++) 
  {
	request = request_buffer->getData();
	icount++; 
	channels[i]->cwrite(request.req_con);
	persons[i] = request.person_id; 
  }

  /*
  NOTE FOR DANIEL after your suggestion, I played with it a little and found this::::::
  Moving this (the one using FD_SET) for loop out of the main while loop actually causes problems. the fdset readset 
  needs to be reset after every call to select. Otherwise, we quickly run into problems.  
  Result immediately is 0, and stays 0. The loop never ends. 
  After every select call, the file descriptors (even though the FDs don't themselves actually change)
  status' of ready to read do change after every select call, and as such, the readset containing the FDs 
  also has to be reset before every system call. Thus, It is impossible for the initialization loop of readset
  to be outside of the while loop. 
  BUT... I did find that the result immediately goes to 0, even though the FDs of readset have all been changed 
  just as they would have been changed for the very first go around (i.e. the first time the while loop runs, 
  result should not be 0, but it is 0, based on what reasoning I have to think that the FD_SET loop needs to be under
  the while loop). 
 
  // call select
  FD_ZERO(&readset);
  //perhaps use all the channels' read file descriptors for the readset initialization
  for(int i = 0; i < workers_amount; i++) 
  {
  	if(channels[i]->read_fd() > max)
	{
		max = channels[i]->read_fd();
	}
    FD_SET(channels[i]->read_fd(), &readset);
  }*/

  while(true)
  {
	// call select
	FD_ZERO(&readset);
	//perhaps use all the channels' read file descriptors for the readset initialization
	for(int i = 0; i < workers_amount; i++) 
	{
  		if(channels[i]->read_fd() > max)
		{
			max = channels[i]->read_fd();
		}
		//This line sets the channels' read file descriptors into the readset. 
		//FD_ZERO (above) just makes sure that no strange bits are every encountered, although, 
		//it is probably not
		//needed here. 
		FD_SET(channels[i]->read_fd(), &readset);
	}

	result = select(max+1, &readset, NULL, NULL, &tv);
	//cout << "Result: " << result << endl;
	// files ready to read
	if(result) 
	{
		for(int i = 0; i < workers_amount; i++) 
		{
		if(FD_ISSET(channels[i]->read_fd(), &readset)) 
		{
			cout << "----START READ\n"; 
			string response = channels[i]->cread(); 
			cout << "----END READ\n";
			rcount++;
			cout << "Request count: " << rcount << endl; 
			// deposit request
			switch(persons[i]) 
			{
			case 0: // Joe
				response_Joe_stats->insertData(Data(response, 0, 0));
				break;
			case 1: // Jane
				response_Jane_stats->insertData(Data(response, 0, 1));
				break;
			case 2: // John
				response_John_stats->insertData(Data(response, 0, 2));
				break; 
			}
			cout << "----RETRIEVING ITEM "<<icount<<'\n';
			if(icount < request_num*3) 
			{
				request = request_buffer->getData();
				icount++;
				cout << "----START WRITE\n";
				channels[i]->cwrite(request.req_con);
				cout << "----END WRITE\n";
				persons[i] = request.person_id;
			}
		}
		}
	}


	if(rcount == request_num*3)
	{
	break;
	}

  }

  // close request channels
  for(int i = 0; i < workers_amount; i++) 
  {
    channels[i]->send_request("quit");
  }
  sleep(5);
  chan.send_request("quit");
}

//-------- stats thread helper function -------------
int determine_stat_thread_index_to_increment(int stat)
{
	int index = 0;
	if (stat >= 0 && stat <= 9)
		index = 0;	
	else if (stat >= 10 && stat <= 19)
		index = 1;
	else if (stat >= 20 && stat <= 29)
		index = 2;
	else if (stat >= 30 && stat <= 39)
		index = 3;
	else if (stat >= 40 && stat <= 49)
		index = 4;
	else if (stat >= 50 && stat <= 59)
		index = 5;
	else if (stat >= 60 && stat <= 69)
		index = 6;
	else if (stat >= 70 && stat <= 79)
		index = 7;
	else if (stat >= 80 && stat <= 89)
		index = 8;
	else if (stat >= 90 && stat <= 99)
		index = 9;

	return index;
}

//-------- statistical thread function --------------
void* keep_track_of_statistics(void* c) 
{
  int person = *((int*)c);
  Data response = Data("",0,0);
  int stat_index = 0;

  for(int r_count = 0; r_count < request_num; r_count++) 
  {
    if (person == 0) 
	{
        // Joe
        response = response_Joe_stats->getData();
		stat_index = determine_stat_thread_index_to_increment(atoi(response.req_con.c_str()));
        joe_stats[stat_index]++;
	}
	else if (person == 1)
	{
		// Jane
		response = response_Jane_stats->getData();
		stat_index = determine_stat_thread_index_to_increment(atoi(response.req_con.c_str()));
        jane_stats[stat_index]++;
	}
	else if (person == 2)		
	{
		// John
		response = response_John_stats->getData();
		stat_index = determine_stat_thread_index_to_increment(atoi(response.req_con.c_str()));
        john_stats[stat_index]++;
    }
    cout << "Data recieved by statistical thread: " << r_count << endl;
  }
  cout << "Increment stat semaphore" << endl;
  done_stat_threads.V();
  cout << "exit statistical thread " << person << "..." << endl; 
}

//------- request thread function ----------------
void* request_thread_handler(void* c) 
{
  int person_id = *((int*)c);
  
  for(int i = 0; i < request_num; i++) 
  {
    // generate requests
    Data* request = new Data("",0,0);
    switch(person_id) 
	{
      case 0: // Joe
        joe_sent_count += 1;
        request->req_con = "data Joe Smith";
        request->req_num = joe_sent_count;
        request->person_id = 0;
        break;
      case 1: // Jane
        jane_sent_count += 1;
        request->req_con = "data Jane Smith";
        request->req_num = jane_sent_count;
        request->person_id = 1;
        break;
      case 2: // John
        john_sent_count += 1;
        request->req_con = "data John Doe";
        request->req_num = john_sent_count;
        request->person_id = 2;
        break;
    }
    // place requests in buffer
    request_buffer->insertData(*request);
    delete request;
  }
  cout << "exiting request thread "<< person_id << "..." << endl;
}

// ------ kill function ---------------
void* kill_all_threads(void* nothing) 
{ 
  done_stat_threads.P(); // wait for stat threads to finish

  cout << "killing event handler..." << endl;
  // kill event thread
  for(int i = 0; i < workers_amount; i++) 
  {  
    Data kill = Data("die", -1, -1);
    request_buffer->insertData(kill);
  }
}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) 
{
  // set default argument values
	request_num = 1000;   // number of requests per person
	buff_size = 100;  // size of bounded buffers
	workers_amount = 5;     // number of worker threads
	int temp;

	// get command line args
	while((temp = getopt (argc, argv, "n:b:w:i:")) != -1)
	switch(temp)
	{
		case 'n':
		request_num = atoi(optarg);
		break;

		case 'b':
		buff_size = atoi(optarg);
		break;

		case 'w':
		workers_amount = atoi(optarg);
		break;
		default:
		abort();
	}

	gettimeofday(&t0, 0); //starts timer

	cout << "CLIENT STARTED:" << endl;

	cout << "Starting up Data Server... " << flush;
	pid_t childpid = fork();
	int exec_unless_error = 0;
	if (childpid == 0)
	{
		exec_unless_error = execl("dataserver", NULL);
		if (exec_unless_error == -1)
		{
			perror("error: execution of dataserver failed; exiting program");
			exit(1);
		}
	}
	else if (childpid < 0)
	{
		perror("error: process fork failed; exiting program");
		exit(1);
	}
	else //the parent, which is successfully still alive, executes this code
	{
		//initialize buffers
		request_buffer = new BoundedBuffer(buff_size);
		response_Joe_stats = new BoundedBuffer(buff_size);
		response_Jane_stats = new BoundedBuffer(buff_size);
		response_John_stats = new BoundedBuffer(buff_size);

		//initialize thread containers
		pthread_t workers_thread;
		pthread_t request_threads[3];
		pthread_t stat_threads[3];
		pthread_t death_to_threads;	

		//cout << "Establishing control channel... " << flush;
		//RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
		//cout << "done." << endl;;

		// used to assign threads to persons
		void* joe  = new int(0);
		void* jane = new int(1);
		void* john = new int(2);
  
		// create statistical threads
		cout << "Creating statistical threads... " << flush;
		pthread_create(&stat_threads[0], NULL, keep_track_of_statistics, joe);
		pthread_create(&stat_threads[1], NULL, keep_track_of_statistics, jane);
		pthread_create(&stat_threads[2], NULL, keep_track_of_statistics, john);
		cout << "done." << endl;

		// create event handler thread
		cout << "Creating event handler thread... " << flush;
		pthread_create(&workers_thread, NULL, event_handler_thread, NULL);
		cout << "done." << endl;

		// create request threads
		cout << "Creating request threads... " << flush;
		pthread_create(&request_threads[0], NULL, request_thread_handler, joe);
		pthread_create(&request_threads[1], NULL, request_thread_handler, jane);
		pthread_create(&request_threads[2], NULL, request_thread_handler, john);
		cout << "done." << endl;

		// create kill thread
		cout << "Creating kill thread... " << flush;
		pthread_create(&death_to_threads, NULL, kill_all_threads, NULL);
		cout << "done." << endl;
  
  
		pthread_join(death_to_threads, NULL);
		pthread_join(workers_thread, NULL);

		//string reply4 = chan.send_request("quit");
		//cout << "Reply to request 'quit' is '" << reply4 << "'" << endl;
		usleep(1000000);
		//delete joe;
		//delete jane;
		//delete john;
		delete request_buffer;
		delete response_Joe_stats;
		delete response_Jane_stats;
		delete response_John_stats;

		print_histogram();

		gettimeofday(&t1, 0); //ends timer

		long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
		cout << request_num << " requests done in " << elapsed << " microseconds." << endl;

		/*-- Start sending a sequence of requests 

		string reply1 = chan.send_request("hello");
		cout << "Reply to request 'hello' is '" << reply1 << "'" << endl;

		string reply2 = chan.send_request("data Joe Smith");
		cout << "Reply to request 'data Joe Smith' is '" << reply2 << "'" << endl;

		string reply3 = chan.send_request("data Jane Smith");
		cout << "Reply to request 'data Jane Smith' is '" << reply3 << "'" << endl;

		string reply5 = chan.send_request("newthread");
		cout << "Reply to request 'newthread' is " << reply5 << "'" << endl;
		RequestChannel chan2(reply5, RequestChannel::CLIENT_SIDE);

		string reply6 = chan2.send_request("data John Doe");
		cout << "Reply to request 'data John Doe' is '" << reply6 << "'" << endl;

		string reply7 = chan2.send_request("quit");
		cout << "Reply to request 'quit' is '" << reply7 << "'" << endl;

		string reply4 = chan.send_request("quit");
		cout << "Reply to request 'quit' is '" << reply4 << "'" << endl;
		*/
	}
}
