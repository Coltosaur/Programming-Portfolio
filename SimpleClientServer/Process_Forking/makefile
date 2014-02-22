# makefile

all: dataserver client function_time_delay

reqchannel.o: reqchannel.H reqchannel.C
	g++ -c -g reqchannel.C

dataserver: dataserver.C reqchannel.o 
	g++ -o dataserver dataserver.C reqchannel.o -lpthread

client: client.C reqchannel.o
	g++ -o client client.C reqchannel.o

function_time_delay: function_time_delay.C
	g++ -o function_time_delay function_time_delay.C