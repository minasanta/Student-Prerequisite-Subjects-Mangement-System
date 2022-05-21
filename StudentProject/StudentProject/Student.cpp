#include "Student.h"
#include <iostream>
#include <map>
using namespace std;

Student::Student() {
	this->name = "";
	this->id = -1;
	this->password = "";
	this->finishedCourses = {};
	this->inProgressCourses = {};
	this->academicYear = -1;
}

Student::Student(string name, int id, string password, list<Course> finishedCourses, list<Course> inProgressCourses, int academicYear) {
	this->name = name;
	this->id = id;
	this->password = password;
	this->finishedCourses = finishedCourses;
	this->inProgressCourses = inProgressCourses;
	this->academicYear = academicYear;
}

bool Student::logIn(string pwd) {
	return pwd == this->password;
}

void Student::displayFinishedCourses() {
	list<Course>::iterator it = finishedCourses.begin();
	while (it != finishedCourses.end()) {
		cout << (*it).getCourseName() << "\n";
		it++;
	}

}
void Student::displayInProgressCourses() {
	list<Course>::iterator it = inProgressCourses.begin();
	while (it != inProgressCourses.end()) {
		cout << (*it).getCourseName() << "\n";
		it++;
	}
}
void Student::display() {
	cout << "----------------------------------------------\n";
	cout << "The student name is : " << this->name <<"\n";
	cout << "The student id is : " << this->id<<"\n";
	cout << "The student password is : " << this->password<<"\n";
	cout << "For the acadmeic year : " << this->academicYear << "\n";
	if (this->finishedCourses.size() != 0) 
	{
		cout << "The finshed courses are : \n"; this->displayFinishedCourses();
	}
	if (this->inProgressCourses.size() != 0)
	{
		cout << "The courses in progress are : \n"; this->displayInProgressCourses();
	}
	cout << "----------------------------------------------\n";
}

string Student::getName() {
	return name;
}
int Student::getID() {
	return id;
}

int Student::getAcademicYear() {
	return this->academicYear;
}
string Student::getPassword() {
	return this->password;
}
list<Course> Student::getProgressCourses() {
	return this->inProgressCourses;
}

list<Course> Student::getFinshedCourses() {
	return this->finishedCourses;
}
void Student::AvailableCoursesList(map<int, Course>& courses) {

	if (!AvailableCourses.empty())
		AvailableCourses.clear();

	for (map<int, Course>::iterator i = courses.begin(); i != courses.end(); i++) {
		bool found = false;
		if (i->second.getCourseCode() == -1)
			continue;
		for (list<Course>::iterator j = inProgressCourses.begin(); j != inProgressCourses.end(); j++)
		{
			if (i->second.getCourseCode() == (*j).getCourseCode()) {
				found = true; break;
			}
		}
		if (found)
			continue;
		for (list<Course>::iterator j = finishedCourses.begin(); j != finishedCourses.end(); j++)
		{
			if (i->second.getCourseCode() == (*j).getCourseCode()) {
				found = true; break;
			}
		}
		if (found)
			continue;
		if (i->second.getNumOfStuds() == i->second.getCourseMaxStud())
			continue;
		else if (check(i->second)) 
		{
			AvailableCourses.push_back(i->second);
		}

	}

}


void Student::ViewAvailableCourses(map<int, Course>& courses) {
	this->AvailableCoursesList(courses);
	if (AvailableCourses.empty())
	{
		cout << "There are no Available courses\n"; 
	}
	else
	{
		cout << "-------------------------------------------------------------------------\n";
		for (Course item : AvailableCourses)
			cout << item.getName() << " \n";
		cout << "-------------------------------------------------------------------------\n";
	}
}

void Student::ViewDetailsOfACourse(map<int, Course>& courses) {
	cout << "Enter the course name : ";
	string name; cin >> name;
	int index = -1;
	for (map<int,Course>::iterator i = courses.begin(); i != courses.end(); i++)
	{
		if (name == i->second.getCourseName()) {
			index = i->second.getCourseCode();
			break;
		}
	}
	if (index == -1)
	{
		cout << "Course not found"; return;
	}
	Course c = courses[index];
	cout << "-------------------------------------------------------------------------\n";
	cout << "The name of the Course : " << c.getName() << "\n";
	cout << "The Course Code : " << c.getCourseCode() << "\n";
	cout << "The Maximum number of students : " << c.getCourseMaxStud() << "\n";
	cout << "The number of hours of the course : " << c.getHours() << "\n";
	cout << "The Required Courses : \n";
	c.dispalyRequiredCourses();
	cout << "-------------------------------------------------------------------------\n";
}

void Student::RegisterForACourse(map<int, Course>& courses) {
	//Check if there are available courses(if the list is empty or not )
	this->AvailableCoursesList(courses);
	if (AvailableCourses.empty()) {
		cout << "There Is No Avaliable Courses\n"; return;
	}
	else {
		bool flag = false;
		char choice = 'Y';
		do {
			cout << "You Can Register For Any Of The Following Courses : " << endl;
			ViewAvailableCourses(courses);
			cout << "Enter The Course Name That You Want To Register For : " << endl;
			string RCourseName;
			cin >> RCourseName;
			//Check if the input Name&Code is in the list
			list<Course>::iterator it;
			for (it = AvailableCourses.begin(); it != AvailableCourses.end(); ++it) {
				if (RCourseName == it->getName()) {
					inProgressCourses.push_back(*it);
					cout << "You Have Successfully Register For Course : " << RCourseName << endl;
					(*it).increaseNumOfStud();
					flag = true;
					break;
				}
			}
			if (it == AvailableCourses.end()) {
				cout << "Invalid Course Name/Code" << endl;
				cout << "Do You Want To Try Again?(Y/N) : ";
				cin >> choice;
				choice = toupper(choice);
				if (choice == 'N') {
					flag = true;
				}
			}
		} while (flag == false && choice == 'Y');
	}
}

void Student::ViewAllCourses() {
	if (this->inProgressCourses.size() > 0) {
		cout << "----------------------------------------------\n";
		cout << "The courses are : \n";
		this->displayInProgressCourses();
		cout << "----------------------------------------------\n";
	}
	else
		cout << "no courses are in progress\n";
}

void Student::EditData() {
	int z;
	string name, pwd;
	cout << "Press 1 to edit your name\tPress 2 to edit your password\t Press 3 to edit both\n";
	cin >> z;
	while (z < 1 || z > 3) {
		cout << "Wrong choice please try again : ";
		cin >> z;
	}
	if (z == 1) {
		cout << "please enter your new name : ";
		cin >> name;
		this->name = name;
	}
	else if (z == 2) {
		cout << "please enter your new password : ";
		cin >> pwd;
		this->password = pwd;
	}
	else {
		cout << "please enter your new name : ";
		cin >> name;
		cout << "please enter your new password : ";
		cin >> pwd;
		this->name = name;
		this->password = pwd;
	}
}

bool Student::check(Course c) {
	int x = 0;
	list<Course> r = c.getRequired();
	for (list<Course>::iterator i = r.begin(); i != r.end(); i++) {
		for (list<Course>::iterator j = finishedCourses.begin(); j != finishedCourses.end(); j++) {
			if ((*i).getCourseCode() == (*j).getCourseCode()) {
				x++;
				break;
			}


		}
	}
	return (x == c.numOfRequiredCourse());
}