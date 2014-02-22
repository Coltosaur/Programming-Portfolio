#include "llist_jar.h"

LListJar::LListJar()
{
}

LListJar::LListJar(int len)
{
}

LListJar::LListJar(const LListJar& jar)
{
}
  
const Marble& LListJar::get_elem(int i) const
{
}
  
void LListJar::add(const Marble& m)
{
}

void LListJar::remove(const Marble& m)
{
   list<Marble>::iterator i;
   for (i = ll.begin(); i != ll.end(); ++i)
      if (*i == m) {
         ll.erase(i); // make yourself familiar with the functions of
                      // list class in STL, e.g. erase
         break;
      }
}
// finish the constructors and the rest functions by yourself

Marble LListJar::remove_any()
{
}
 
void LListJar::clear()
{
}

bool LListJar::is_empty() const
{
}

bool LListJar::is_in_jar(const Marble& m) const
{
}
   
int LListJar::marble_number() const
{
}
   
int LListJar::marble_nsize(Marble:: Size s) const
{
}
   
int LListJar::marble_ncolor(Marble:: Color c) const
{
}
   
void LListJar::merge(const Jar& jar1, const Jar& jar2)
{
}
   
void LListJar::intersection(const Jar& jar1, const Jar& jar2)
{
}
   
void LListJar::difference(const Jar& jar1, const Jar& jar2)
{
}

ostream& operator<<(ostream& os, const LListJar& jar)
{
}
