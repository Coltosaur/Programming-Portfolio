/*
 Test pilot program for helper network functions
*/
#include <stdio.h>
#include <stdlib.h>
#include <sstream>
#include <iostream>
#include <string>

using namespace std;

string short2string(const unsigned short num)
{
	stringstream ss; //create a stringstream
	ss << num; //add num to the stream
	return ss.str(); //return a string with the contents of the stream
}

int main(void)
{
	const unsigned short num = 50;
	
	cout << "Short: " << short2string(num) << endl;
	return 0;
}
