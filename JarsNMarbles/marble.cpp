#include "marble.h"
#include <string>
#include <iostream>
#include <math.h>

using namespace std; 
Marble::Marble()
{
    switch(random_color())
    {
        case 0:
            color = red;
            break;
        case 1:
            color = blue;
            break;
        case 2:
            color = yellow;
            break;
        case 3:
            color = green;
            break;
        default:
            cout << "Error in getting color.";
            break;
    }
    switch(random_size())
    {
        case 0:
            size = small;
            break;
        case 1:
            size = medium;
            break;
        case 2:
            size = large;
            break;
        default:
            cout << "no available size";
            break;
    }
}
     
Marble::Marble(Color c):color(c)
{
    set_color(c);
    switch(random_size())
    {
        case 0:
            set_size(small);
            break;
        case 1:
            set_size(medium);
            break;
        case 2:
            set_size(large);
            break;
        default:
            cout << "no available size";
            break;
    }
}

Marble::Marble(Size s):size(s)
{
    switch(random_color())
    {
        case 0:
            set_color(red);
            break;
        case 1:
            set_color(blue);
            break;
        case 2:
            set_color(yellow);
            break;
        case 3:
            set_color(green);
            break;
        default:
            cout << "no color available";
            break;
    }
    set_size(s);
}

Marble::Marble(Color c, Size s):color(c),size(s)
{
    set_size(s);
    set_color(c);
}

void Marble::set_color(Color c)
{ 
    color = c; 
}

void Marble::set_size(Size s)
{
    size = s; 
}

Marble::Color Marble::get_color() const
{
    return color;
}

Marble::Size Marble::get_size() const
{  
    return size;
}

int Marble::random_size()   
{
    int random_num1 = rand()%3;
    return random_num1;
}

int Marble::random_color()
{
    int random_num2 = rand()%4;
    return random_num2;
}

bool operator==(const Marble& m1, const Marble& m2)
{
    return (m1.get_color() == m2.get_color())&&(m1.get_size() == m2.get_size());
}

ostream& operator<<(ostream& os, const Marble& m)
{
    switch(m.get_color())
    {
        case 0:
            os<<"red";
            break;
        case 1:
            os<<"blue";
            break;
        case 2:
            os<<"yellow";
            break;
        case 3:
            os<<"green";
            break;
    }
    os<<", ";      
    switch(m.get_size())
    {
        case 0:
            os<<"small";
            break;
        case 1:
            os<<"medium";
            break;
        case 2:
            os<<"large";
            break;
    }
    return os;
}

istream& operator>>(istream& is, Marble& m)
{    
     string c,s; // i need these to be a color and a size :( grrr    
     is >> c >> s;
     if (c == "red")
        m.set_color(Marble::red);
     else if (c=="blue")
	   m.set_color(Marble::blue);
     else if (c=="yellow")
	   m.set_color(Marble::yellow);
     else if (c=="green")
           m.set_color(Marble::green);
     else
        cout << "Invalid Color\n";
		 
     if (s == "small")
	m.set_size(Marble::small);
     else if (s=="medium")
           m.set_size(Marble::medium);
     else if (s=="large")
	   m.set_size(Marble::large);
     else
	cout << "Invalid Size\n";
     
     if (!is) return is;
     return is;   
}
