/*This is the Wife class header file.
  The data members in this class
  are connected in a linked list.
  Note that a pointer is defined.
  */
  // Gilbert Duenas
  
#ifndef WIFE_H
#define WIFE_H
using namespace std;
#include"Person.h"
class Child; //Forward class declaration
typedef Child* ChildPtr; //Pointer defined.

class Wife: public Person
{
  friend class Family;
 protected:
  //Declaration of protected variables.
  ChildPtr myChildren;
  long husbandSSN;
  
 public:
  //Declaration of default constructors.
  Wife();
  Wife(long num, string FN, string LN, long num2);
  ~Wife();
};
#endif //WIFE_H

