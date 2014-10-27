/*This is the Family class implementation file.
  This defines the methods used and edits a linked list
  of Husbands, Wives, and Children.

  Gilbert Duenas*/
  
#ifndef FAMILY_CPP
#define FAMILY_CPP
#include<fstream>
#include<iostream>
#include"Family.h"

Family::Family()
{
  top = NULL;
}

Family::~Family(){}

/* This method adds a husband node. Before a node is created, several checks are made.
   First it checks if the node already exists. Then it checks if there is only one node. */
void Family::AddHusband(long SSN, string Fname, string Lname)
{
  if(SearchHusband(SSN))
    {cout << Fname << " was not added." << endl;
      return;}
  if(top==NULL)
    {
      HusbandPtr h = new Husband(SSN, Fname, Lname);
      h->nextFamily = top;
      top = h;
      cout << Fname << " was added." << endl;
      return;
    }
  HusbandPtr h = top;
  
  HusbandPtr hNew = new Husband(SSN, Fname, Lname);
  while(h->nextFamily!=NULL)
    {
      h = h->nextFamily;
    }
  hNew->nextFamily = h->nextFamily;
  h->nextFamily = hNew;	
  cout << Fname << " was added." << endl;
}

/* This method removes a husband node. 
   It checks if the node already exists
   and removes any wife nodes and child nodes as well. */
void Family::RemoveHusband(long SSN)
{
  if(!SearchHusband(SSN))
    {
      cout << SSN << " cannot be removed." << endl;
      return;
    }
  HusbandPtr temp, h;
  
  RemoveWife(SSN);
  if(SSN == top->SSN)
    {
      temp = top;
      top = top->nextFamily;
    }
  else
    {
      h = top;
      while(h->nextFamily->SSN != SSN)
	{
	  h = h->nextFamily;
	}
      temp = h->nextFamily;
      h->nextFamily = h->nextFamily->nextFamily;
    }
  cout << temp->Fname << " was removed." << endl;
  delete temp;
}

/* This method adds a wife node. Before a node is created, several checks are made.
   First it checks if the node already exists. Then it checks if there is only one node.  */
void Family::AddWife(long SSN, string Fname, string Lname, long husbandSSN)
{		
  if(!SearchHusband(husbandSSN))
    {
      cout << "The wife was not added. The husband does not exist" << endl;
      return;
    }
  HusbandPtr h = top;
  while(h->SSN != husbandSSN)
    {
      h = h->nextFamily;
    }
  if(h->myWife!=NULL)
    {
      cout << h->Fname << " is already married." << endl; 
      cout << Fname << " was not added." << endl;
      return;
    }
  WifePtr w = new Wife(SSN, Fname, Lname, husbandSSN);
  h->myWife = w;
  cout << w->Fname << " was added as the wife of " << h->Fname << "." << endl;
  return;
}

/* This method removes a wife node. It checks if the node already exists
   and removes any child nodes attached to it. */
void Family::RemoveWife(long husbandSSN)
{
  HusbandPtr h = top;
  if(!SearchHusband(husbandSSN))
    {
      cout << "The wife was not removed. The husband does not exist." << endl;
      return;
    }
  while(h->SSN != husbandSSN)
    {
      h = h->nextFamily;
    }
  if(h->myWife==NULL)
    {
      cout << "The wife was not removed. She does not exist." << endl;
      return;
    }
  WifePtr w = h->myWife;
  ChildPtr c, tempChild;
  c = w->myChildren;
  while(c!=NULL)
    {
      tempChild = c;
      c = c->mySibling;
      cout << tempChild->Fname << " was removed." << endl;
      delete tempChild;
    }
  cout << w->Fname << " was removed." << endl;
  h->myWife = NULL;
  delete w;
}

/* This method adds a child node. Before a node is created, several checks are made.
   First it checks if the node already exists. Then it checks if there is only one node. */
