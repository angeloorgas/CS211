/*This is the Person class implementation file.
  This defines the methods used.*/
// Gilbert Duenas

#ifndef PERSON_CPP
#define PERSON_CPP
#include<iostream>
#include"Person.h"

//Declaration of default constructors.
Person::Person()
{
  id = 0000;
  name = "EMPTY";
  email = "EMPTY";
  address = "EMPTY";
  dateOfBirth = "EMPTY";
  gender = "EMPTY";
}

Person::Person(long theId,
	       string theName,
	       string theEmail,
	       string theAddress,
	       string theDateOfBirth,
	       string theGender)
{
  id = theId;
  name = theName;
  email = theEmail;
  address = theAddress;
  dateOfBirth = theDateOfBirth;
  gender = theGender;
}

Person::~Person(){}

//Methods for retrieving variables.
long Person::getId()
{
  return id;
}

string Person::getName()
{
  return name;
}

string Person::getEmail()
{
  return email;
}

string Person::getAddress()
{
  return address;
}

string Person::getDateOfBirth()
{
  return dateOfBirth;
}

string Person::getGender()
{
  return gender;
}

//Methods for setting variables.
void Person::setId(long setid)
{
  id = setid;
}

void Person::setName(string setname)
{
  name = setname;
}

void Person::setEmail(string setemail)
{
  email = setemail;
}

void Person::setAddress(string setaddress)
{
  address = setaddress;
}

void Person::setDateOfBirth(string setdateOfBirth)
{
  dateOfBirth = setdateOfBirth;
}

void Person::setGender(string setgender)
{
  gender = setgender;
}

void Person::setMULTI(string setname, string setemail, string setaddress, 
    string setdateOfBirth, string setgender)
{
  name = setname;
  email = setemail;
  address = setaddress;
  dateOfBirth = setdateOfBirth;
  gender = setgender;
}
#endif // PERSON_CPP

