#ifndef VECTOR_JAR_H_
#define VECTOR_JAR_H_
#include <vector> 
#include "marble.h" 
#include "jar.h"

class VectorJar : public Jar { private:
   vector<Marble> vec; public:
   // constructors
   VectorJar();
   VectorJar(int len); // already finished for you in vector_jar.cpp
  // copy constructor:
  VectorJar(const VectorJar& jar);
  // assessors
  const Marble& get_elem(int i) const;
  // functions
  void add(const Marble& m);
  void remove(const Marble& m);
  Marble remove_any();
  void clear();
  bool is_empty() const;
  bool is_in_jar(const Marble& m) const;
  int marble_number() const;
  int marble_nsize(Marble:: Size s) const;
  int marble_ncolor(Marble:: Color c) const;
  void merge(const Jar& jar1, const Jar& jar2);
  void intersection(const Jar& jar1, const Jar& jar2);
  void difference(const Jar& jar1, const Jar& jar2);
};

ostream& operator<<(ostream& os, const VectorJar& jar);

#endif
