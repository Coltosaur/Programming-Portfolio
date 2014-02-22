#include <time.h> 
#include "vector_jar.h"
#include "llist_jar.h"
#include "jar.h"

using namespace std;

int main() {
   srand(time(0)); // for random marbles
   int jarflag;
   
   // if the user enter 1, then you should test vector jars;
   // otherwise, enter 2 to test list jars.
   cout << "Which kind of jar do you want to test? " << "(1: vector jar; 2: list jar)" << endl;
   cin >> jarflag;
   if(jarflag==1)
      {
         // jarflag = 1, do testing as instructed;
         // show a menu with choices to let the user to choose ways
         // to generate vector jar objects: VectorJar
         VectorJar jar1(10);
         cout<<"A jar with 10 randomly generated marbles was created"<<endl;
         cout << jar1 << "\n";
         VectorJar jar2(10);
         cout <<"Another jar was created with 10 marbles randomly generated." << endl;
         cout << jar2 << "\n";
         VectorJar jar3;
         cout << "A new third jar has been created based on those two random jars." << endl;
         jar3.merge(jar1,jar2);
         cout << jar3 << "\n";
         
         jar3.clear();
         cout << "The jar has been cleared to test function \"intersection\"" << endl;
         jar3.intersection(jar1,jar2);
         cout << jar3 << endl;
         
         
      }
    else if(jarflag==2)
      {
         // jarflag = 2, do testing as instructed;
         // show a menu with choices to let the user to choose
        
      }
   else
      {
         cout<<"wrong number entered"<<endl;
      }
   return 0;
}
