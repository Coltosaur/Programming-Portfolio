# makefile

all: dataserver client

semaphore.o: semaphore.H semaphore.c
	g++ -c -g semaphore.c

boundedbuffer.o: boundedbuffer.h boundedbuffer.c semaphore.o
	g++ -c -g boundedbuffer.c

reqchannel.o: reqchannel.H reqchannel.C
	g++ -c -g reqchannel.C

dataserver: dataserver.C reqchannel.o 
	g++ -g -o dataserver dataserver.C reqchannel.o -lpthread

client: client.C reqchannel.o semaphore.o boundedbuffer.o
	g++ -g -o client client.C reqchannel.o semaphore.o boundedbuffer.o -pthread
