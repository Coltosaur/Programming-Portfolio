/*
So, this program is what I, Colt Campbell, used to implement a function 
that sends a request and gets a reply based on the request. At first, I tried
using more or less of the same code that is in the dataserver.c and reqchannel.c/h files
in order to emulate the same way the code is being produced and thus getting a more 
accurate measure of the speed of process_request in a single process. However, I found 
it simpler to make a function (process_request_no_channels(string request)) that 
takes in a request string and returns a string that is the reply. The overall performance 
is much faster as well doing it through one function than through several functions
anyways. 
I will comment out the unneeded code but know that it can fairly easily work 
with "handle_process(string request)" in the main function as with my own implementation
of the task.
*/

#include <cassert>
#include <cstring>
#include <sstream>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>

#include <pthread.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>

using namespace std;

/*
int wfd;
int rfd;

const int MAX_MESSAGE = 255;

string cread() {

  char buf[MAX_MESSAGE];

  if (read(rfd, buf, MAX_MESSAGE) < 0) {
    perror(string("Error reading from pipe!").c_str());
  }
  
  string s = buf;

  //  cout << "Request Channel (" << my_name << ") reads [" << buf << "]\n";

  return s;

}

int cwrite(string _msg) {

  if (_msg.length() >= MAX_MESSAGE) {
    cerr << "Message too long for Channel!\n";
    return -1;
  }

  //  cout << "Request Channel (" << my_name << ") writing [" << _msg << "]";

  const char * s = _msg.c_str();

  if (write(wfd, s, strlen(s)+1) < 0) {
    perror(string("Error writing to pipe!").c_str());
  }

  //  cout << "(" << my_name << ") done writing." << endl;
} 
*/

string int2string(int number) {
   stringstream ss;//create a stringstream
   ss << number;//add number to the stream
   return ss.str();//return a string with the contents of the stream
}

/*
void process_hello(const string & _request) {
  cwrite("hello to you too");
}

void process_data(const string &  _request) {
  cwrite(int2string(rand() % 100));
}

void process_request(const string & _request) {

  if (_request.compare(0, 5, "hello") == 0) {
    process_hello( _request);
  }
  else if (_request.compare(0, 4, "data") == 0) {
    process_data(_request);
  }
  //else if (_request.compare(0, 9, "newthread") == 0) {
    //process_newthread(_channel, _request);
  //}
  else {
   cwrite("unknown request");
  }

}


void handle_process(string request) {
	cout << "Request: " << request << endl;

    if (request.compare("quit") == 0) {
      cwrite("bye");         // give the other end a bit of time.
      exit(0);                // break out of the loop;
    }

    process_request(request);
}
*/

string process_request_no_channels(string request)
{
	if (request.compare(0, 5, "hello") == 0) {
		return "Hello to you too";
	}
	else if (request.compare(0, 4, "data") == 0) {
		return int2string(rand() % 100);
	}
	else if (request.compare("quit") == 0)
	{
		return "bye";
	}
	else
		return "unknown request";
}

int main(int argc, char * argv[]) {
  struct timeval t0, t1;

  for (int i = 0; i < 100; i++)
  {
	string request = "data TestPerson" + int2string(i);
	cout << "Request " << request << endl; 
    gettimeofday(&t0, 0);
	//handle_process("data TestPerson" + int2string(i));
	string request_reply = process_request_no_channels(request);
	gettimeofday(&t1, 0);
	cout << "Reply to request " << request_reply << endl;
	cout << endl << flush;
	long elapsed = (t1.tv_sec-t0.tv_sec)*1000000 + t1.tv_usec-t0.tv_usec;
    cout << "Function Comm done in " << elapsed << " microseconds." << endl;
	cout << endl << flush;
	if (request.compare("quit") == 0)
		exit(0);
  }

}