/*************
Gilbert Duenas

This program allows the user to encrypt a file using a ROT method or cryptogram method.
Then it saves the encrypted text into a file.
Afterwards, the user can also select to decrypt the encrypted file.
**************/
#include<iostream>
#include<vector>
#include<string>
#include<fstream>
using namespace std;

class EncDec //Class for encryption and decryption
{
private:
  string keyFile;  //Data member to store cryptogram key.
  vector<string> originalFile;  //Data member to store files being opened and read.
  
public:
  EncDec(){};

  string filetoString(string filename);  //Method to open a file and copy into a string.
  vector<string> filetoVector(string filename);  //Method to open a file and copy into a vector.
  void vectortoFile(const vector<string>& V, string filename);  //Method for copying a vector to a file.
  void displayVector(const vector<string> V); //Method for displaying a vector.
  void EncryptROT();  //Encrypts data using the ROT method.
  void DecryptROT();  //Decrypts data using the ROT method.
  void EncryptCrypto();  //Encrypts data using the cryptogram method.
  void DecryptCrypto();  //Decrypts data using the cryptogram method.
};

//Method implementation.
string EncDec::filetoString(string filename)
{
  ifstream fin;
  fin.open(filename.data());  //Open a file and save it to a string.
  string word;
  
  if(!fin)
    {
      cout << "\nThe file could not be opened."
           << "\nPlease retry."
           << endl;
      exit(1);
    }
  else
    {
      while(!fin.eof())  //Data is saved to string keyFile until the end of file.
        keyFile.push_back(fin.get());
      fin.close();
    }
  return keyFile;
}

vector<string> EncDec::filetoVector(string filename)
{
  ifstream fin;
  fin.open(filename.data());  //Open a file and save it to a vector.
  string word;
  
  if(!fin)
    {
      cout << "\nThe file could not be opened."
	   << "\nPlease retry."
           << endl;
      exit(1);
    }
  else
    {
      while(fin>>word)  //Data is saved to the vector until the end of file.
	originalFile.push_back(word);
      fin.close();
    }
  return originalFile;
}

void EncDec::vectortoFile(const vector<string>& V, string filename)
{
  ofstream fout;
  fout.open(filename.data());  //Read a vector and save it to a file.
  string word;
  
  if(!fout)
    {
      cout << "\nThe file could not be opened."
           << "\nPlease retry."
           << endl;
      exit(1);
    }
  else
    {
      for(int i=0; i<V.size(); i++)  //Data is saved to the file until the end of the vector.
	{	
	  word = V[i];
	  fout << word << " ";
	}
      fout.close();
    }
  return;
}

void EncDec::displayVector(const vector<string> V)
{
  for(int i=0; i<V.size(); i++)  //Output vector V for confirmation.
    cout << V[i] <<" ";
  cout << endl;
}

void EncDec::EncryptROT()  //Encrypt using the ROT method.
{
  //Declare and initialize variables.
  int rot = 0;
  string filename = "original.txt";
  string save = "encrypt01.txt";
  
  cout << "\tEnter ROT number: ";
  cin >> rot;
  cout << endl;
  
  vector<string> V = filetoVector(filename);  //Load file from user input into vector V.
  vector<string> encVec;  //Declare vector encVec to store encrypted text.
  //Loop to read a single element and store it into string word.
  for(int i=0; i<V.size(); i++)  
    {
      string word = V[i];
      for(int j=0; j<word.size(); j++)  //Loop to read each element of string word.
	{
	  int value = word[j];
	  if(value>96 && value<123)  //Encrypt lowercase.
	    {
	      value += rot;
	      if(value>122)
		word[j] = value - 26;
	      else
		word[j] = value;
	    }
	  else if(value>64 && value<91)  //Encrypt uppercase.
	    {
	      value += rot;
	      if(value>90)
		word[j] = value - 26;
	      else
		word[j] = value;
	    }
	  else  //If value is not a letter, then skip.
	    {
	      word[j] = value;
	    }
	}
      string encryptWord = word;  //Store encrypted word in string encryptWord.  
      encVec.push_back(encryptWord);  //Store string encryptWord in vector encVec.
    }
  vectortoFile(encVec, save);  //Save encVec to file "encrypt01.txt".
  displayVector(encVec);  //Output vector decVec for confirmation.
  return;
}

