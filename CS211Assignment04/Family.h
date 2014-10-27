/*This is the Family class header file.
  The data members in this class
  are connected in a linked list.
  Note that a pointer is defined.

  Gilbert Duenas*/
  
#ifndef FAMILY_H
#define FAMILY_H
#include<string>
using namespace std;
#include"Husband.h"
#include"Wife.h"
#include"Child.h"

class Family
{
 protected: 
  //Declaration of protected pointer.
  HusbandPtr top;
  
 public:
  //Declaration of default constructors.
  Family();
  ~Family();
  
  //Methods for adding and removing nodes.
  void AddHusband(long SSN, string Fname, string Lname);
  void RemoveHusband(long SSN);
  void AddWife(long SSN, string Fname, string Lname, long husbandSSN);
  void RemoveWife(long husbandSSN);
  void AddAChild(long SSN, string Fname, string Lname, long fatherSSN);
  void RemoveAChild(long FatherSSN, long childSSN);
  
  //Methods for printing and searching.
  void PrintAFamily(long fatherSSN);
  void PrintAllFamilies();
  bool SearchHusband(long SSN);
  bool SearchChild(long fSSN, long cSSN);
  
  //Method for opening a transaction file.
  bool ReadTransactionFile(string filename);
};
#endif //FAMILY_H

