#pragma once
#include <string>
#include <list>
using namespace std;
class Course
{
	string name;
	int courseCode;
	int maxStud;
	list<Course> requiredCourses;
	int hours;
	int numOfStuds;
public:
	Course();
	Course(string, int, int, list<Course>, int);
	int getCourseCode();
	void addPrerequisite(Course c);
	string getCourseName();
	int getCourseMaxStud();
	int getHours();
	list <Course> getRequired();
	void dispalyRequiredCourses();
	void display();
	void setName(string name);
	void setCourseCode(int courseCode);
	void setMaxStudents(int maxStud);
	void setRequiredCourses(list<Course> requiredCourses);
	void setHours(int hours);
	void increaseNumOfStud();
	int getNumOfStuds();
	//string getRequiredCourseName(int i);
	int numOfRequiredCourse();
	string getName();
};
