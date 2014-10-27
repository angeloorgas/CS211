/*This is the Student class header.
  It has several public methods for retrieving
  and setting different attributes.*/
// Gilbert Duenas

#ifndef STUDENT_H
#define STUDENT_H
#include<string>
#include<vector>
using namespace std;
#include"Person.h"
#include"Course.h"

//Student inherits from the Person class
class Student: public Person
{
  //Declaration of protected variables.
 protected:
  int yearOfStudy;  //Number of years of study
  string major;  //Student's major
  long advisorId;  //Advisor's Faculty ID
  //A vector of Course is needed.
  vector<Course> coursesTaken; 
  //Static counter for objects created.
  static long nextStId;
  
  //Declaration of default constructors.
 public:
  Student();
  Student(int theyearOfStudy,
	  string themajor,
	  long theadvisorId);
  ~Student();
  
  //Methods for retrieving variables.
  int getYearOfStudy();
  string getMajor();
  long getAdvisorId();
  vector<Course> getCoursesTaken();
  
  //Methods for setting variables.
  void setYearOfStudy( int setyearofstudy);
  void setMajor( string setmajor);
  void setAdvisorId(long setadvisorid);
  void setCoursesTaken(Course courseObject);
  void setCoursesdropped(int i);
};
#endif //STUDENT_H