void EncDec::DecryptROT()  //Decrypt using the ROT method.
{
  //Declare and initialize variables.
  int rot = 0;
  string filename = "encrypt01.txt";
  string save = "decrypt01.txt";
  
  cout << "\tEnter ROT number: ";  //Ask the user for input.
  cin >> rot;
  cout << endl;
  
  vector<string> V = filetoVector(filename);  //Load file "encrypt01.txt" into vector V.
  vector<string> decVec;  //Declare vector decVec to store decrypted text.
  //Loop to read a single element and store it into string word.
  for(int i=0; i<V.size(); i++)
    {
      string word = V[i];
      for(int j=0; j<word.size(); j++)  //Loop to read each element of string word.
	{
	  int value = word[j];
	  if(value>96 && value<123)  //Decrypt lowercase. 
	    {
	      value -= rot;
	      if(value<97)
		word[j] = value + 26;
	      else
		word[j] = value;
	    }
	  else if(value>64 && value<91)  //Decrypt uppercase.
	    {
	      value -= rot;
	      if(value<65)
		word[j] = value + 26;
	      else
		word[j] = value;
	    }
	  else  //If value is not a letter, then skip.
	    {	
	      word[j] = value;
	    }
	}	
      string decryptWord = word;  //Store decrypted word in string decryptWord.
      decVec.push_back(decryptWord);  //Store string decryptWord in vector decVec.
    }
  vectortoFile(decVec, save);  //Save decVec to file "decrypt01.txt".
  displayVector(decVec);  //Output vector decVec for confirmation.
  return;
}

void EncDec::EncryptCrypto()  //Encrypt using the cryptogram method.
{
  cout << endl;
  //Declare and initialize variables.
  string filename = "original.txt";
  string key = "key.txt";
  string save = "encrypt02.txt";
  
  string key2 = filetoString(key);  //Load the cryptogram into string key2.
  vector<string> V = filetoVector(filename);  //Load file from user input into vector V.
  vector<string> encVec;  //Declare vector encVec to store encrypted text.
  //Loop to read a single element and store it into string word.
  for(int i=0; i<V.size(); i++)
    {  
      string word = V[i];
      for(int j=0; j<word.length(); j++)  //Loop to read each element of string word.
	{
	  int value = word[j];
	  
	  if(value>96 && value<123)  //Encrypt lowercase.
	    {
	      char value2 = key2.at(value - 97);
	      word[j] = value2;
	    }
	  else if(value>64 && value<91)  //Encrypt uppercase.
	    {
	      char value2 = key2.at(value - 65);
	      word[j] = value2 - 32;
	    }
	  else  //If value is not a letter, then skip.
	    {
	      word[j] = value;
	    }
	}
      string encryptWord = word;  //Store encrypted word in string encryptWord.
      encVec.push_back(encryptWord);  //Store string encryptWord in vector encVec.
    }
  vectortoFile(encVec, save);//Save encVec to file "encrypt02.txt".
  displayVector(encVec);  //Output vector decVec for confirmation. 
  return;
}

