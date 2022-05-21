#include "Admin.h"
#include "Course.h"
#include "Student.h"
#include <iostream>
#include <list>
#include <stack>
#include <map>
using namespace std;

Admin::Admin(string name, string password) {
	this->name = name;
	this->password = password;
}


string Admin::getName() {
	return this->name;
}

string Admin::getPassword() {
	return this->password;
}

bool Admin::logIn(string pwd) {
	return pwd == this->password;
}

void Admin::addNewStudent(map<int,Student>& students, map<int,Course>& courses) {
	string name; int id; string password; list<Course> finishedCourses,inProgressCourses; int academicYear;
	cout << "Enter the name of the student : "; cin>>name;
	cout << "Enter the id of the student : "; cin >> id;

	if (students.find(id) != students.end()) 
	{
		cout << "this student is already exists.\n";
		return;
	}

	cout << "Enter the password of the student : "; cin>>password;
	cout << "Enter the academic year of the student : "; cin >> academicYear;
	while (academicYear > 5 || academicYear <= 0) 
	{
		cout << "Wrong year, please try Again \n";
		cout << "Enter the academic year of the student : "; cin >> academicYear;
	}
	cout << "How many courses this students finshed : "; int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the code of course #" << i + 1 << " : ";
		int code; cin >> code;
		bool found = false;
		for (int i = 0; i < courses.size(); i++)
		{
			if (courses[i].getCourseCode() == code) {
				finishedCourses.push_back(courses[i]);
				found = true;
				break;
			}
		}
		if (!found)
		{
			cout << "There's no course like that, please try again \n"; i--;
		}
	}
	cout << "How many courses this students in progress : ";cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the code of course #" << i + 1 << " : ";
		int code; cin >> code;
		bool found = false;
		for (int i = 0; i < courses.size(); i++)
		{
			if (courses[i].getCourseCode() == code) {
				inProgressCourses.push_back(courses[i]);
				courses[i].increaseNumOfStud();
				found = true;
				break;
			}
		}
		if (!found)
		{
			cout << "There's no course like that, please try again \n"; i--;
		}
	}
	students[id] = Student(name, id, password, finishedCourses, inProgressCourses, academicYear);
}

void Admin::AddNewCourse(map<int, Course>& courses) {
	string name; int courseCode; int maxStud; int hours; list<Course> requiredCourses;
	cout << "Enter Course Name : "; cin>>name;
	cout << "Enter Course Code : "; cin >> courseCode;
	if (courses.find(courseCode) != courses.end())
	{
		cout << "this course is already exists.\n";
		return;
	}
	cout << "Enter Max Number of Students for this course : "; cin >> maxStud;
	cout << "Enter the Credit hours of the Course : "; cin >> hours;
	cout << "Enter the number of pre required courses for this course : "; int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the code of course #" << i + 1 << " : ";
		int c; cin >> c;

		if(courses.find(c) != courses.end())
			requiredCourses.push_back(courses[c]);
		else
		{
			cout << "There's no course like that, please try again \n"; i--;
		}
	}

	courses[courseCode] = Course(name, courseCode, maxStud, requiredCourses, hours);
}

void Admin::addPrerequisiteCourse(map<int, Course>& courses) {
	cout << "Enter the course code that you want to edit : ";
	int c; cin >> c;
	int edit = -1;
	int toAdd = -1;
	if (courses.find(c) != courses.end())
		edit = c;
	else
	{
		cout << "Not found\n";
		return;
	}
	cout << "Enter the code of prerequisite course : "; cin >> c;
	if (courses.find(c) != courses.end())
		toAdd = c;
	else
	{
		cout << "Not found\n";
		return;
	}
	courses[edit].addPrerequisite(courses[toAdd]);
}
void Admin::editCourseData(map<int, Course>& courses) {
	cout << "Enter the code of the course : ";
	int code; cin >> code;

	if (courses.find(code) == courses.end()) 
	{
		cout << "No course here with this code \n"; return;
	}

	string name; int courseCode; int maxStud; int hours; list<Course> requiredCourses;
	cout << "Enter Course Name : "; cin >> name;
	cout << "Enter Course Code : "; cin >> courseCode;

	for (map<int, Course>::iterator i = courses.begin(); i != courses.end(); i++)
	{
		if ((name == i->second.getCourseName() && name != courses[code].getCourseName())|| (courseCode == i->second.getCourseCode() && courseCode != courses[code].getCourseCode()))
		{
			cout << "this course is already exists.\n";
			return;
		}
	}
	cout << "Enter Max Number of Students for this course : "; cin >> maxStud;
	cout << "Enter the Credit hours of the Course : "; cin >> hours;
	cout << "Enter the number of pre required courses for this course : "; int n; cin >> n;
	for (int i = 0; i < n; i++)
	{
		cout << "Enter the code of course #" << i + 1 << " : ";
		int c; cin >> c;
		if (courses.find(c) != courses.end())
			requiredCourses.push_back(courses[c]);
		else
		{
			cout << "There's no course like that, please try again \n"; i--;
		}
	}
	courses[code].setName(name);
	courses[code].setCourseCode(code);
	courses[code].setHours(hours);
	courses[code].setMaxStudents(maxStud);
	courses[code].setRequiredCourses(requiredCourses);
}

void Admin::viewListSpecificCourse(map<int, Student>& students, map<int, Course>& courses) {
	int code;
	cout << "Enter the code of the course : "; cin >> code;
	if (courses.find(code) == courses.end())
	{
		cout << "Not found\n";
		return;
	}
	stack<Student> stds; 
	for (map<int, Student>::iterator i = students.begin(); i != students.end(); i++)
	{
		list<Course>inProgress = i->second.getProgressCourses();
		for (list<Course>::iterator j = inProgress.begin(); j != inProgress.end(); j++)
		{
			if (code == (*j).getCourseCode()) {
				stds.push(i->second);
				break;
			}
		}
	}
	int i = 1;
	cout << "-------------------------------------------------------------------------\n";
	while (!stds.empty()) {
		cout << i << " - " << "the student name is " << stds.top().getName() << " with ID " << stds.top().getID() << " in acadmeic year " << stds.top().getAcademicYear() << " \n";
		stds.pop();
		i++;
	}
	cout << "-------------------------------------------------------------------------\n";
}

void Admin::viewListSpecificStudent(map<int, Student>& students) {
	int id; 
	cout << "Enter the ID of the student : ";
	cin >> id;
	if (students.find(id) == students.end())
	{
		cout << "Not found\n";
		return;
	}
	cout << "----------------------------------------------------------\n";
	cout << "In progress courses are : \n";
	students[id].displayInProgressCourses();
	cout << "Finshed courses are : \n";
	students[id].displayFinishedCourses();
	cout << "----------------------------------------------------------\n";
}
