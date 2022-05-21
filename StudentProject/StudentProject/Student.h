#pragma once
#include<string>
#include<list>
#include <vector>
#include"Course.h"
#include <map>
using namespace std;
class Student
{
	string name;
	int id;
	string password;
	list<Course> finishedCourses;
	list<Course> inProgressCourses;
	list<Course> AvailableCourses;
	int academicYear;

public:
	Student();
	Student(string, int, string, list<Course>, list<Course>, int);
	bool logIn(string);
	void displayFinishedCourses();
	void displayInProgressCourses();
	void display();
	string getName();
	int getID();
	string getPassword();
	list<Course> getProgressCourses();
	list<Course> getFinshedCourses();
	int getAcademicYear();
	void AvailableCoursesList(map<int, Course>& courses);
	void ViewAvailableCourses(map<int, Course>& courses);
	void ViewDetailsOfACourse(map<int, Course>& courses);
	void RegisterForACourse(map<int, Course>& courses);
	void ViewAllCourses();
	void EditData();
	bool check(Course c);
};