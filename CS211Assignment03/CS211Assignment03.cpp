/*This is the Main program file.
A University object is created and a transaction file is processed.  

Gilbert Duenas
    */

#ifndef ASSIGNMENT03_CPP
#define ASSIGNMENT03_CPP
#include<iostream>
#include"University.h"

int main() 
{
  University csusm;
  csusm.ProcessTransactionFile("TransactionFile.txt");
  return 0;
}
#endif //ASSIGNMENT03_CPP

