/* 
    File: simpleclient.C

    Author: R. Bettati
            Department of Computer Science
            Texas A&M University
    Date  : 2012/07/11

    Simple client main program for MPs in CSCE 313
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
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
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
/* FORWARDS */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* MAIN FUNCTION */
/*--------------------------------------------------------------------------*/

int main(int argc, char * argv[]) {

	// set default argument values
	int request_num = 1000;   // number of requests per person
	int buff_size = 100;  // size of bounded buffers
	int workers_amount = 5;     // number of worker threads
	string server_host_name = "";
	unsigned short port_num = 0;
	int temp;

	// get command line args
	while((temp = getopt (argc, argv, "n:b:w:h:p:")) != -1)
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
		
	case 'h':
		server_host_name = optarg;
		break;

	case 'p':
		port_num = (unsigned short)(atoi(optarg));
		break;

	default:
		abort();
	}

	cout << "CLIENT STARTED:" << endl;

	cout << "Establishing control channel... " << flush;
	//RequestChannel chan("control", RequestChannel::CLIENT_SIDE);
	NetworkRequestChannel chan(server_host_name, port_num);
	cout << "done." << endl;;

	/* -- Start sending a sequence of requests */

	string reply1 = chan.send_request("hello");
	cout << "Reply to request 'hello' is '" << reply1 << "'" << endl;

	string reply2 = chan.send_request("data Joe Smith");
	cout << "Reply to request 'data Joe Smith' is '" << reply2 << "'" << endl;

	string reply3 = chan.send_request("data Jane Smith");
	cout << "Reply to request 'data Jane Smith' is '" << reply3 << "'" << endl;

	//string reply5 = chan.send_request("newthread");
	//cout << "Reply to request 'newthread' is " << reply5 << "'" << endl;
	//RequestChannel chan2(reply5, RequestChannel::CLIENT_SIDE);

	//string reply6 = chan2.send_request("data John Doe");
	//cout << "Reply to request 'data John Doe' is '" << reply6 << "'" << endl;

	//string reply7 = chan2.send_request("quit");
	//cout << "Reply to request 'quit' is '" << reply7 << "'" << endl;

	string reply4 = chan.send_request("quit");
	cout << "Reply to request 'quit' is '" << reply4 << "'" << endl;

	usleep(1000000);
}
