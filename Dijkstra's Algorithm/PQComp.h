template<typename ElemType>
class PQComp
{ 
   public:
          
     int operator() (const Item<ElemType>& e1, const Item<ElemType>& e2)
     {
        return e1.getKey() - e2.getKey();
     }
};
