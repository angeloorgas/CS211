/*This is the main program file.
  It creates a Family object and calls a function
  to process a transaction file.

  Gilbert Duenas*/
  
#ifndef ASSIGNMENT04_CPP
#define ASSIGNMENT04_CPP
#include"Family.h"

int main()
{
  Family USAFamilies;
  //Not all methods are called by the transaction file.
  USAFamilies.ReadTransactionFile("text04.txt");
  return 0;
} 
#endif //ASSIGNMENT04_CPP
