/*This is the Husband class header file.
  The data members in this class
  are connected in a linked list.
  Note that two pointers are defined.
  
  Gilbert Duenas*/
  
#ifndef HUSBAND_H
#define HUSBAND_H
using namespace std;
#include"Person.h"
#include"Wife.h"
//Forward declaration of Husband and Wife
class Husband;
class Wife;
//Pointers defined for Husband and Wife
typedef Husband* HusbandPtr;
typedef Wife* WifePtr;

class Husband: public Person
{
  friend class Family;
 protected:
  //Declaration of protected variables.
  HusbandPtr nextFamily;
  WifePtr myWife;
  
 public:
  //Declaration of default constructors.
  Husband();
  Husband(long num, string FN, string LN);
  ~Husband();
};
#endif //HUSBAND_H

