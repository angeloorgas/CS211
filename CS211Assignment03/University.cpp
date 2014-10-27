/*This is the University class implementation file.
  This defines the methods used.*/
// Gilbert Duenas

#ifndef UNIVERSITY_CPP
#define UNIVERSITY_CPP
#include<iostream>
#include <fstream>
#include"University.h"

bool University::failure = false;
bool University::success = true;

//Default constructors
University::University(){}
University::~University(){}

//Implementation of methods for creating and removing objects.
bool University::CreateNewDepartment(string depName, string depLoc, 
				     long depChairId)
{
  //If the depChairId is 0, it means the chair is not known yet.
  if(depChairId != 0)
    {
      //Check if the depChairId passed to this method is a valid existing faculty.
      bool valid = checkDepChair(depChairId); 
      if(!valid)
	{
	  //Print appropriate message and return failure if the chair is not valid
	  cout << "Chair ID " << depChairId << " is invalid." << endl;
	  return failure;
	}
    }
  //Add the new department to the Departments vector
  Department newDept(depName, depLoc, depChairId);
  Departments.push_back(newDept);
  return success;
}

bool University::RemoveADepartment(long deptId)
{
  //Check if the depId passed to this method is a valid existing department id. 
  //If not, return failure;
  bool valid =  checkDeptId(deptId);
  if(!valid)
    {
      cout << "Cannot remove." << endl;
      return failure;
    }
  //Then search if the department has no faculty, courses, or students.
  bool validFD = checkFacultyDept(deptId);
  bool validC = checkCourseDept(deptId);
  bool validM = checkStudentMajor(getDeptName(deptId));
  if(validFD || validC || validM)
    {
      cout << "Department " << deptId << " has existing attributes." << endl;
      cout << "Cannot remove." << endl;
      return failure;
    }
  //Remove the department from the Departments vector after checking those items.
  OKremoveDept(deptId);
  return success;
}

bool University::CreateNewStudent(string sName, string sEmail, string sAddress, 
				  string sDateOfBirth, string sGender, 
				  int sYearOfStudy, string sMajor, long sAdvisorId)
{
  //If the sMajor or sAdvisorId is 0,
  //then the student has not chosen a major or been assigned a faculty advisor. 
  if(sMajor !=  "0" || sAdvisorId !=0)
    {
      //Check if the faculty and major are valid. Return failure if invalid.
      bool validF = checkFacultyId(sAdvisorId);
      bool validM = checkDeptName(sMajor);
      if(!validF || !validM)
	{ 
	  cout << "Cannot create student." << endl;
	  return failure;
	}
    }
  //Otherwise create the student.
  Student newStudent(sYearOfStudy, sMajor, sAdvisorId);
  newStudent.setMULTI(sName, sEmail, sAddress, sDateOfBirth, sGender);
  Students.push_back(newStudent);
  return success;
}

bool University::RemoveAStudent(long sStId)
{
  //Check if the student ID is valid.
  bool validSID = checkStudentId(sStId);
  if(!validSID)
    {
      cout << "Student " << sStId << " was not removed." << endl;
      return failure;
    }
  //Drop the courses taken by the student.
  for(int i = 0; i < Students.size(); i++)
    {
      if(Students[i].Person::getId() == sStId)
	{
	  vector<Course> listCourse = Students[i].getCoursesTaken();
	  for(int j = 0; j < listCourse.size(); j++)
	    {
	      long courseID = listCourse[j].getCRN();
	      DropACourseForAStudent(courseID, sStId);
	    }
	}
    }
  //Remove the student.  
  OKremoveStudent(sStId);
  return success;
}

bool University::CreateNewCourse(string cName, long cDepId, 
				 long cTaughtBy, int cMaxSeat)
{
  //If cTaughtBy is 0, then no faculty is assigned to teach this course.
  if(cTaughtBy != 0)
    {
      //Check if faculty ID and department ID are valid.
      bool validF = checkFacultyId(cTaughtBy);
      bool validD = checkDeptId(cDepId);
      if(!validF || !validD)
	{
	  cout << "Cannot create course." << endl;
	  return failure;
	}
    }
  //Create the course.
  Course newCourse(cName, cDepId, cTaughtBy, cMaxSeat);
  Courses.push_back(newCourse);
  return success;
}

