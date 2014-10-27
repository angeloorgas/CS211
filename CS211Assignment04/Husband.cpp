/*This is the Husband class implementation file.
  This defines the methods used.*/

  //Gilbert Duenas
  
#ifndef HUSBAND_CPP
#define HUSBAND_CPP
#include<iostream>
#include"Husband.h"

//Implementation of default constructors.
Husband::Husband()
{
  nextFamily = NULL;
  myWife = NULL;
}

Husband::Husband(long num, string FN, string LN)
{
  nextFamily = NULL;
  myWife = NULL;
  setData(num, FN, LN);
}

Husband::~Husband(){}
#endif //HUSBAND_CPP
