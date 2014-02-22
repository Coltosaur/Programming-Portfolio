/*
This file will implement our bounded_buffer functions
and constructor/destructor. 
*/

#include "boundedbuffer.h"

BoundedBuffer::BoundedBuffer(int size)
{
	//Constructor
	buff_size = size;
	lock = new Semaphore(1);
	full = new Semaphore(0);
	empty = new Semaphore(buff_size);
}

BoundedBuffer::~BoundedBuffer()
{
	//Destructor
	delete lock;
	delete full;
	delete empty;
}

void BoundedBuffer::insertData(Data data)
{
	/*
	Produces data in the buffer by pushing it to buffer.
	We first decrement empty, then start the critical section 
	and push the data into the buffer, then end critical section
	and finally increment full. 
	*/
	empty->P();
	lock->P();
	q.push(data);
	lock->V();
	full->V();
}

Data BoundedBuffer::getData()
{
	/*
	Here, the consumer pulls data from the buffer
	(consuming the data). We achieve this by decrementing 
	full, starting the critical section, popping the data 
	out of the buffer, ending the critical section, and then 
	incrementing empty. 
	*/
	full->P();
	lock->P();
	Data d = q.front();
	q.pop();
	lock->V();
	empty->V();
	return d;
}