bool University::RemoveACourse(long cCRN)
{
  //Check if the CRN is valid.
  bool validCRN = checkCourseCRN(cCRN);
  if(!validCRN)
    {
      cout << "CRN " << cCRN << " could not be removed." << endl;
      return failure;
    }
  //Check the Students vector if any students are taking the course.
  for(int i = 0; i < Students.size(); i++)
    {
      vector<Course> listCourse = Students[i].getCoursesTaken();
      for(int j = 0; j < listCourse.size(); j++)
	{
	  if(listCourse[j].getCRN() == cCRN)
	    return failure;
	}
    }
  //Remove the course.
  OKremoveCourse(cCRN);
  return success;
}

bool University::CreateNewFaculty(string fName, string fEmail, string fAddress, string fDateOfBirth, string fGender,
				  float fSalary, int fYearOfExp, long fDepId)
{
  //Check if fDepId is a valid department id. 
  bool valid =  checkDeptId(fDepId);
  if(!valid)
    {
      cout << "Cannot create this faculty member." << endl;
      return failure;
    }
  //Create the faculty if valid. 
  Faculty newFaculty(fSalary, fYearOfExp, fDepId);
  newFaculty.setMULTI(fName, fEmail, fAddress, fDateOfBirth, fGender);
  Faculties.push_back(newFaculty);
  return success;
}

bool University::RemoveAFaculty(long fFactId)
{
  //Check if this is a valid faculty ID.
  bool validFID = checkFacultyId(fFactId);
  if(!validFID)
    {
      cout << "Faculty " << fFactId << " could not be removed." << endl;
      return failure;
    }
  //Check the Courses vector if faculty is teaching a course.
  for(int i = 0; i < Courses.size(); i++)
    {
      if(Courses[i].getIsTaughtBy() == fFactId)
	{
	  cout << "Faculty " << fFactId << " is teaching and could not be removed." << endl;
	  return failure;
	}
    }
  //Check the Students vector if faculty is advising a student.
  for(int i = 0; i < Students.size(); i++)
    {
      if(Students[i].getAdvisorId() == fFactId)
	{
	  cout << "Faculty " << fFactId << " is advising and could not be removed." << endl;
	  return failure;
	}
    }
  //Check the Departments vector if the faculty is Chair.
  for(int i = 0; i < Departments.size(); i++)
    {
      if(Departments[i].getchairId() == fFactId)
	{
	  cout << "Faculty " << fFactId << " is Chairing and could not be removed." << endl;
	  return failure;
	}
    }
  //Remove the faculty if no failures.
  OKremoveFaculty(fFactId);
  return success;
}

//Implementation of methods for listing objects by specific parameters.
bool University::ListCoursesTaughtByFaculty(long facultyId)
{
  //Check if a valid faculty ID.
  bool valid = checkFacultyId(facultyId);
  if(!valid)
    {
      cout << "Cannot list the courses for faculty " << facultyId << "." << endl;
      return failure;
    }
  //Print the appropriate faculties if valid and return success.
  cout << "\nCOURSES TAUGHT BY " << facultyId << "------------------------" 
       << "\nCourse ID\t" << "Course Name" << endl;
  for(int i = 0; i < Faculties.size(); i++)
    {
      if(Courses[i].getIsTaughtBy() == facultyId)
	{
	  cout << Courses[i].getCRN() << "\t\t" << Courses[i].getName() <<endl;
	}
    }
  cout << "---------------------------------------------\n" << endl;
  return success;
}

bool University::ListCoursesTakenByStudent(long studentId)
{
  //Check if a valid student ID.
  bool valid = checkStudentId(studentId);
  if(!valid)
    {
      cout << "Cannot list the courses for student " << studentId << "." << endl;
      return failure;
    }
  //Print the appropriate faculties if valid and return success.
  cout << "\nCOURSES TAKEN BY " << studentId << "-------------------------" 
       << "\nCourse ID\t" << "Course Name" << endl;
  for(int i = 0; i < Students.size(); i++)
    {
      if(Students[i].Person::getId() == studentId)
	{
	  vector<Course> listCourse = Students[i].getCoursesTaken();
	  for(int j = 0; j < listCourse.size(); j++)
	    {
	      cout << listCourse[j].getCRN() << "\t\t" << listCourse[j].getName() <<endl;
	    }
	}
    }
  cout << "---------------------------------------------\n" << endl;
  return success;
}

