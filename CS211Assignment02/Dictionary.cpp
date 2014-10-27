/*This program file contains the implementation of the Dictionary class.*/

#ifndef DICTIONARY_CPP
#define DICTIONARY_CPP

#include<fstream>

using namespace std;

#include "Dictionary.h"

bool Dictionary::failure = false;
bool Dictionary::success = true;

//Default constructor with constants initialized. 03/11/2013
Dictionary::Dictionary():maxWordsInDict(10000), maxWordsPerFile(100)
{
  //This routine sets the following values to the following attributes.
  totalWordsInDict = 0;	//Initialize variable to 0
  for(int i=0; i<25; i++) //Use a for-loop to initialize an array with 26 elements
    numOfWordsInFile[i] = 0; //Set each element to 0.
}

//------------------------------------------------------------------
//This second constructor was not used in the program. 03/11/2013
Dictionary::Dictionary(int dictMaxWords, int fileMaxWords):maxWordsInDict(dictMaxWords), maxWordsPerFile(fileMaxWords)
{
  /* This routine sets the following values to the following attributes
     maxWordsInDict = dictMaxWords;
     maxWordsPerFile = fileMaxWords;
     totalWordsInDict = 0;	
     numOfWordsInFile[0] = 0; referring to A.txt
     numOfWordsInFile[1] = 0; referring to B.txt
     numOfWordsInFile[25] = 0; referring to Z.txt
  */
}

//Destructor
Dictionary::~Dictionary(){}

//------------------------------------------------------------------
//Method for adding a word. 03/11/2013
bool Dictionary::AddAWord(string word) 
{
  //This variable contains the index of the word that will be added.
  int index = getIndex(word); 
  //This variable contains the filename where the word will be added.
  string fileName = getfileName(word); 
  /*This checks if the maximum number of words has been reached in both 
  the dictionary and the corresponding filename.*/
  maxCheck(word); 
  word = stringtoLower(word); //Convert the word to lowercase.
  
  if(SearchForWord(word)==success)  //Check if the word exists in the dictionary.
    {
      //If the word exists, inform the user which file it is located.
      cout << "The following word already exists in " << fileName << ": " << word  << endl;
      return failure; //AddAWord failure
    }
  else  //Add the word to the dictionary if it is not found.
    {
      totalWordsInDict++; //Increment the total number of words in the dictionary.
      numOfWordsInFile[index]++; //Increment the number of words for that file.
      
      ofstream fout; //Declare ofstream fout.
      if(!fout) //Check if the file exists.
	{
	  fileNotFound(fileName); //Display an error message if the file does not exist.
 	}
      fout.open(fileName.data(), ios::app);  //Append the word to the file.	
      fout << word << " " << endl; //Add the word to it with a space.
      fout.close(); //Close the file.
      return success; //AddAWord success
    }
}

//------------------------------------------------------------------
//Method for deleting a word. 03/11/2013
bool Dictionary::DeleteAWord(string word) 
{
  cout << "\nDELETING: " << word << endl;
  int deleteCount = 0;
  //This variable contains the index of the word that will be added.  
  int index = getIndex(word); 
  //This variable contains the filename where the word will be added.
  string fileName = getfileName(word); 
  //Method to open a file and copy into a vector.
  vector<string> originalFile = filetoVector(fileName);  
  
  ofstream fout; //Declare ofstream fout.
  if(!fout) //Check if the file exists.
    {
      fileNotFound(fileName); //Display an error message if the file does not exist.
      return failure;  
    }
  else
    {  
      fout.open(fileName.data());  //Read a vector and save it to a file.
      //Data is saved to the file until the end of the vector.
	  for(int i=0; i<originalFile.size(); i++)  
	{	
	  //Compare the element word to an element of vector originalFile.
	  if(word == originalFile[i]) 
	    {
	      originalFile[i] = " "; //Replace the element with a blank.
	      fout << originalFile[i]  << " "; //Save the variable to the file.
	      totalWordsInDict--; //Decrement totalWordsInDict.
	      numOfWordsInFile[index]--; //Decrement numOfWordsInFile.	
	      deleteCount++;
	      cout << endl;
	    }
	  else
	    {
	      fout << originalFile[i] << " "; //Save the string to the file.
	    }
	}
      fout.close(); //Close the file.
    }
  if(deleteCount==0)
    {	
      cout << "\'" << word << "\'" << " was not found and could not be deleted." << endl; //Inform the user nothing was deleted.
      return success;
    }
}

