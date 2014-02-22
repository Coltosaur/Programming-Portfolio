#include "BinaryHeap.h"
#include "Item.h"
#include "PQComp.h"
#include "RuntimeException.h"

using namespace std;

template<typename ElemType>
class PQHeap
{
   protected:
      typedef Item<ElemType> Item;
      typedef PQComp<ElemType> PQComp;
   private:
      BinaryHeap<Item, PQComp> T;
      static const int DEF_SIZE = 8;
   public:
       class EmptyPriorityQueue : public RuntimeException
       {
           public:
               EmptyPriorityQueue() : RuntimeException("The Priority Queue is empty.") {}
       };
      PQHeap(int size = DEF_SIZE) : T(size) { }
      bool isEmpty() const {return T.isEmpty();}
      int* insertItem(const int k, const ElemType& e, int& num_comps)
      {
	  int* pos = new int[1];
          Item tmp(k,e,pos);
          T.insert(tmp, num_comps);
	  cout << "position in the array: " << *pos << endl;
	  return pos;
      }
      const ElemType& minElement() throw(EmptyPriorityQueue)
      {
         if (T.isEmpty()) throw EmptyPriorityQueue();
         return T.findMin().getElem();
      }
      const int minKey() throw(EmptyPriorityQueue)
      {
         if (T.isEmpty()) throw EmptyPriorityQueue();
         return T.findMin().getKey();
      }
      void removeMin(int& num_comps) throw(EmptyPriorityQueue)
      {
         if (T.isEmpty()) throw EmptyPriorityQueue();
         T.deleteMin(num_comps);
      }
      void updateKey(int* pos, int k, int& num_comps)
      {
			T.updateKey(pos,k, num_comps);
			
      }
};