bool University::ListFacultiesInDepartment(long departId)
{
  //Check that the departId passed to this method is a valid existing department id. 
  bool valid =  checkDeptId(departId);
  //If invalid, print appropriate message and return failure.
  if(!valid)
    {
      cout << "Cannot list the faculties in department " << departId << "." << endl;
      return failure;
    }
  //Print the appropriate faculties if valid and return success.
  cout << "\nFACULTIES IN DEPARTMENT " << departId << "------------------" 
       << "\nFaculty ID\t" << "Name" << endl;
  for(int i = 0; i < Faculties.size(); i++)
    {
      if(Faculties[i].getDepartId() == departId)
	{
	  cout << Faculties[i].Person::getId() << "\t\t" 
	       << Faculties[i].Person::getName() <<endl;
	}
    }
  cout << "---------------------------------------------\n" << endl;
  return success;
}

bool University::ListStudentsOfAFaculty(long facultyId)
{
  //Check that the facultyId passed to this method is a valid existing faculty id. 
  bool valid = checkFacultyId(facultyId);
  if(!valid)
    {
      cout << "Cannot list the students for faculty " << facultyId << "." << endl;
      return failure;
    }
  cout << "\nSTUDENTS OF FACULTY " << facultyId << "----------------------" 
       << "\nStudent ID\t" << "Name" << endl;
  for(int i = 0; i < Students.size(); i++)
    {
      if(Students[i].getAdvisorId() == facultyId)
	{
	  cout << Students[i].Person::getId() << "\t\t" 
	       << Students[i].Person::getName() <<endl;
	}
    }
  cout << "---------------------------------------------\n" << endl;
  return success;
}

bool University::ListCoursesOfADepartment(long departId)
{
  //Check if a valid Department ID.
  bool valid = checkDeptId(departId);
  if(!valid)
    {
      cout << "Cannot list the courses for department " << departId << "." << endl;
      return failure;
    }
  //Print the appropriate departments if valid and return success.
  cout << "\nCOURSES IN DEPARTMENT " << departId << "--------------------" 
       << "\nCourse ID\t" << "Course Name" << endl;
  for(int i = 0; i < Courses.size(); i++)
    {     
      if(Courses[i].getDepartId() == departId)
	{
	  cout << Courses[i].getCRN() << "\t\t" << Courses[i].getName() <<endl;
	}
    }
  cout << "---------------------------------------------\n" << endl;
  return success;
}

bool University::ListDepartments()
{  //Print the departments in the Department vector.
  cout << "\nDEPARTMENT LISTING---------------------------" 
       << "\nID\t" << "Name" << endl;
  for(int i = 0; i < Departments.size(); i++)
    {
      cout << Departments[i].getdeptId() << "\t" << Departments[i].getname() <<endl;
    }
  cout << "---------------------------------------------\n" << endl;
  return success;
}

bool University::ListStudents()
{  //Print the students in the Student vector.
  cout << "\nSTUDENT LISTING------------------------------" 
       << "\nID\t" << "Name" << endl;
  for(int i = 0; i < Students.size(); i++)
    {
      cout << Students[i].Person::getId() << "\t" << Students[i].Person::getName() <<endl;
    }
  cout << "---------------------------------------------\n" << endl;
  return success;
}

bool University::ListCourses()
{  //Print the courses in the Courses vector.
  cout << "\nCOURSE LISTING-------------------------------" 
       << "\nCRN\t" << "Name" << endl;
  for(int i = 0; i < Courses.size(); i++)
    {
      cout << Courses[i].getCRN() << "\t" << Courses[i].getName() <<endl;
    }
  cout << "---------------------------------------------\n" << endl;
  return success;
}

bool University::ListFaculties()
{  //Print the faculties in the faculties vector.
  cout << "\nFACULTY LISTING------------------------------" 
       << "\nID\t" << "Name" << endl;
  for(int i = 0; i < Faculties.size(); i++)
    {
      cout << Faculties[i].Person::getId() << "\t" << Faculties[i].Person::getName() <<endl;
    }
  cout << "---------------------------------------------\n" << endl;
  return success;
}

