# makefile mp5

all: dataserver client

semaphore.o: semaphore.H semaphore.c
	g++ -c -g semaphore.c

boundedbuffer.o: boundedbuffer.h boundedbuffer.c semaphore.o
	g++ -c -g boundedbuffer.c
	
NetworkRequestChannel.o: NetworkRequestChannel.H NetworkRequestChannel.C
	g++ -c -g NetworkRequestChannel.C -lsocket -lnsl -lpthread

dataserver: dataserver.C NetworkRequestChannel.o
	g++ -g -o dataserver dataserver.C NetworkRequestChannel.o -lsocket -lnsl -lpthread

client: client.C NetworkRequestChannel.o semaphore.o boundedbuffer.o
	g++ -g -o client client.C NetworkRequestChannel.o semaphore.o boundedbuffer.o -lsocket -lnsl -pthread
