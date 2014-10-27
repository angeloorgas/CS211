/*This is the Faculty class header.  
  It has several public methods for retrieving 
  and setting different attributes.*/
/* Gilbert Duenas*/

#ifndef FACULTY_H
#define FACULTY_H
using namespace std;
#include"Person.h"

//Faculty inherits from the Person class
class Faculty: public Person 
{
  //Declaration of protected variables.
 protected:
  float salary;  //Salary earned per year
  int yearOfExp;  //Number of years of experience
  long departId;  //Department ID
  //Static counter for objects created.
  static long nextFacultyId;
  
 public:
  //Declaration of default constructors.
  Faculty();
  Faculty(float thesalary,
	  int theyearOfExp,
	  long thedepartId);
  ~Faculty();
  
  //Methods for retrieving variables.
  float getSalary();
  int getYearOfExp();
  long getDepartId();
  
  //Methods for setting variables.
  void setSalary(float setsalary);
  void setYearOfExp(int setyearofexp);
  void setDepartId(long setdepartid);	
};
#endif //FACULTY_H
