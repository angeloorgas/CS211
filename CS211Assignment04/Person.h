/*This is the Person class header file.
  The data members in this class
  are inherited by the classes Husband, Wife and Child.
  
  Gilbert Duenas*/
  
#ifndef PERSON_H
#define PERSON_H
#include<string>
using namespace std;

class Person
{
 protected:
  //Declaration of protected variables.
  long SSN;
  string Fname;
  string Lname;
  
 public:
  //Declaration of default constructors.
  Person();
  Person(long num, string FN, string LN);
  ~Person();
  
  //Methods for setting and printing data.
  void setData(long num, string FN, string LN);
  void print() const;
};
#endif //PERSON_H

