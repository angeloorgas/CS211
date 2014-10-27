/*This header file declares a class Dictionary. The Dictionary has functions to add
 words, delete words, search for words, print a file, and spell check a file. There are
 also several smaller functions that perform tasks for other functions.*/
//Gilbert Duenas

#ifndef DICTIONARY_H
#define DICTIONARY_H

#include<iostream>
#include<string>
#include<vector>

using namespace std;

class Dictionary
{
 protected:
  static bool failure; //Return false if failure.
  static bool success; //Return true if success.
  const int maxWordsInDict; //Maximum number of words for the dictionary.
  const	int maxWordsPerFile; //Maximum number of words for a file.
  int totalWordsInDict; //Total number of words in the dictionary.
  int numOfWordsInFile[26]; //Total number of words in a given dictionary file.
  
 public:
  Dictionary(); //Default constructor.
  //Second constructor with parameters.
  Dictionary(int dictMaxWords, int fileMaxWords); 
  ~Dictionary(); //Destructor
  bool AddAWord(string word); //Method for adding a word.
  bool DeleteAWord(string word); //Method for deleting a word.
  bool SearchForWord(string word); //Methord for searching for a word.
  //Method for printing a particular dictionary file.
  bool PrintAFileInDict(string fileName); 
  bool SpellChecking(string fileName); //Method for spell checking a file.
  //Method for entering words from a file into the dictionary files.
  bool InsertWordsIntoDict(string fileName); 
  /*Method to check if the maximum number of words has been reached in both the
  dictionary and the corresponding filename.*/
  bool maxCheck(string word); 
  //Returns failure and displays an error message if file is not found.
  bool fileNotFound(string filename);  
  void ProcessTransactionFile(); //Processes a transaction file.		
  //Method for determining the name of the file that needs to be accessed.
  string getfileName(string word); 
  //Method to retrieve the index of the word that will be added. 
  int getIndex(string word); 
  //Method to open a file and copy into a vector.
  vector<string> filetoVector(string fileName);  
  string stringtoLower(string word); //Method to convert a string to lowercase.
};
#endif //DICTIONARY_H