void EncDec::DecryptCrypto()  //Decrypt using the cryptogram method.
{
  cout << endl;
  //Declare and initialize variables.
  string filename = "encrypt02.txt";
  string key = "key.txt";
  string save = "decrypt02.txt";
  
  string key2 = filetoString(key);  //Load the cryptogram into string key2.
  //Load a file into vector V and save it to vector decVec.
  vector<string> V = filetoVector(filename);
  vector<string> decVec;  //Declare vector decVec to store decrypted text.
  //Loop to read a single element and store it into string word.
  for(int i=0; i<V.size(); i++)
    {
      string word = V[i];
      for(int j=0; j<word.length(); j++)  //Loop to read each element of string word.
	{
	  int value = word[j];
	  
	  if(value>96 && value<123)  //Decrypt lowercase.
	    {
	      char value = word[j];
	      int value2 = key2.find(value, 0);
	      word[j] = value2 + 97;
	    }
	  else if(value>64 && value<91)  //Decrypt uppercase.
	    {
	      char value = word[j] + 32;
	      int value2 = key2.find(value, 0);
	      word[j] = value2 + 65;
	    }
	  else  //If value is not a letter, then skip.
	    {
	      word[j] = value;
	    }
	}
      string decryptWord = word;  //Store decrypted word in string decryptWord.	
      decVec.push_back(decryptWord);  //Store string decryptWord in vector decVec.
    }  
  vectortoFile(decVec, save);  //Save decVec to a file.
  displayVector(decVec);  //Output vector decVec for confirmation.
  return;
}

//Declare functions.
void menuLoop();
void menuEncrypt();
void menuDecrypt();

int main()
{
  menuLoop();  //Begin the program loop
  cout << "\nGoodbye.\n" << endl;
  return 0;
}

void menuLoop()
{
  bool exit = false;  //Declare a variable for exiting the program.
  int choice = 0;  //Initialize a variable for user input.
  
  while(exit!=true)  //Begin menu selection loop.
    {
      cout << "\n[1] Encrypt Data"  //Display user options.
	   << "\n[2] Decrypt Data"
	   << "\n[3] Exit"
	   << "\nPlease enter your selection: ";
      cin >> choice;  //Get user input.
      
      switch(choice)  //Switch for encryption or decryption.
	{
	case 1:  //Selection for encrypting data.
	  {
	    menuEncrypt();
	    break;
	  }
	case 2:  //Selection for decrypting data.
	  {
	    menuDecrypt();
	    break;	  
	  }
	case 3:  //Exit program.
	  {
	    exit = true; 
	    break;
	  }
	default:  //Display an error message if an integer is not entered.
	  {
	    cout << "\nInvalid selection, please try again." << endl;
	    break;
	  }	
	}	
    }	
  return;
}

void menuEncrypt()  //Submenu for performing encryptions.
{
  //Instantiate an object.
  EncDec Encrypt;
  int choice = 0;
  cout << "\n\t[1] Encrypt using ROT method"  //Display user options.
       << "\n\t[2] Encrypt using Cryptogram method"
       << "\n\t[3] Cancel"
       << "\n\tPlease enter your selection: ";
  cin >> choice;  //Get user input.
  
  switch(choice)  //Switch for ROT or Cryptogram encryption method
    {
    case 1:  //Call the function to encrypt using ROT method.
      {
	Encrypt.EncryptROT();
	break;
      }
    case 2:  //Call the function to encrypt using cryptogram method.
      {
	Encrypt.EncryptCrypto();
	break;
      }
    case 3:  //Cancel out of the menu.
      {
	break;
      }
    default:  //Display an error message if an integer is not entered.
      {
	cout << "\nInvalid selection, please try again." << endl;
	break;
      }
    }
  return;
}

void menuDecrypt()  //Submenu for performing decryptions.
{
  //Instantiate an object.
  EncDec Decrypt;
  int choice = 0;
  cout << "\n\t[1] Decrypt using ROT method"  //Display user options.
       << "\n\t[2] Decrypt using Cryptogram method"
       << "\n\t[3] Cancel"
       << "\n\tPlease enter your selection: ";
  cin >> choice;  //Get user input.
  
  switch(choice)  //Switch for ROT or Cryptogram decryption method.
    {
    case 1:  //Call the function to decrypt using the ROT method.
      {
	Decrypt.DecryptROT();
	break;
      }
    case 2:  //Call the function to decrypt using the cryptogram method.
      {
	Decrypt.DecryptCrypto();  
	break;
      }
    case 3:  //Cancel out of the menu.
      {
	break;
      }
    default:  //Display an error message if an integer is not entered.
      {
	cout << "\nInvalid selection, please try again." << endl;
	break;
      }
    }
  return;
}
