#include "UnsortedArray.h"
#include "Item.h"
#include "PQComp.h"
#include "RuntimeException.h"

using namespace std;

template<typename ElemType>
class PQArray
{
    protected:
        typedef Item<ElemType> Item;
        typedef PQComp<ElemType> PQComp;
    private:
        UnsortedArray<Item, PQComp> T;
    public:
        class EmptyPQArray : public RuntimeException
        {
            public:
                EmptyPQArray() : RuntimeException("The Priority Queue is empty.") {}
        };
        PQArray(int size = 0) : T(size) { }
        bool isEmpty() const {return T.isEmpty();}
        int* insertItem(const int k, const ElemType& e, int& num_comps)
        {
            int *pos = new int[1];
            Item tmp(k,e,pos);
            T.insert(tmp,num_comps);
            tmp.setPos(T.vec.size()-1);
            cout << "Position in the array: " << *pos << endl;
            return tmp.getPos();
        }
        void Display(){T.Display();}
        const ElemType minElement() throw(EmptyPQArray)
        {
           if (T.isEmpty()) throw EmptyPQArray();
           return T.findMin().getElem();
        }
        const int minKey() throw(EmptyPQArray)
        {
           if (T.isEmpty()) throw EmptyPQArray();
           return T.findMin().getKey();
        }
        void removeMin(int& num_comps) throw(EmptyPQArray)
        {
           if (T.isEmpty()) throw EmptyPQArray();
           T.deleteMin(num_comps);
        }
        void updateKey(int *pos, int k, int& num_comps)
        {
            T.updateKey(pos, k, num_comps);
        }
};
