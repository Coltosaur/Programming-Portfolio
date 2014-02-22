#include "RuntimeException.h"
#include <iostream>
#include "vector"

using namespace std;

template<typename ElemType, typename Comp>
class UnsortedArray
{
    private:
        Comp comp;
    public:
        vector<ElemType> vec;
        class EmptyVector : public RuntimeException
        {
            public:
                EmptyVector() : RuntimeException("The vector is empty.") {}
        };
        UnsortedArray(int size = 0){ }
        ElemType findMin() throw(EmptyVector);
        bool isEmpty() const {return vec.empty();}
        void insert(const ElemType& x, int& num_comps);
        void deleteMin(int& num_comps) throw(EmptyVector)
        { 
             int j=0;
             ElemType key = vec[0];
             for (int i = 0; i < vec.size(); i++)
             {
                 if ((num_comps++, comp(vec[i], key) < 0))
                 {
					 key = vec[i];
                     j = i;
                 }
             } 
             vec.erase(vec.begin()+j);

			 for (int i = 0; i < vec.size(); i++)
			 {
				 vec[i].setPos(i);
			 }
        }
        void Display()
        {
             for (int i=0;i<vec.size();i++)
             {  
                 cout<<endl<<"vec["<<i<<"]="<<vec[i].getElem()<<endl;
             }
        }
        void updateKey(int *pos, int k, int& num_comps);
};

template<typename ElemType, typename Comp>
void UnsortedArray<ElemType, Comp>::insert(const ElemType& x, int& num_comps)
{
    vec.push_back(x);
}

template<typename ElemType, typename Comp>
ElemType UnsortedArray<ElemType, Comp>::findMin() throw(EmptyVector)
{
    ElemType key = vec[0];
    int temp = 0;
    if (isEmpty()) throw EmptyVector();
    for (int i = 1; i < vec.size(); i++)
    {
        if (comp(vec[i], key) < 0)
        {
            key = vec[i];
            temp = i;
            
        }
    }
    return vec[temp];
}   

template<typename ElemType, typename Comp>
void UnsortedArray<ElemType, Comp>::updateKey(int *pos, int k, int& num_comps)
{
    vec[*pos].setKey(k);
}