//Implementation of methods for changing object attributes.
bool University::AddACourseForAStudent(long courseId, long stId)
{
  //Check if there is room in the course and if the CRN and Student ID are valid.
  bool valid = checkCourseSeat(courseId);
  bool validCID = checkCourseCRN(courseId);
  bool validSID = checkStudentId(stId);
  if(!valid || !validCID || !validSID)
    {
      cout << "Course CRN " << courseId << " could not be added." << endl;
      return failure;
    }
  //Find the course and student.
  for(int i = 0; i < Courses.size(); i++)
    {
      if(Courses[i].getCRN() == courseId)
	{
	  for(int j = 0; j < Students.size(); j++)
	    {
	      if(Students[j].Person::getId() == stId)
		{  //Add the course to the object and increment assigned seats.
		  Students[j].setCoursesTaken(Courses[i]);
		  Courses[i].addAssignedSeat();
		  return success;
		}
	    }
	}
    }
}

bool University::DropACourseForAStudent(long courseId, long stId)
{
  //Check if the CRN and student ID are valid.
  bool validCID = checkCourseCRN(courseId);
  bool validSID = checkStudentId(stId);
  if(!validCID || !validSID)
    {
      cout << "Course CRN " << courseId << " could not be dropped." << endl;
      return failure;
    }
  //Find the course and student.
  for(int i = 0; i < Courses.size(); i++)
    {
      if(Courses[i].getCRN() == courseId)
	{
	  for(int j = 0; j < Students.size(); j++)
	    {
	      if(Students[j].Person::getId() == stId)
		{
		  Students[j].setCoursesdropped(i);
		  Courses[i].dropAssignedSeat();
		  return success;
		}
	    }
	}
    } 
}

bool University::AssignDepartmentChair(long facultyId, long departId)
{
  //Check if the faculty ID and department ID are valid.
  bool validFID = checkFacultyId(facultyId);
  bool validDID = checkDeptId(departId);
  if(!validFID || !validDID)
    {
      cout << "The department chair was not assigned." << endl;
      return failure;
    }
  //Assign the Chair if valid.
  for(int i = 0; i < Faculties.size(); i++)
    {
      if(Faculties[i].Person::getId() == facultyId)
	{
	  for(int j = 0; j < Departments.size(); j++)
	    {
	      if(Departments[j].getdeptId() == departId)
		{
		  Departments[j].setChairId(facultyId);
		  return success;
		}
	    }
	}
    }
}

bool University::AssignInstructorToCourse (long facultyId, long courseId)
{
  //Check if the faculty ID and CRN are valid.
  bool validFID = checkFacultyId(facultyId);
  bool validCRN = checkCourseCRN(courseId);
  if(!validFID || !validCRN)
    {
      cout << "The instructor was not assigned." << endl;
      return failure;
    }
  //If valid, Assign the instructor to the course.
  for(int i = 0; i < Faculties.size(); i++)
    {
      if(Faculties[i].Person::getId() == facultyId)
	{
	  for(int j = 0; j < Courses.size(); j++)
	    {
	      if(Courses[j].getCRN() == courseId)
		{
		  Courses[j].setIsTaughtBy(facultyId);
		  return success;  
		}
	    }
	}
    }
}

//Implementation of Method for verifying data members within objects.
string University::getDeptName(long deptId)
{
  for(int i = 0; i < Departments.size(); i++)
    {
      if(Departments[i].getdeptId() == deptId)
	{	
	  return Departments[i].getname();
	}
    }
  cout << "*******Department " << deptId << " does not exist*******"  << endl;
}

//This method checks the Faculties vector if a department chair exists.
bool University::checkDepChair(long depChairId)
{
  for(int i = 0; i < Faculties.size(); i++)
    {
      if(Faculties[i].getDepartId() == depChairId)
	{	
	  return success;
	}
    }  
  cout << "*******Department " << depChairId << " does not exist*******"  << endl;
  return failure;
}

//This method checks the Departments vector if the department exists.
bool University::checkDeptId(long deptId)
{
  for(int i = 0; i < Departments.size(); i++)
    {
      if(Departments[i].getdeptId() == deptId)
	return success;
    }
  cout << "*******Department " << deptId << " does not exist*******" << endl;
  return failure;
}

//This method checks the Departments vector if the department name exists.
bool University::checkDeptName(string deptName)
{
  for(int i = 0; i < Departments.size(); i++)
    {
      if(Departments[i].getname() == deptName)
	return success;
    }
  cout << "*******Department " << deptName << " does not exist*******" << endl;
  return failure;
}

//This method checks the Faculty vector if a faculty is assigned to the department.
bool University::checkFacultyDept(long deptId)
{
  for(int i = 0; i < Faculties.size(); i++)
    {
      if(Faculties[i].getDepartId() == deptId)
	return success;
    }
  cout << "*******Faculty in department " << deptId << " do not exist*******" << endl;
  return failure;
}