void Family::AddAChild(long SSN, string Fname, string Lname, long fatherSSN)
{
  HusbandPtr h = top;
  if(!SearchHusband(fatherSSN))
    {
      cout << "The child was not added. The father does not exist." << endl;
      return;
    }
  if(SearchChild(fatherSSN, SSN))
    {
      cout << "The child was not added. This person already exists." <<endl;
      return;
    }
  while(h->SSN != fatherSSN)
    {
      h = h->nextFamily;
    }
  if(h->myWife==NULL)
    {
      cout << "The child was not added. The mother does not exist." << endl;
      return;
    }
  WifePtr w = h->myWife;
  if(w->myChildren==NULL)
    {
      ChildPtr c = new Child(SSN, Fname, Lname, fatherSSN);
      w->myChildren = c;
      cout << c->Fname << " was added as a child of " 
	   << w->Fname << " and " << h->Fname << "." << endl;
      return;
    }
  else
    {
      ChildPtr c = w->myChildren;
      ChildPtr cNew = new Child(SSN, Fname, Lname, fatherSSN);
      while(c->mySibling!=NULL)
	{
	  c = c->mySibling;
	}
      cNew->mySibling = c->mySibling;
      c->mySibling = cNew;	
      cout << cNew->Fname << " was added as a sibling of " << c->Fname << "." << endl;
    }
}

/* This method removes a specific child node. It checks if the husband and wife nodes 
   exist ahead of the child node and returns the appropriate message if any 
   exceptions are discovered. */
void Family::RemoveAChild(long fatherSSN, long childSSN)
{
  HusbandPtr h = top;
  if(!SearchHusband(fatherSSN))
    {
      cout << "The child was not removed. The father does not exist." << endl;	
      return;
    }
  while(h->SSN != fatherSSN)
    {		
      h = h->nextFamily;		
    }
  if(h->myWife==NULL)
    {
      cout << "The child was not removed. The mother does not exist." << endl;
      return;
    }
  WifePtr w = h->myWife;
  if(w->myChildren==NULL)
    {
      cout << "The child was not removed. This couple has no children" << endl;
      return;
    }
  ChildPtr c, temp;
  c = w->myChildren;
  if(c->SSN==childSSN)
    {
      temp = w->myChildren;
      w->myChildren = c->mySibling;
      delete temp;
      return;
    }
  c = c->mySibling;
  while(c!=NULL)
    {
      if(c->SSN==childSSN)
	{
	  temp = c;
	  c = c->mySibling;
	  cout << temp->Fname << " was removed." << endl;
	  delete temp;
	  return;
	}
      c = c->mySibling;
    }
  cout << "The child does not exist." << endl;
}

/* This searches for a specific SSN and 
   prints out a single family in the link list, 
   including the wife and any children if they exist. */
void Family::PrintAFamily(long fatherSSN){
  HusbandPtr h = top;
  if(!SearchHusband(fatherSSN))
    {
      cout << "The family does not exist." << endl;
      return;
    }
  else
    {
      cout << "\n**************BEGIN PRINT SINGLE FAMILY**************" << endl;
      while(h->SSN != fatherSSN)
	{
	  h = h->nextFamily;
	}
      cout << "Husband/Father" << endl;
      h->print();  
      if(h->myWife!=NULL)
	{
	  cout << "Wife/Mother" << endl;
	  h->myWife->print();
	  ChildPtr c = h->myWife->myChildren;
	  int counter2 = 1;
	  while(c!=NULL)
	    {
	      cout << "Child " << counter2 << endl;
	      c->print();
	      c = c->mySibling;
	      counter2++;
	    }
	}  
      cout << "*********************END PRINT*********************" << endl;
    }
}

/* This prints out the entire family listing,
   including the wife and any children if they exist.*/
