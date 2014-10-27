/*This is a dictionary program using a single class with a cpp and header file. 
This is the main program file which instantiates an object of Dictionary, then calls 
a function to process a transaction file. The user is asked to input the name of the
transaction file. Several actions are performed and output is displayed based on
 those actions within the transaction file.*/
//Gilbert Duenas
#ifndef MAIN_CPP
#define MAIN_CPP

#include "Dictionary.h"

int main()
{
  Dictionary  data; //Instantiate an object.
  data.ProcessTransactionFile(); //Call the ProcessTransactionFile method.
  return 0;
}
/*
  Other Comments:
  1)	Do not worry about punctuations. Your program should only consider words and ignore all punctuations.
  2) 	All words should be in lower case before it is placed in the dictionary
  3)	Do not write 26 statements to open/close A.txt to Z.txt files.
  4)	When a file name is a variable, you need to open it as follows:  fin.open(fileName.data());
*/
#endif //MAIN_CPP

