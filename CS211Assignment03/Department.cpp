/*This is the Department class implementation file.
  This defines the methods used.*/
// Gilbert Duenas
#ifndef DEPARTMENT_CPP
#define DEPARTMENT_CPP
#include<iostream>
#include"Department.h"

//Initialization of static data member.
long Department::nextDepartId = 100;

//Implementation of default constructors.
Department::Department()
{
  deptId = nextDepartId;
  name = "EMPTY";
  location = "EMPTY";
  chairId  =  00;
  nextDepartId++;	
}

Department::Department(string thename,
		       string thelocation,
		       long thechairId)
{
  deptId = nextDepartId;
  name = thename;
  location = thelocation;
  chairId = thechairId;
  nextDepartId++;
}

Department::~Department(){}

//Implementation of methods for retrieving data.
long Department::getdeptId()
{
  return deptId;
}

string Department::getname()
{
  return name;
}

string Department::getlocation()
{
  return location;
}

long Department::getchairId()
{
  return chairId;
}

//Implementation for setting variables.
void Department::setId (long setdeptid)
{
  deptId = setdeptid;
}

void Department::setName (string setname)
{
  name = setname;
}

void Department::setLocation (string setlocation)
{
  location = setlocation;
}

void Department::setChairId(long setchairid)
{
  chairId = setchairid;
}
#endif //DEPARTMENT_CPP