//------------------------------------------------------------------
//Methord for searching for a word. 03/11/2013
bool Dictionary::SearchForWord(string word) 
{
  //This variable contains the filename where the word will be added.
  string fileName = getfileName(word); 
  //Method to open a file and copy into a vector.
  vector<string> originalFile = filetoVector(fileName);  
  word = stringtoLower(word); //Convert the word to lowercase.
  //Data is saved to the file until the end of the vector.
  for(int i=0; i<originalFile.size(); i++)  
    {	
	  //Compare the element word to an element of vector originalFile.
      if(word == originalFile[i]) 
	{
	  return success;
	}
    }
  return failure; //SearchForWord failure
}

//------------------------------------------------------------------
//Method for printing a particular dictionary file. 03/11/2013
bool Dictionary::PrintAFileInDict(string fileName) 
{
  cout << "\nPRINTING: " << fileName << endl;
  int count = 0; //Counter for output.
  string word;
  ifstream fin;
  fin.open(fileName.data());  //Open a file 
  
  if(!fin)
    {
      fileNotFound(fileName);  //Check if the file exists.
      return failure;
    }
  else
    {
      while(fin>>word) //
	{ 
	  cout << word << " " ; 
	  count++; //Increment the counter.
	  
	  if(count>4) //Check if the counter is at 5
	    {
	      count = 0; //Reset the counter
	      cout << endl; //Output a new line.
	    }
	}
      cout << endl;
    }					
  return success; // PrintAFileInDict success
}

//------------------------------------------------------------------
//Method for spell checking a file. 03/11/2013
bool Dictionary::SpellChecking(string fileName) 
{
  cout << "SPELLCHECKING:" << endl;
  //Method to open a file and copy into a vector.
  vector<string> originalFile = filetoVector(fileName);  
  //Data is saved to the file until the end of the vector.
  for(int i=0; i<originalFile.size(); i++)  
    {	
	 //Compare an element of originalFile vector to the dictionary files.
      if(SearchForWord(originalFile[i])==failure) 
	{
	  //If the element is not found, it is incorrect and an error is displayed.
	  cout << "The following word is spelled incorrectly: "<< originalFile[i]  << endl; 
	}
    }
  return success;
}

//------------------------------------------------------------------
//Method for entering words from a file into the dictionary files. 03/11/2013
bool Dictionary::InsertWordsIntoDict(string fileName) 
{
  //Method to open a file and copy into a vector. 
  vector<string> originalFile = filetoVector(fileName);  
  //Data is saved to the file until the end of the vector.
  for(int i=0; i<originalFile.size(); i++)  
    {	
      AddAWord(originalFile[i]); //Add the word to the dictionary files.
    }
  return success;
}

//------------------------------------------------------------------
/*Method to check if the maximum number of words has been reached in both the 
dictionary and the corresponding filename. 03/11/2013*/
bool Dictionary::maxCheck(string word) 
{
  /*Check if the total number of words in the dictionary is greater than or equal 
  to the maximum.*/
  if(totalWordsInDict >= maxWordsInDict) 
    {
      cout << "Sorry, your entry has exceeded the maximum number of words in the dictionary." << endl;
      return failure;
    }
  
  int index = getIndex(word);
  /*Check if the number of words in the file is greater than the maximum words 
  per file.*/
  if((numOfWordsInFile[index]) > maxWordsPerFile) 
    {
      cout << "Sorry, your entry has exceeded the maximum number of words in the file." << endl;
      return failure;
    }
  return success;
}

//------------------------------------------------------------------
//Returns failure and displays an error message if file is not found. 03/11/2013
bool Dictionary::fileNotFound(string filename)
{
  //Display  a message.
  cout << ">>>>> THE FILE " << filename << " WAS NOT FOUND." << endl; 
}

