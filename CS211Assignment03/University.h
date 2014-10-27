/*This is the University class header.
  It has several public methods for retrieving
  and setting different attributes.*/
// Gilbert Duenas

#ifndef UNIVERSITY_H
#define UNIVERSITY_H
#include<string>
using namespace std;
#include"Faculty.h"
#include"Student.h"
#include"Course.h"
#include"Department.h"

class University
{
  //Declaration of protected variables.
  //Vectors of user defined classes are needed.
 protected:
  vector<Department> Departments;
  vector<Student> Students;
  vector<Course> Courses;
  vector<Faculty> Faculties;
  static bool failure;
  static bool success;
  
 public:
  //Declaration of default constructors.
  University();
  ~University();
  
  //Methods for creating and removing objects.
  bool CreateNewDepartment(string depName, string depLoc, long depChairId);
  bool RemoveADepartment(long depId);
  bool CreateNewStudent(string sName, string sEmail, string sAddress, 
			string sDateOfBirth, string sGender,
			int sYearOfStudy, string sMajor, long sAdvisorId);
  bool RemoveAStudent(long sStId);
  bool CreateNewCourse(string cName, long cDepId, long cTaughtBy, int cMaxSeat);
  bool RemoveACourse(long cCRN);
  bool CreateNewFaculty(string fName, string fEmail, string fAddress, 
			string fDateOfBirth, string fGender,
			float fSalary, int fYearOfExp, long fDepId);
  bool RemoveAFaculty(long fFactId);
  
  //Methods for listing objects by specific parameters.
  bool ListCoursesTaughtByFaculty(long facultyId);
  bool ListCoursesTakenByStudent(long studentId);
  bool ListFacultiesInDepartment (long departId);
  bool ListStudentsOfAFaculty(long facultyId);
  bool ListCoursesOfADepartment(long departId);
  bool ListDepartments();
  bool ListStudents();
  bool ListCourses();
  bool ListFaculties();
  
  //Methods for changing object attributes.
  bool AddACourseForAStudent(long courseId, long stId);
  bool DropACourseForAStudent(long courseId, long stId);
  bool AssignDepartmentChair(long facultyId, long departId);
  bool AssignInstructorToCourse (long facultyId, long courseId);
  
  //Methods for verifying data members within objects.
  string getDeptName(long deptId);
  bool checkDepChair(long depChairId);
  bool checkDeptId(long deptId);
  bool checkDeptName(string deptName);
  bool checkFacultyDept(long deptId);
  bool checkFacultyId(long facultyId);
  bool checkCourseDept(long deptId);
  bool checkCourseCRN(long CRN);
  bool checkCourseSeat(long courseId);
  bool checkStudentId(long stId);
  bool checkStudentMajor(string deptName);
  bool OKremoveDept(long deptId);
  bool OKremoveStudent(long stID);
  bool OKremoveCourse(long CRN);
  bool OKremoveFaculty(long facultyID);
  
  //Method for processing a transaction file.
  bool ProcessTransactionFile(string fileName);
};
#endif //UNIVERSITY_H
