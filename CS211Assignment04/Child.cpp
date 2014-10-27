/*This is the Child class implementation file.
  This defines the methods used.*/

  // Gilbert Duenas

#ifndef CHILD_CPP
#define CHILD_CPP
#include<iostream>
#include"Child.h"

//Implementation of default constructors.
Child::Child()
{
  mySibling = NULL;
  dadSSN = 0;
}

/*The father's SSN is passed to this constructor
 to determine where the child is connected. */
Child::Child(long num, string FN, string LN, long num2)
{
  mySibling = NULL;
  setData(num, FN, LN);
  dadSSN = num2; //Father's SSN
}

Child::~Child(){}
#endif //CHILD_CPP