//------------------------------------------------------------------
//Processes a transaction file. 03/11/2013
void Dictionary::ProcessTransactionFile() 
{
  string input, cmd, word, fileName; //Declare string variables for the transaction file.
  cout << "Please enter the name of your transaction file: ";
  cin >> input;
  
  ifstream fin;
  fin.open(input.data());
  
  if(!fin)
    {
      fileNotFound(input); //Display an error message if the file does not exist.
    }
  else
    {
      while(!fin.eof())
	{
	  fin >> cmd;
	  /*AddW adds a word into the dictionary using the AddAWord(string word)
	  function.*/
	  if(cmd=="AddW") 
	    {
	      fin >> word;  
	      AddAWord(word);
	    }
	  /*DeleteW removes a word from the dictionary using the DeleteAWord(string
	  word) function.*/
	  else if(cmd=="DeleteW") 
	    {
	      fin >> word; 
	      DeleteAWord(word);
	    }
	  /*InsertF adds words to the dictionary file using the 
	  InsertWordsIntoDict(string fileName) function.*/
	  else if( cmd=="InsertF") 
	    {
	      fin >> word;
	      InsertWordsIntoDict(word);
	    }
	  /*PrintF outputs words in a file using the PrintAFileInDict(string fileName)
	  function.*/
	  else if( cmd=="PrintF") 
	    {
	      fin >> fileName;
	      PrintAFileInDict(fileName);
	    }
	  /*SearchW searches for a word in the dictionary using the
	  SearchForWord(string word) function.*/
	  else if( cmd=="SearchW") 
	    {
	      fin >> word;
	      cout << "\nSEARCHING FOR: " << word << endl;
	      if(SearchForWord(word)==success)
		{
		  cout << "\'" << word << "\'" << " was found." << endl;
		}
	      else
		{
		  cout << "\'" << word << "\'" << " was not found." << endl;
		}
	    }
	  /*SpellCheck checks the spelling of a file using the SpellChecking(string fileName) function. */
	  else if( cmd=="SpellCheck") 
	    {
	      fin >> fileName;
	      SpellChecking(fileName);
	    }
	}
    }
}

//------------------------------------------------------------------
/*Method for determining the name of the file that needs to be accessed.
 03/11/2013*/
string Dictionary::getfileName(string word)
{
  string fileName = "#.txt"; // All files should be have ".txt" extension 
  fileName[0] = toupper(word[0]); // The # sign is replaced with appropriate uppercase letter. 
  return fileName;
}

//------------------------------------------------------------------
//Method to retrieve the index of the word that will be added. 03/11/2013
int Dictionary::getIndex(string word)
{
  char ch = word[0]; //Assign the first element of the word to ch.
  ch = toupper(ch); //Convert the character to uppercase. 
  int index = ch -'A'; //Calculate the index by 'subtracting 'A'.
  return index;
}

//------------------------------------------------------------------
//Method to open a file and copy into a vector. 03/11/2013
vector<string> Dictionary::filetoVector(string fileName) 
{
  vector<string> originalFile; //Declare a vectore to store string variables.
  
  ifstream fin;
  fin.open(fileName.data()); //Open a file and save it to a vector.
  string wordtoVector;
  
  if(!fin) //Check if the file exists.
    {
      fileNotFound(fileName); //Display an error message if the file does not exist.
    }
  else
    {
      while(fin>>wordtoVector) //Data is saved to the vector until the end of file.
	{
	  originalFile.push_back(wordtoVector); //Save the string into the vector.
	}
      fin.close(); //Close the file.
    }
  return originalFile; //Return the vector.
}

//------------------------------------------------------------------
 //Method to convert a string to lowercase. 03/11/2013
string Dictionary::stringtoLower(string word)
{
  for(int i=0; i<word.size(); i++)
    {
      char ch = word[i]; //Assign the first element of the word to ch.
      ch = tolower(ch); //Convert the character to lowercase.
      word[i] = ch; //Assign ch to the first element of word.
    }
  return word;
}
#endif //DICTIONARY_CPP

