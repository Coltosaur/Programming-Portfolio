/*
** This is the NetworkRequestChannel.H file
** Written by Colt Campbell
** CSCE 313-504 MP5
*/

#ifndef _NETWORKREQUESTCHANNEL_H_
#define _NETWORKREQUESTCHANNEL_H_

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

#define MAXDATASIZE 256

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include <signal.h>
#include <sstream>
#include <iostream>
#include <cassert>
#include <pthread.h>

using namespace std;

/*--------------------------------------------------------------------------*/
/* DATA STRUCTURES */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* HELPER FUNCTIONS */ 
/*--------------------------------------------------------------------------*/

/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CLASS  N e t w o r k R e q u e s t C h a n n e l */
/*--------------------------------------------------------------------------*/

class NetworkRequestChannel
{
private:
	int sockfd;
	//int numbytes; //client specific
	//struct addrinfo hints, *servinfo, *p;
	//char s[INET6_ADDRSTRLEN]; 
	//char buf[MAXDATASIZE]; //client specific
	//int rv;

	//fd_set read_fds;

	//pthread_t accepted_client_thread;

public:
	NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no);
	/* Creates a CLIENT-SIDE local copy of the channel. The channel is connected
	to the given port number at the given server host. This constructor is called by 
	The CLIENT. 
	*/

	NetworkRequestChannel(const unsigned short _port_no, int backlog, void *(*connection_handler)(void*));
	/* Creates a SERVER-SIDE local copy of the channel that is accepting connections 
	at the given port number. 
	NOTE that multiple clients can be connected to the same server-side end of the 
	request channel. Whenever a new connection comes in, it is accepted by the server, 
	and the given connection handler is invoked. The parameter to the connection 
	handler is the file descriptor of the slave socket returned by the accept call. 
	NOTE that the connection handler does not want to deal with closing the socket. 
	You will have to close the socket once the connection handler is done. */

	~NetworkRequestChannel();
	/* Destructor of the local copy of the channel. */

	string send_request(string _request);
	/* Send a string over the channel and wait for a reply. */

	string cread();
	/* Blocking read of data from the channel. Returns a string
	of characters read from the channel. Returns NULL if read failed. */

	int cwrite(string _msg);
	/* Write the data to the channel. The function returns the number of characters
	written to the channel. */

	int read_sockfd()
	{
		return sockfd;
	}

	//used in convertin the unsigned short port number to a string (for conversion
	//to char* for getaddrinfo)
	string short2string(const unsigned short num)
	{
		stringstream ss; //create a stringstream
		ss << num; //add num to the stream
		return ss.str(); //return a string with the contents of the stream
	}

	//signal handler for server sigaction sa (used in killing zombies)
	void sigchld_handler(int s)
	{
		while (waitpid(-1, NULL, WNOHANG) > 0);
	}

	//get sockaddr, IPv4, or IPv6
	void *get_in_addr(struct sockaddr *sa)
	{
		if (sa->sa_family == AF_INET)
		{
			return &(((struct sockaddr_in*)sa)->sin_addr);
		}
		return &(((struct sockaddr_in6*)sa)->sin6_addr);
	}
};

#endif //END NETWORKREQUESTCHANNEL_H