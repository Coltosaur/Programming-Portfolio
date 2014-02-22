#include "RuntimeException.h"

template<typename ElemType, typename Comp>
class BinaryHeap
{
   private:
      Comp comp; //comp is a comparator class and comp(a,b) will compare a and b
      int curSize; //number of elements in heap
      ElemType *array; //dynamic heap array
      int length; //the length of the array
      static const int DEF_SIZE = 8;
      void getNewArray(int newSize)
      {
         array = new ElemType[newSize];
         length = newSize;
      }
   public:
       class EmptyHeap : public RuntimeException
       {
           public:
               EmptyHeap() : RuntimeException("The Heap is empty.") {}
       };
      BinaryHeap(int size = DEF_SIZE) //constructor
      {
         curSize = 0;
         getNewArray(size);
      }
      ElemType& findMin() throw(EmptyHeap)
      {
         if (isEmpty()) throw EmptyHeap();
         return array[0];
      }
      void checkSize(); 
      bool isEmpty() const {return curSize == 0;}
      void walkDown(int hole, int& num_comps);
      void walkUp(int hole, int& num_comps);
      void buildHeap();
      void insert(const ElemType& x, int& num_comps);
      void deleteMin(int& num_comps) throw(EmptyHeap);
      void updateKey(int *pos, int k, int& num_comps);
};

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::buildHeap()
{
    for (int i = (curSize-2)/2; i >= 0; i--) walkDown(i);
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::walkDown(int hole, int& num_comps)
{
    int child;
    ElemType key = array[hole];
    for ( ; 2*hole+1 < curSize; hole = child)
    {
       child = 2*hole+1;
       if (child != curSize-1 && (num_comps++,comp(array[child],array[child+1]) > 0))
          child++; //right child = 2*hole + 2
       if ((num_comps++,comp(key, array[child]) > 0))
       {
		   array[hole] = array[child];
		   *(array[hole].pos) = hole;
	   }
       else
          break;
    }
    array[hole] = key;
    *(key.pos) = hole;
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::walkUp(int hole, int& num_comps) //fixed it :D 
{
    ElemType x = array[hole];
    for ( ; hole > 0 && (num_comps++, comp(array[(hole-1)/2], x) > 0); hole = (hole-1)/2) 
	{
		array[hole] = array[(hole-1)/2];
        *(array[hole].pos) = hole;
    }
    array[hole] = x;
    *(x.pos) = hole;
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::checkSize()
{
    if (curSize == length) 
    {
        ElemType *oldArray = array;
        getNewArray(2*curSize);
        for (int i = 0; i < curSize; i++)
                array[i] = oldArray[i];
        delete [] oldArray;
    }
}

template<typename ElemType,typename Comp>
void BinaryHeap<ElemType, Comp>::insert(const ElemType& x, int& num_comps)
{ 
   checkSize();
   //walk up (establish heap order now)
   int hole = curSize++;
   for ( ; hole > 0 && (num_comps++,comp(array[(hole-1)/2], x) > 0); hole = (hole-1)/2)
   {
	   array[hole] = array[(hole-1)/2];
	   *(array[hole].pos) = hole;
   }
   array[hole] = x;
   *(array[hole].pos) = hole;
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::deleteMin(int& num_comps) throw(EmptyHeap)
{
    if (isEmpty()) throw EmptyHeap();
    array[0] = array[--curSize]; //decrease size
    walkDown(0, num_comps);
}

template<typename ElemType, typename Comp>
void BinaryHeap<ElemType, Comp>::updateKey(int *pos, int k, int& num_comps)
{
    array[*pos].setKey(k);
    walkDown(*pos, num_comps);
    walkUp(*pos, num_comps);
}