//This method checks the Faculty vector if a faculty ID is valid.
bool University::checkFacultyId(long facultyId)
{
  for(int i = 0; i < Faculties.size(); i++)
    {
      if(Faculties[i].Person::getId() == facultyId)
	return success;
    }
  cout << "*******Faculty " << facultyId << " does not exist*******" << endl;
  return failure;
}

//This method checks the Courses vector if a course is assigned to the department.
bool University::checkCourseDept(long deptId)
{
  for(int i = 0; i < Courses.size(); i++)
    {
      if(Courses[i].getDepartId() == deptId)
	return success;
    }
  cout << "*******Course Department " << deptId << " does not exist*******" << endl;
  return failure;
}

//This method checks the Courses vector if a course exists.
bool University::checkCourseCRN(long CRN)
{
  for(int i = 0; i < Courses.size(); i++)
    {
      if(Courses[i].getCRN() == CRN)
	return success;
    }
  cout << "*******Course CRN " << CRN << " does not exist*******" << endl;
  return failure;
}

//This method checks the Courses vector if a course is full.
bool University::checkCourseSeat(long courseId)
{
  for(int i = 0; i < Courses.size(); i++)
    {
      if(Courses[i].getCRN() == courseId)
	{
	  if(Courses[i].getMaxAvailableSeats() == Courses[i].getAssignedSeats())
	    {
	      cout << "*******Course " << courseId << " is full*******" <<endl;
	      return failure;
	    }
	}
    }
  return success;
}

//This method checks the Students vector if a student exists.
bool University::checkStudentId(long stId)
{
  for(int i = 0; i < Students.size(); i++)
    {
      if(Students[i].Person::getId() == stId)
	return success;
    }
  cout << "*******Student " << stId << " does not exist*******" << endl;
  return failure;
}

//This method checks the Students vector if a major is assigned to a student.
bool University::checkStudentMajor(string deptName)
{
  for(int i = 0; i < Students.size(); i++)
    {
      if(Students[i].getMajor() == deptName)
	return success;
    }
  return failure;
}

//This method removes a Department object from the Departments vector.
bool University::OKremoveDept(long deptId)
{
  for(int i = 0; i < Departments.size(); i++)
    {
      if(Departments[i].getdeptId() == deptId)
	{
	  Departments.erase(Departments.begin() + i);
	  return success;
	}
    }
  cout << "*******Department " << deptId << " does not exist*******" << endl;
  return failure;
}

//This method removes a Student object from the Students vector.
bool University::OKremoveStudent(long stID)
{
  for(int i = 0; i < Students.size(); i++)
    {
      if(Students[i].Person::getId() == stID)
	{
	  Students.erase(Students.begin() + i);
	  return success;
	}
    }
  cout << "*******Student " << stID << " does not exist*******" << endl;
  return failure;
}

//This method removes a Course object from the Courses vector.
bool University::OKremoveCourse(long CRN)
{
  for(int i = 0; i < Courses.size(); i++)
    {
      if(Courses[i].getCRN() == CRN)
	{
	  Courses.erase(Courses.begin() + i);
	  return success;
	}
    }
  cout << "*******Course " << CRN << " does not exist*******" << endl;
  return failure;
}

//This method removes a Faculty object from the Faculties vector.
bool University::OKremoveFaculty(long facultyID)
{
  for(int i = 0; i < Faculties.size(); i++)
    {
      if(Faculties[i].Person::getId() == facultyID)
	{
	  Faculties.erase(Faculties.begin() + i);
	  return success;
	}
    }
  cout << "*******Faculty " << facultyID << " does not exist*******" << endl;
  return failure;
}

