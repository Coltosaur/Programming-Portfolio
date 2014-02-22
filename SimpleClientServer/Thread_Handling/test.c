/* 
My test file for the semaphore and boundedbuffer
*/
#include <iostream>
#include "semaphore.H"
#include "boundedbuffer.h"

int main()
{
	BoundedBuffer b = BoundedBuffer(10);
	Semaphore s = Semaphore(1);
	for (int i = 0; i < 5; i++)
	{
		Data test = Data("test", 0, 0);
		test.printData();
		b.producer(test);
	}
	s.P();
	s.V();
	s.P();
	for (int i = 0; i < 5; i++)
	{
		Data hopes_it_works = b.consumer();
		hopes_it_works.printData(); //woot it works :)
	}
	return 0;
}