void Family::PrintAllFamilies()
{
  cout << "\n**************BEGIN PRINT ALL FAMILIES**************";
  int counter = 1;
  HusbandPtr h = top;
  while(h!=NULL)
    {
      cout << "\nFamily " << counter 
	   << "\n-----------------------------------------"
	   << "\nHusband/Father" << endl;
      h->print();  
      WifePtr w = h->myWife;
      if(w != NULL)
	{
	  cout << "Wife/Mother" << endl;
	  w->print();
	  ChildPtr c = w->myChildren;
	  int counter2 = 1;
	  while(c!=NULL)
	    {
	      cout << "Child " << counter2 << endl;
	      c->print();
	      c = c->mySibling;
	      counter2++;			
	    }
	}
      h = h->nextFamily;
      counter++;
    }
  cout << "*********************END PRINT*********************" << endl;
}

//This performs a search based on the Husband's SSN
bool Family::SearchHusband(long SSN)
{
  HusbandPtr h = top;
  while(h!=NULL)
    {
      if(h->SSN == SSN)
	{
	  cout << "\nHusband SSN " << SSN << " was found." << endl;
	  return true;
	}
      h = h->nextFamily;    
    }
  cout << "\nHusband SSN " << SSN << " was not found." << endl;
  return false;
}

/* This performs a search based on the Child's SSN
   and the father's SSN*/
bool Family::SearchChild(long fSSN, long cSSN)
{
  HusbandPtr h = top;  
  while(h!=NULL)
    {
      WifePtr w = h->myWife;
      if(w != NULL)
	{
	  ChildPtr c = w->myChildren;
	  while(c!=NULL)
	    {
	      if(c->SSN==cSSN)
		{
		  cout << "\nChild SSN " << cSSN << " was found." << endl;
		  return true;
		}
	      c = c->mySibling;
	    }
	}
      h = h->nextFamily;
    }
  cout << "\nChild SSN " << cSSN << " was not found" << endl;
  return false;
}

//This processes a transaction file.
bool Family::ReadTransactionFile(string filename){
  //Declare string variable for the transaction file.
  string cmd; 
  
  //Declare variables for person.
  long SSN, SSN2;
  string Fname, Lname;
  
  //Open the transaction file and process commands one by one. 
  //Return success when complete.
  cout << "\nProcessing transaction file....\n\n";
  ifstream fin;
  fin.open(filename.data());
  if(!fin)
    {
      //Display an error message if the file does not exist.
      cout << "The file was not found." << endl;
      return false;
    }
  else
    {
      while(!fin.eof())
	{
	  fin >> cmd;
	  //Methods are called based on the input from the file.
	  if(cmd=="AddHusband") 
	    {	
	      fin >> SSN >> Fname >> Lname;
	      AddHusband(SSN, Fname, Lname);
	    }
	  else if(cmd=="RemoveHusband") 
	    {
	      fin >> SSN;
	      RemoveHusband(SSN);
	    }
	  else if(cmd=="AddWife") 
	    {
	      fin >> SSN >> Fname >> Lname >> SSN2;
	      AddWife(SSN, Fname, Lname, SSN2);
	    }
	  else if(cmd=="RemoveWife") 
	    {
	      fin >> SSN;
	      RemoveWife(SSN);
	    }
	  else if(cmd=="AddAChild") 
	    {
	      fin >> SSN >> Fname >> Lname >> SSN2;
	      AddAChild(SSN, Fname, Lname, SSN2);
	    }
	  else if(cmd=="RemoveAChild") 
	    {
	      fin >> SSN >> SSN2;
	      RemoveAChild(SSN, SSN2);
	    }
	  else if(cmd=="PrintAFamily") 
	    {
	      fin >> SSN;
	      PrintAFamily(SSN);
	    }
	  else if(cmd=="PrintAllFamilies")		
	    {
	      PrintAllFamilies();
	    }
	  else if(cmd=="SearchHusband") 
	    {
	      fin >> SSN;
	      SearchHusband(SSN);
	    }
	  else if(cmd=="SearchChild") 
	    {
	      fin >> SSN >> SSN2;
	      SearchChild(SSN, SSN2);
	    }
	}
      fin.close();
    }
  return true;
}
#endif //FAMILY_H

