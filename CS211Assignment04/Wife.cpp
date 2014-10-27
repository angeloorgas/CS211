/*This is the Wife class implementation file.
  This defines the methods used.*/

    /*Gilbert Duenas*/
  
#ifndef WIFE_CPP
#define WIFE_CPP
#include<iostream>
#include"Wife.h"

//Implementation of default constructors.
Wife::Wife()
{
  myChildren = NULL;
  husbandSSN = 0;
}

Wife::Wife(long num, string FN, string LN, long num2)
{
  myChildren = NULL;
  setData(num, FN, LN);
  husbandSSN = num2;
}

Wife::~Wife(){}
#endif //WIFE_CPP
