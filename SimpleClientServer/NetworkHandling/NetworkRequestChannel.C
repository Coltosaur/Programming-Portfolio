/*
** This is the network request channel c file
** Written by Colt Campbell
** CSCE 313-504 MP5
*/ 

/*--------------------------------------------------------------------------*/
/* DEFINES */
/*--------------------------------------------------------------------------*/

    /* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* INCLUDES */
/*--------------------------------------------------------------------------*/

#include "NetworkRequestChannel.H"

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
/* PRIVATE METHODS FOR CLASS   N e t w o r k R e q u e s t C h a n n e l    */
/*--------------------------------------------------------------------------*/

	/* -- (none) -- */

/*--------------------------------------------------------------------------*/
/* CONSTRUCTOR/DESTRUCTOR FOR CLASS   N e t w o r k R e q u e s t C h a n n e l  */
/*--------------------------------------------------------------------------*/

//CLIENT-SIDE local copy of channel
NetworkRequestChannel::NetworkRequestChannel(const string _server_host_name, const unsigned short _port_no)
{
	int rv;
	char s[INET6_ADDRSTRLEN]; 
	struct addrinfo hints, *servinfo, *p;
	string port_num = short2string(_port_no);

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	
	if ((rv = getaddrinfo(_server_host_name.c_str(), port_num.c_str(), &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	//loop through all the results and connect to the first we can
	for (p = servinfo; p!= NULL; p = p->ai_next)
	{
		if ((sockfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
		{
			perror("client: socket");
			continue;
		}
		if (connect(sockfd, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(sockfd);
			perror("client: connect");
			continue;
		}
		break;
	}

	if (p == NULL)
	{
		//we get here if we haven't connected to anything
		fprintf(stderr, "client: failed to connect.\n");
		exit(2);
	}

	inet_ntop(p->ai_family, get_in_addr((struct sockaddr *)p->ai_addr), s, sizeof s);
	printf("client: connecting to %s\n", s);

	freeaddrinfo(servinfo);
}

//SERVER-SIDE local copy of channel
NetworkRequestChannel::NetworkRequestChannel(const unsigned short _port_no, 
											 int backlog, void *(*connection_handler)(void *))
{
	int rv;
	char s[INET6_ADDRSTRLEN]; 
	struct sockaddr_storage their_addr; //server specific
	socklen_t sin_size; //server specific
	struct sigaction sa; //server specific
	int yes; //server specific
	struct addrinfo hints, *servinfo, *p;
	string port_num = short2string(_port_no);

	memset(&hints, 0, sizeof hints);
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_flags = AI_PASSIVE; //use my IP

	yes = 1;
	int socketfd = 0;

	if ((rv = getaddrinfo(NULL, port_num.c_str(), &hints, &servinfo)) != 0)
	{
		fprintf(stderr, "getaddrinfo: %s\n", gai_strerror(rv));
		exit(1);
	}

	//loop through all the results and bind to the first we can
	for (p = servinfo; p != NULL; p = p->ai_next)
	{
		if ((socketfd = socket(p->ai_family, p->ai_socktype, p->ai_protocol)) == -1)
		{
			perror("server: socket");
			continue;
		}

		if (setsockopt(socketfd, SOL_SOCKET, SO_REUSEADDR, &yes, sizeof(int)) == -1)
		{
			perror("setsockopt");
			exit(1);
		}

		if (bind(socketfd, p->ai_addr, p->ai_addrlen) == -1)
		{
			close(socketfd);
			perror("server: bind");
			continue;
		}
		break;
	}

	if (p == NULL)
	{
		fprintf(stderr, "server: failed to bind\n");
		exit(2);
	}

	freeaddrinfo(servinfo);

	if (listen(socketfd, backlog) == -1)
	{
		perror("listen");
		exit(1);
	}

	printf("server: waiting for connections...\n");

	while(1) //main accept() loop
	{
		sin_size = sizeof their_addr;
		sockfd = accept(socketfd, (struct sockaddr *)&their_addr, &sin_size);
		if (sockfd == -1)
		{
			perror("accept");
			continue;
		}
		pthread_t accepted_client_thread;

		inet_ntop(their_addr.ss_family, get_in_addr((struct sockaddr *)&their_addr), s, sizeof s);
		printf("server: got connection from %s\n", s);
		pthread_create(&accepted_client_thread, NULL, connection_handler, &sockfd);
		//close(socketfd);
	}
	pthread_exit(NULL);
}

//Destructor for channels
NetworkRequestChannel::~NetworkRequestChannel()
{
	//freeaddrinfo(servinfo); //all done with this structure
	close(sockfd);
	//FD_ZERO(&read_fds);
}

/*--------------------------------------------------------------------------*/
/* READ/WRITE FROM/TO NETWORK REQUEST CHANNELS  */
/*--------------------------------------------------------------------------*/

string NetworkRequestChannel::send_request(string _request)
{
	cwrite(_request);
	string s = cread();
	return s;
}

string NetworkRequestChannel::cread()
{
	char buf[MAXDATASIZE-1];
	int numbytes = 0;
	string s = "";

	if ((numbytes = recv(sockfd, buf, MAXDATASIZE-1, 0)) <= 0)
	{
		cout << "numbytes " << numbytes << endl;
		return NULL;
	}
	cout << "numbytes " << numbytes << endl;
	s = buf;
	return s;
}

int NetworkRequestChannel::cwrite(string _msg)
{
	int sent_bytes = 0;
	if (_msg.length() >= MAXDATASIZE)
	{
		cerr << "message too long for channel!\n";
		return -1;
	}

	const char * s = _msg.c_str();
	if ((sent_bytes = send(sockfd, s, strlen(s)+1, 0)) == -1)
	{
		perror("send");
	}
	return sent_bytes;
}