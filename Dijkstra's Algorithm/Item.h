template<typename ElemType>
class Item
{
   private:
      int key;
      ElemType elem;
   public:
      int *pos;
      Item(const int k = 0, const ElemType& e = ElemType(), int *p = 0) : key(k), elem(e), pos(p) { } //constructor
      const int getKey() const {return key;}
      const ElemType& getElem() const {return elem;}
      void setKey(const int k) {key = k;}
      void setElem(const ElemType& e) {elem = e;}
      int* getPos() const {return pos;}
      void setPos(int i) {*pos = i;}
};


