/*This is the Person class header.  
  It has several public methods for retrieving 
  and setting different attributes.*/
// Gilbert Duenas

#ifndef PERSON_H
#define PERSON_H
#include<string>
using namespace std;

class Person
{
  //Declaration of protected variables.
 protected:
  long id;  //ID number
  string name;  //First name and last name
  string email; //Email Address
  string address;  //Street Address
  string dateOfBirth;  //Date of birth
  string gender;  //Gender
  
 public:
  //Declaration of default constructors.
  Person();
  Person(long theId,
	 string theName,
	 string theEmail,
	 string theAddress,
	 string theDateOfBirth,
	 string theGender);
  ~Person();
  
  //Methods for retrieving variables.
  long getId();
  string getName();
  string getEmail();
  string getAddress();
  string getDateOfBirth();
  string getGender();
  
  //Methods for setting variables.
  void setId(long setid);
  void setName(string setname);
  void setEmail(string setemail);
  void setAddress(string setaddress);
  void setDateOfBirth(string setdateOfBirth);
  void setGender(string setgender);
  void setMULTI(string setname, string setemail, string setaddress, 
    string setdateOfBirth, string setgender);
};
#endif // PERSON_H

