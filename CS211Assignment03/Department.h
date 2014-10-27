/*This is the Department class header file.
  It has several public methods for retrieving
  and setting different attributes.*/
// Gilbert Duenas

#ifndef DEPARTMENT_H
#define DEPARTMENT_H
#include<string>
using namespace std;

class Department
{
  //Declaration of protected variables.
 protected:
  long deptId;  //Department ID number
  string name;  //Department Name
  string location;  //Department Location
  long chairId;  //ID of the Department Chair
  static long nextDepartId;  //Counter for objects created
  
  //Declaration of default constructors.
 public:
  Department();
  Department(string thename,
	     string thelocation,
	     long thechairId);
  ~Department();
  
  //Methods for retrieving variables.
  long getdeptId();
  string getname();
  string getlocation();
  long getchairId();
  
  //Methods for setting variables.
  void setId (long setdeptid);
  void setName (string setname);
  void setLocation (string setlocation);
  void setChairId(long setchairid);
};
#endif //DEPARTMENT_H

