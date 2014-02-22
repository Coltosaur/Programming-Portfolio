/*
This file will be our bounded_buffer header file.
It will be used to declare the bounded_buffer
operations and constructor/destructor. 
*/

#ifndef _BOUNDEDBUFFER_H_
#define _BOUNDEDBUFFER_H_

#include <pthread.h>
#include <queue>
#include <string>
#include <iostream>
#include "semaphore.H"

using namespace std;

class Data
{
public: 
	string req_con; //request content
	int req_num; //request number
	int person_id; //identifier for person

	Data(string content, int num, int id)
	{
		// Constructor
		req_con = content;
		req_num = num; 
		person_id = id;
	}

	void printData()
	{
		cout << req_con << "\n";
	}
};

class BoundedBuffer
{
private:
	Semaphore* lock;
	Semaphore* full;
	Semaphore* empty;
	queue<Data> q; 
public:
	int buff_size;

	BoundedBuffer(int size); //Constructor

	~BoundedBuffer(); //Destructor

	void insertData(Data data);

	Data getData();
};


#endif //_BOUNDEDBUFFER_H_