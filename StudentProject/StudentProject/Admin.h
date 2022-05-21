#pragma once
#include <string>
#include "Course.h"
#include "Student.h"
#include <vector>
#include <map>
using namespace std;
class Admin
{
	string name;
	string password;
public:
	Admin(string, string);
	bool logIn(string pwd);
	string getName();
	string getPassword();
	void addNewStudent(map<int,Student>& students, map<int,Course>& courses);
	void AddNewCourse(map<int, Course>& courses);
	void addPrerequisiteCourse(map<int, Course>& courses);
	void editCourseData(map<int, Course>& courses);
	void viewListSpecificCourse(map<int, Student>& students, map<int, Course>& courses);
	void viewListSpecificStudent(map<int, Student>& students);
};