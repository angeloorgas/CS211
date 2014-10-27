/*This is the Faculty class implementation file.
  This defines the methods used.*/
// Gilbert Duenas

#ifndef FACULTY_CPP
#define FACULTY_CPP
#include<iostream>
#include"Faculty.h"

//Initialization of static data member.
long Faculty::nextFacultyId = 600;

//Implementation of default constructors.
Faculty::Faculty()
{
  setId(nextFacultyId);
  salary = 0000.0;
  yearOfExp = 00;
  departId = 000;
  nextFacultyId++;
}

Faculty::Faculty(float thesalary,
		 int theyearOfExp,
		 long thedepartId)
{
  setId(nextFacultyId);
  salary = thesalary;
  yearOfExp = theyearOfExp;
  departId = thedepartId;
  nextFacultyId++;
}

Faculty::~Faculty(){}

//Implementation of methods for retrieving data.
float Faculty::getSalary()
{
  return salary;
}

int Faculty::getYearOfExp()
{
  return yearOfExp;
}

long Faculty::getDepartId()
{
  return departId;
}

//Implementation for setting variables.
void Faculty::setSalary(float setsalary)
{
  salary = setsalary;
}

void Faculty::setYearOfExp(int setyearofexp)
{
  yearOfExp = setyearofexp;
}

void Faculty::setDepartId(long setdepartid)
{
  departId = setdepartid;
}
#endif //FACULTY_CPP

