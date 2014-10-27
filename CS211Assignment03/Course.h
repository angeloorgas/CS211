/*This is the Course class header.  
  It has several public methods for retrieving 
  and setting different attributes.*/

/* Gilbert Duenas
  */

#ifndef COURSE_H
#define COURSE_H
#include<string>
using namespace std;

class Course
{
  //Declaration of protected variables.
 protected:
  long CRN;  //Course Reference Number ID 
  int maxAvailableSeats;
  string name;
  long departId;
  long assignedSeats;
  long isTaughtBy;
  //Static counter for objects created.
  static long nextCRN;
  
 public:
  //Declaration of default constructors.
  Course();
  Course(string thename,
	 long thedepartId,
	 long theisTaughtBy,
	 int themaxAvailableSeats);
  ~Course();
  
  //Methods for retrieving variables.
  long getCRN();
  int getMaxAvailableSeats();
  string getName();
  long getDepartId();
  long getAssignedSeats();
  long getIsTaughtBy();
  
  //Methods for setting variables.
  void setCRN(long setCRN);
  void setMaxAvailableSeats(int maxavailableseats);
  void setName(string setname);
  void setDepartId(long departid);
  void setAssignedSeats(long setassignedseats);
  void setIsTaughtBy(long setistaughtby);
  void addAssignedSeat();
  void dropAssignedSeat();
};
#endif //COURSE_H
