#ifndef JAR_H_
#define JAR_H_
#include "marble.h"

class Jar { public:
   // interface functions
   virtual const Marble& get_elem(int i) const = 0;
   virtual void add(const Marble& x) = 0;
   virtual bool is_in_jar(const Marble& x) const = 0;
   virtual void remove (const Marble& x) = 0;
   virtual Marble remove_any()=0;
   virtual void clear() = 0;
   virtual int marble_number() const =0;
   virtual int marble_nsize(Marble:: Size s) const =0;
   virtual int marble_ncolor(Marble:: Color c) const =0;
   virtual bool is_empty() const = 0;
   virtual void merge(const Jar& jar1, const Jar& jar2) = 0;
   virtual void intersection(const Jar& jar1, const Jar& jar2) = 0;
   virtual void difference(const Jar& jar1, const Jar& jar2) = 0;
};

#endif
