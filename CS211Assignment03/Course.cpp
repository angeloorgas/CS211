/*This is the Course class implementation file.
  This defines the methods used.*/
// Gilbert Duenas

#ifndef COURSE_CPP
#define COURSE_CPP
#include<iostream>
#include"Course.h"

//Initialization of static data member.
long Course::nextCRN = 200; 

//Implementation of default constructors.
Course::Course()
{
  CRN = nextCRN;
  maxAvailableSeats = 0;
  name = "EMPTY"; 
  departId = 0;
  assignedSeats = 0;
  isTaughtBy = 0;
  nextCRN++;
}

Course::Course(string thename,
	       long thedepartId,
	       long theisTaughtBy,
	       int themaxAvailableSeats)
{
  CRN = nextCRN;
  name = thename;
  departId = thedepartId;
  assignedSeats = 0;
  isTaughtBy = theisTaughtBy;
  maxAvailableSeats = themaxAvailableSeats;
  nextCRN++;
}

Course::~Course(){}

//Implementation of methods for retrieving data.
long Course::getCRN()
{
  return CRN;
}

int Course::getMaxAvailableSeats()
{
  return maxAvailableSeats;
}

string Course::getName()
{
  return name;
}

long Course::getDepartId()
{
  return departId;
}

long Course::getAssignedSeats()
{
  return assignedSeats;
}

long Course::getIsTaughtBy()
{
  return isTaughtBy;
}

//Implementation for setting variables.
void Course::setCRN(long setCRN)
{
  CRN = setCRN;
}

void Course::setMaxAvailableSeats(int setmaxavailableseats)
{
  maxAvailableSeats = setmaxavailableseats;
}

void Course::setName(string setname)
{
  name = setname;
}

void Course::setDepartId(long setdepartid)
{
  departId = setdepartid;
}

void Course::setAssignedSeats(long setassignedseats)
{
  assignedSeats = setassignedseats;
}

void Course::setIsTaughtBy(long setistaughtby)
{
  isTaughtBy = setistaughtby;
}

//Implementation for incrementing and decrementing Assigned seats.
void Course::addAssignedSeat()
{
  assignedSeats++;
}

void Course::dropAssignedSeat()
{
  assignedSeats--;
}
#endif //COURSE_CPP
