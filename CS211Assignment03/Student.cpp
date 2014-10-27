/*This is the Student class implementation file.
  This defines the methods used.*/
// Gilbert Duenas
#ifndef STUDENT_CPP
#define STUDENT_CPP
#include<iostream>
#include"Student.h"

//Initialization of static data member.
long Student::nextStId = 500;

//Implementation of default constructors.
Student::Student()
{
  setId(nextStId);
  yearOfStudy = 0;
  major = "MAJOR";
  advisorId = 000;
  nextStId++;
}

Student::Student(int theyearOfStudy,
		 string themajor,
		 long theadvisorId)
{
  setId(nextStId);
  yearOfStudy = theyearOfStudy;
  major = themajor;
  advisorId = theadvisorId;
  nextStId++;
}

Student::~Student(){}

//Methods for retrieving variables.
int Student::getYearOfStudy()
{
  return yearOfStudy;
}

string Student::getMajor()
{
  return major;
}

long Student::getAdvisorId()
{
  return advisorId;
}

vector<Course> Student::getCoursesTaken()
{
  return coursesTaken;
}

//Methods for setting variables.
void Student::setYearOfStudy( int setyearofstudy)
{
  yearOfStudy = setyearofstudy;
}

void Student::setMajor( string setmajor)
{
  major = setmajor;
}

void Student::setAdvisorId(long setadvisorid)
{
  advisorId = setadvisorid;
}

void Student::setCoursesTaken(Course courseObject)
{
  coursesTaken.push_back(courseObject);
}

void Student::setCoursesdropped(int i)
{
  coursesTaken.erase(coursesTaken.begin() + i);
}
#endif //STUDENT_CPP