//This method processes the transaction file.
bool University::ProcessTransactionFile(string fileName)
{
  //Declare string variable for the transaction file.
  string cmd; 
  
  //Declare variables for department.
  string depName, depLoc; 
  long depChairId, depId;
  
  //Declare variables for courses.
  string cName; 
  long cDepId, cTaughtBy, cCRN;
  int cMaxSeat;
  
  //Declare variables for students and faculty.
  string Name, Email, Address, DateOfBirth, Gender;
  
  //Variables specific to students.
  int sYearOfStudy; 
  string sMajor;
  long sAdvisorId, sStId;
  
  //Variables specific to faculty.
  float fSalary;
  int fYearOfExp;
  long fDepId, fFactId;
  
  //Open the transaction file and process commands one by one. 
  //Return success when complete.
  cout << "\nProcessing transaction file....\n\n";
  ifstream fin;
  fin.open(fileName.data());
  if(!fin)
    {
      //Display an error message if the file does not exist.
      cout << "The file was not found." << endl;
      return failure;
    }
  else
    {
      while(!fin.eof())
	{
	  fin >> cmd;
	  //CreateNewDepartment 
	  if(cmd=="CreateNewDepartment") 
	    {	
	      fin >> depName >> depLoc >> depChairId;
	      CreateNewDepartment(depName, depLoc, depChairId);
	    }
	  
	  else if(cmd=="RemoveADepartment") 
	    {
	      fin >> depId;
	      RemoveADepartment(depId);
	    }
	  
	  else if(cmd=="CreateNewStudent") 
	    {
	      fin >> Name >> Email >> Address >> DateOfBirth >> Gender 
		  >> sYearOfStudy >> sMajor >> sAdvisorId;
	      CreateNewStudent(Name, Email, Address, DateOfBirth, Gender, 
			       sYearOfStudy, sMajor, sAdvisorId);
	    }
	  
	  else if(cmd=="RemoveAStudent") 
	    {
	      fin >> sStId;
	      RemoveAStudent(sStId);
	    }
	  
	  else if(cmd=="CreateNewCourse") 
	    {
	      fin >> cName >> cDepId >> cTaughtBy >> cMaxSeat;
	      CreateNewCourse(cName, cDepId, cTaughtBy, cMaxSeat);
	    }
	  
	  else if(cmd=="RemoveACourse") 
	    {
	      fin >> cCRN;
	      RemoveACourse(cCRN);
	    }
	  
	  else if(cmd=="CreateNewFaculty") 
	    {
	      fin >> Name >> Email >> Address >> DateOfBirth >> Gender 
		  >> fSalary >> fYearOfExp >> fDepId;
	      CreateNewFaculty(Name, Email, Address, DateOfBirth, Gender, 
			       fSalary, fYearOfExp, fDepId);
	    }
	  
	  else if(cmd=="RemoveAFaculty")		
	    {
	      fin >> fFactId;
	      RemoveAFaculty(fFactId);
	    }
	  
	  else if(cmd=="ListCoursesTaughtByFaculty") 
	    {
	      fin >> fFactId;
	      ListCoursesTaughtByFaculty(fFactId);
	    }
	  
	  else if(cmd=="ListCoursesTakenByStudent") 
	    {
	      fin >> sStId;
	      ListCoursesTakenByStudent(sStId);
	    }
	  
	  else if(cmd=="ListFacultiesInDepartment") 
	    {
	      fin >> depId;
	      ListFacultiesInDepartment(depId);
	    }
	  
	  else if(cmd=="ListStudentsOfAFaculty") 
	    {
	      fin >> fFactId;
	      ListStudentsOfAFaculty(fFactId);
	    }
	  
	  else if(cmd=="ListCoursesOfADepartment") 
	    {
	      fin >> depId;
	      ListCoursesOfADepartment(depId);
	    }
	  
	  else if(cmd=="AddACourseForAStudent") 
	    {
	      fin >> cCRN >> sStId;
	      AddACourseForAStudent(cCRN, sStId);
	    }
	  
	  else if(cmd=="DropACourseForAStudent") 
	    {
	      fin >> cCRN >> sStId;
	      DropACourseForAStudent(cCRN, sStId);
	    }
	  
	  else if(cmd=="AssignDepartmentChair") 
	    {
	      fin >> fFactId >> depChairId;
	      AssignDepartmentChair(fFactId, depChairId);
	    }
	  
	  else if(cmd=="AssignInstructorToCourse") 
	    {
	      fin >> fFactId >> cCRN;
	      AssignInstructorToCourse(fFactId, cCRN);
	    }
	  
	  else if(cmd=="ListDepartments") 
	    {
	      ListDepartments();
	    }
	  
	  else if(cmd=="ListStudents") 
	    {
	      ListStudents();
	    }
	  
	  else if(cmd=="ListCourses") 
	    {
	      ListCourses();
	    }
	  
	  else if(cmd=="ListFaculties") 
	    {
	      ListFaculties();
	    }
	}
      fin.close();
    }
  return success;
}
#endif //UNIVERSITY_CPP

