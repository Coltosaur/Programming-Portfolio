/*

	Project 2: Reversi
	CSEC 315
	Team 502-e 
	

	This is used for establishing socket connection on server side
	compile command must be: g++ serverSocket.cpp -o server -lsocket -lnsl
	wont be compiled if missing lsocket and lnsl
	This was only tested and compiled on CS tamu UNIX server
	from now:
	open 2 terminals
		Server term: server 12345
		Client term: client 127.0.0.1 12345
		Client term: input message
		... both will get responses

*/
#include "gameServer.h"

#include <stdio.h>
#include <stdlib.h>
#include <strings.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <netinet/in.h>

int main(int argc, char *argv[]) {

	int sock, newsock, port_num;
	char send_message[1024], receive_message[1024];
	socklen_t clientlen;
	struct sockaddr_in server_address, client_address;

	//check if command calls contain port number

	if (argc <2) {
	
		fprintf(stderr, "Missing Port Number");
		exit(1);
	} else {
		
		//get the port number
		port_num = atoi(argv[1]);
	}
	//creating a socket 
	//1st para = domain
	//2nd = type
	//3rd = protocol

	sock = socket(AF_INET, SOCK_STREAM, 0);

	if (sock < 0) {
		fprintf(stderr, "Error whille openning socket");
		exit(1);
	}

	//clear address structure
	bzero((char *) &server_address, sizeof(server_address));

	//setup the server address structure for binding call
	
	server_address.sin_family = AF_INET;	// server byte order
	server_address.sin_addr.s_addr = INADDR_ANY; //filled with current host's IP usually 127.0.0.1
	server_address.sin_port = htons(port_num); // converting port num into network byte order

    	// This bind() call will bind  the socket to the current IP address on port, port_num
     	if (bind(sock, (struct sockaddr *) &server_address, sizeof(server_address)) < 0)  {
		
		 fprintf(stderr, "Error while binding");
		 exit(1);
	 }

	 // listen() dectect the incoming connections
	 if (listen(sock,5) < 0 ) {
		
		fprintf(stderr, "Error while listening");
		exit(1);

	 }

	 clientlen = sizeof(client_address);

	 //accepting connection
	 //the accept return a new socket file descriptor
	 // in order to reuse the original socket file for accepting new connections
	 // using another socket file newsock to communicate with connected client
	 newsock = accept(sock, (struct sockaddr *) &client_address, &clientlen);

	 if (newsock < 0)
		fprintf(stderr,"Error while accepting");
	
	 printf("server: got connection from %s port %d\n", inet_ntoa(client_address.sin_addr), ntohs(client_address.sin_port));

	 //testing sending mess
	 //this will send to the client
	 
	 //creating serverEngine 
	 //Start Game Engine
	 serverEngine e;
	 
	 string board ="";
	 string AImove;
	 board = e.showBoard();
	 bzero(send_message,1024); //clear

	 memcpy(send_message,board.c_str(),board.size());

	 int count =0;
	while (1) {
	 /*
	 Comment out this code if wanting to send a message to client manually otherwise
	 the board will be sent
	 
	 printf("Enter 'q' to terminate or send a message to this client: \n");
	 
	 bzero(send_message,1024);
	 fgets(send_message,1023,stdin);
	 */
		
		//beginning with sending the board to the client
		//the board has been initialized before while loop for the first time 
		//and before the end of while loop for the rest
		
		
	send(newsock, send_message,1024,0);
	//starting receiving message
	 bzero(receive_message,1024);//clear
	//clear the board
	board.clear();
		
	 int n;
	 n = read(newsock,receive_message,1024);
		
	if (n <0) {
		fprintf(stderr,"Error while reading from socket");
	}
		
	if (receive_message[0] != '\0') {
		
		if (receive_message[0] == 'q' ) {
			
		  send(newsock, "thank you for playing", 22,0);
		  printf("Client sends disconnection request!\n");
		  close(newsock);
		  break;
		}
		printf("The received request from client is: %s ",receive_message);
		string help;
		//Receive "help" command from the client
		if ( receive_message[0] == 'h' && receive_message[1] == 'e' 
				&& receive_message[2] == 'l' && receive_message[3] == 'p') {
			printf("Receive the help request from client!");
			help = "\nThe list of move that you can play: ";
			help += e.printValidMoves('O');
			board += help;
			
		} else if (receive_message[0] == 'u' && receive_message[1] == 'n'
				&& receive_message[2] == 'd' && receive_message[3] == 'o'){
				
				//receive 'undo' command from the client
				e.undo(count-1);
				
		} else {
				
		//this if statement is for testing Human - AI
		//Assumption Human play first!
		
		if(!e.makeMove('O',receive_message)) {
			//receiving an invalid move from user -> no AI move
			//still return the board with no move!
			
			printf("Invalid Move For O -> Generating Table with count = %d\n",count);
			board += "Invalid Move!\n"; 
			
		} else { 
		
			//AI make a move here
			
			count+= 1;
			AImove = e.AImove();
			printf("Move For AI -> Generating Table with count = %d\n",count);
		
			board += AImove;
			e.updateBoard(count);

			}
		}
		board += e.showBoard();

		bzero(send_message,1024);

		memcpy(send_message,board.c_str(),board.size());
	
		printf("Sending reply to client\n**********************************\n");

		//save the state of the board for undo
		
	 }	
	}
	 close(sock);
	 return 0;
	 



}




