/* 
    File: dataserver.C

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2012/07/16

    Dataserver main program for MP3 in CSCE 313
*/

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <cassert>
#include <string>
#include <string.h>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <errno.h>

//#include "reqchannel.H"
#include "NetworkRequestChannel.H"

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTANTS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* VARIABLES */
/*--------------------------------------------------------------------------*/

static int nthreads = 0;

/*--------------------------------------------------------------------------*/
/* FORWARDS */
/*--------------------------------------------------------------------------*/

//void handle_process_loop(RequestChannel & _channel);
//void handle_process_loop(NetworkRequestChannel & _channel);

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- SUPPORT FUNCTIONS */
/*--------------------------------------------------------------------------*/

string int2string(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- THREAD FUNCTIONS */
/*--------------------------------------------------------------------------*/

/*void * handle_data_requests(void * args) {

  RequestChannel * data_channel =  (RequestChannel*)args;

  // -- Handle client requests on this channel. 
  
  handle_process_loop(*data_channel);

  // -- Client has quit. We remove channel.
 
  delete data_channel;
}*/

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- INDIVIDUAL REQUESTS */
/*--------------------------------------------------------------------------*/

/*void process_hello(RequestChannel & _channel, const string & _request) {
  _channel.cwrite("hello to you too");
}*/

void process_hello(int sockfd, const string & _request)
{
	string s = "hello to you too";
	if (send(sockfd, s.c_str(), s.length(), 0) == -1)
		perror("server: send process_hello");
}

/*
void process_data(RequestChannel & _channel, const string &  _request) {
  usleep(1000 + (rand() % 5000));
  //_channel.cwrite("here comes data about " + _request.substr(4) + ": " + int2string(random() % 100));
  _channel.cwrite(int2string(rand() % 100));
}*/

void process_data(int sockfd, const string & request)
{
	usleep(1000 + (rand() % 5000));
	string s = int2string(rand()%100);
	if (send(sockfd, s.c_str(), s.length(), 0) == -1)
		perror("server: send process_data");
}

/*
void process_newthread(RequestChannel & _channel, const string & _request) {
  int error;
  nthreads ++;

  // -- Name new data channel

  string new_channel_name = "data" + int2string(nthreads) + "_";
  //  cout << "new channel name = " << new_channel_name << endl;

  // -- Pass new channel name back to client

  _channel.cwrite(new_channel_name);

  // -- Construct new data channel (pointer to be passed to thread function)
  
  RequestChannel * data_channel = new RequestChannel(new_channel_name, RequestChannel::SERVER_SIDE);

  // -- Create new thread to handle request channel

  pthread_t thread_id;
  //  cout << "starting new thread " << nthreads << endl;
  if (error = pthread_create(& thread_id, NULL, handle_data_requests, data_channel)) {
    fprintf(stderr, "p_create failed: %s\n", strerror(error));
  }  

}*/

/*--------------------------------------------------------------------------*/
/* LOCAL FUNCTIONS -- THE PROCESS REQUEST LOOP */
/*--------------------------------------------------------------------------*/

/*void process_request(RequestChannel & _channel, const string & _request) {

  if (_request.compare(0, 5, "hello") == 0) {
    process_hello(_channel, _request);
  }
  else if (_request.compare(0, 4, "data") == 0) {
    process_data(_channel, _request);
  }
  else if (_request.compare(0, 9, "newthread") == 0) {
    process_newthread(_channel, _request);
  }
  else {
    _channel.cwrite("unknown request");
  }

}*/

void process_request(int sockfd, const string & _request)
{
	if (_request.compare(0,5, "hello") == 0)
	{
		process_hello(sockfd, _request);
	}
	else if (_request.compare(0, 4, "data") == 0) 
	{
		process_data(sockfd, _request);
	}
	//else if (_request.compare(0, 9, "newthread") == 0) 
	//{
		//process_newthread(sockfd, _request);
	//}
	else 
	{
		string s = "unknown request";
		if (send(sockfd, s.c_str(), s.length(), 0) == -1)
			perror("server: send from process request");
	}
}

/*
void handle_process_loop(RequestChannel & _channel) {

  for(;;) {

    cout << "Reading next request from channel (" << _channel.name() << ") ..." << flush;
    string request = _channel.cread();
    cout << " done (" << _channel.name() << ")." << endl;
    cout << "New request is " << request << endl;

    if (request.compare("quit") == 0) {
      _channel.cwrite("bye");
      usleep(10000);          // give the other end a bit of time.
      break;                  // break out of the loop;
    }

    process_request(_channel, request);
  }
  
}*/

//CONNECTION HANDLER FUNCTION
void* connection_handler(void* c)
{
	int sockfd = *((int*)c);
	int receive = 0;
	string request = "";
	char buf[MAXDATASIZE];
	
	for(;;)
	{
		cout << "Reading next request from channel(" << sockfd << ") ..." << endl;
		
		buf[0] = '\0';
		request.clear();

		if ((receive = recv(sockfd, buf, MAXDATASIZE-1,0)) == -1)
		{
			cout << "in error of receive" << endl;
			perror("server: recv");
		}
		else if (receive == 0)
		{
			cout << "socket closed" << endl;
			continue;
		}
		else if (receive > 0)
		{
			request = buf;
			cout << "New request is " << request << endl;
		}
		usleep(10000);
		//handle quit here
		if (request.compare("quit") == 0)
		{
			string s = "bye";
			if (send(sockfd, s.c_str(), s.length(), 0) == -1)
				perror("server: send");
			//usleep(1000000);
			close(sockfd);
			break;
		}

		process_request(sockfd, request);
	}

}

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {

    cout << "Establishing server channel... \n" << flush;
  //RequestChannel control_channel("control", RequestChannel::SERVER_SIDE);
	int temp; 
	unsigned short port_num;
	int backlog;

	//cout << "port num: " << port_num << endl;
	//cout << "backlog num: " << backlog << endl;

	while((temp = getopt(argc, argv, "p:b:")) != -1)
	switch(temp)
	{
	case 'p':
		port_num = (unsigned short)(atoi(optarg));
		break;
	case 'b':
		backlog = atoi(optarg);
		break;
	default:
		abort();
	}
	cout << "port num: " << port_num << endl;
	cout << "backlog num: " << backlog << endl;

	NetworkRequestChannel control_channel(port_num, backlog, connection_handler);
  //  cout << "done.\n" << flush;

  //handle_process_loop(control_channel);

}

