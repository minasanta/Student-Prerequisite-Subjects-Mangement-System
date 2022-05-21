#include "Course.h"
#include <list>
#include <string>
#include <vector>
#include <iostream>
using namespace std;

Course::Course() {
	this->name = "";
	this->courseCode = -1;
	this->maxStud = -1;
	this->requiredCourses = {};
	this->hours = -1;
	this->numOfStuds = -1;
}

Course::Course(string name, int courseCode, int maxStud, list<Course> requiredCourses, int hours) {
	this->name = name;
	this->courseCode = courseCode;
	this->maxStud = maxStud;
	this->requiredCourses = requiredCourses;
	this->hours = hours;
	this->numOfStuds = 0;
}

void Course::addPrerequisite(Course c) {
	this->requiredCourses.push_back(c);
}

int Course::getCourseCode() {
	return this->courseCode;
}
string Course::getCourseName() {
	return this->name;
}
void Course::dispalyRequiredCourses() {
	list<Course>::iterator it = this->requiredCourses.begin();
	while (it != this->requiredCourses.end()) {
		cout << (*it).name << "\n";
		it++;
	}
}
void Course::display() {
	cout << "----------------------------------------------\n";
	cout << "The name of the course is : " << this->name << "\n";
	cout << "The code of the course is : " << this->courseCode << "\n";
	cout << "The number of students enrolled in this course is : " << this->numOfStuds << "\n";
	cout << "The max students of the course is : " << this->maxStud<< "\n";
	cout << "The hours of the course is : " << this->hours << "\n";
	if(this->requiredCourses.size()!=0)
	{
		cout << "The required courses of the course are : " << "\n";
		this->dispalyRequiredCourses();
	}
	cout << "----------------------------------------------\n";
}


void Course::setName(string name) {
	this->name = name;
}
void Course::setCourseCode(int courseCode) {
	this->courseCode = courseCode;
}
void Course::setMaxStudents(int maxStud) {
	this->maxStud = maxStud;
}
void Course::setRequiredCourses(list<Course> requiredCourses) {
	this->requiredCourses = requiredCourses;
}
void Course::setHours(int hours) {
	this->hours = hours;
}
string Course::getName() {
	return this->name;
}

int Course::getCourseMaxStud() {
	return this->maxStud;
}
int  Course::getHours() {
	return this->hours;
}
list <Course> Course::getRequired() {
	return this->requiredCourses;
}

void Course::increaseNumOfStud() {
	this->numOfStuds++;
}
int Course::getNumOfStuds() {
	return numOfStuds;
}

int Course::numOfRequiredCourse() {
	return requiredCourses.size();
}