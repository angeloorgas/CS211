/*This is the Person class implementation file.
  The methods in this class
  are inherited by the classes Husband, Wife and Child.
  
  Gilbert Duenas*/
  
#ifndef PERSON_CPP
#define PERSON_CPP
#include<iostream>
#include"Person.h"

//Implementation of default constructors.
Person::Person()
{
  SSN = 0;
  Fname = "First name";
  Lname = "Last name";
}

Person::Person(long num, string FN, string LN)
{
  SSN = num;
  Fname = FN;
  Lname = LN;
}

Person::~Person(){}

//Implementation for setting and printing data.
void Person::setData(long num, string FN, string LN)
{
  SSN = num;
  Fname = FN;
  Lname = LN;
}

void Person::print() const
{
  cout << "SSN:\t" << SSN << "\tName: " << Fname << " " << Lname << endl;
}
#endif //PERSON_CPP
