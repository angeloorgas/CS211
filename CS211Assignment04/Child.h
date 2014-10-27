/*This is the Child class header file.
  The data members in this class
  are connected in a linked list.
  Note that a pointer is defined.

  Gilbert Duenas*/
  
#ifndef CHILD_H
#define CHILD_H
using namespace std;
#include"Person.h"
class Child; //Forward declaration.
typedef Child* ChildPtr; //Pointer defined.

//Objects and methods are inherited from class Person
class Child: public Person
{
  //The class Family has access to Child's methods and variables
  friend class Family;
 protected:
  //Declaration of protected variables.
  ChildPtr mySibling;
  long dadSSN;
  
 public:
  //Declaration of default constructors.
  Child();
  Child(long num, string FN, string LN, long num2);
  ~Child();
};
#endif //CHILD_H
