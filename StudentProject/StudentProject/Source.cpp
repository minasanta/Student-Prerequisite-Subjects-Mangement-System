#include <iostream>
#include "Admin.h"
#include "Course.h"
#include "Student.h"
#include <vector>
#include <map>
#include <fstream>
#include <sstream>

using namespace std;

void adminUI(string);
void studentUI(string);
void save(map<int,Student>,map<int,Course>);
void upLoad(map<int,Student>&, map<int,Course>&);

const Admin mina("MinaNabil", "12345678");
const Admin michel("MichelMagdy", "12345678");
const Admin samy("SamySamer","12345678");
const Admin sandra("SandraAlfy", "12345678");
const Admin maria("MariaMedhat", "12345678");
const Admin marina("MarinaAtef", "12345678");

int main() {
	system("color f5");
	vector<Admin> admins = {mina, michel, samy, sandra, maria, marina};
	map<int,Student> students;
	map<int,Course> courses;
	upLoad(students, courses);

	cout << "*****************************************************************************\n\n";
	cout << "      Hello With Student Prerequisite Subjects Management System             \n\n";
	cout << "*****************************************************************************\n\n";

	while (true) 
	{
		cout << "Are you\n 1 - admin \t 2 - student : ";
		int choice; cin >> choice;
		while (choice != 1 && choice != 2) {
			cout << "Wrong choice please try again : ";
			cin >> choice;
		}

		if (choice == 1)
		{
			string userName;
			cout << "enter your user name : ";
			cin >> userName;
			int foundUser = -1;
			do
			{
				for (int i = 0; i < admins.size(); i++)
				{
					if (userName == admins[i].getName()) {
						foundUser = true;
						foundUser = i;
						break;
					}
				}
				if (foundUser != -1)
					break;
				cout << "there's no user called like this\n";
				cout << "1- enter 0 leave the programe \t 2- any number to try again \n";
				int c; cin >> c;
				if (c == 0)
					return 0;
				cout << "enter your user name : ";
				cin >> userName;
			} while (true);
			while (true)
			{
				cout << "Enter the password for " << userName << " : ";
				string pwd;cin>>pwd;
				if (admins[foundUser].logIn(pwd)) {
					break;
				}
				cout << "Wrong password\n";
				cout << "1- enter 0 leave the programe \t 2- any number to try again \n";
				int c; cin >> c;
				if (c == 0)
					return 0;
			}
			int c = 0;
			do {
				adminUI(admins[foundUser].getName());
				cin >> c;
				char s;
				switch (c)
				{
				case 1: admins[foundUser].addNewStudent(students, courses);break;
				case 2: admins[foundUser].AddNewCourse(courses); break;
				case 3: admins[foundUser].addPrerequisiteCourse(courses);  break;
				case 4: admins[foundUser].viewListSpecificCourse(students,courses); break;
				case 5: admins[foundUser].viewListSpecificStudent(students); break;
				case 6: admins[foundUser].editCourseData(courses);  break;
				case 7:
					for (map<int, Student>::iterator i = students.begin(); i != students.end(); i++) {
						i->second.display();
					}; break;
				case 8:
					for (map<int,Course>::iterator i = courses.begin(); i != courses.end(); i++) {
						i->second.display();
					}; break;
				case 9: break;
				case 10: 
					cout << "Do you want to save the changes Y/N : ";
					cin >> s;
					while (s != 'y' && s != 'Y' && s != 'n' && s != 'N') {
						cout << "Try again Y/N : "; cin >> s;
					}
					if (s == 'y' || s == 'Y')
						save(students,courses);
					return 0; break;
				default: break;
				}
			} while (c != 9);
		}
		else {
			int id;
			cout << "enter your ID : ";
			cin >> id;
			do
			{
				if (students.find(id) != students.end())
					break;
				cout << "there's no user called like this\n";
				cout << "1- enter 0 leave the programe \t 2- any number to try again \n";
				int c; cin >> c;
				if (c == 0)
					return 0;
				cout << "enter your ID : ";
				cin >> id;
			} while (true);
			while (true)
			{
				cout << "Enter the password for " << students[id].getName() << " : ";
				string pwd; cin >> pwd;
				if (students[id].logIn(pwd)) {
					break;
				}
				cout << "Wrong password\n";
				cout << "1- enter 0 leave the programe \t 2- any number to try again \n";
				int c; cin >> c;
				if (c == 0)
					return 0;
			}
			int c = 0;
			do {
				studentUI(students[id].getName());
				cin >> c;
				char s;
				switch (c)
				{
				case 1: students[id].ViewAvailableCourses(courses); break;
				case 2: students[id].ViewDetailsOfACourse(courses); break;
				case 3: students[id].RegisterForACourse(courses);  break;
				case 4: students[id].ViewAllCourses(); break;
				case 5: students[id].EditData(); break;
				case 6: break;
				case 7: cout << "Do you want to save the changes Y/N : ";
					cin >> s;
					while (s != 'y' && s != 'Y' && s != 'n' && s != 'N') {
						cout << "Try again Y/N : "; cin >> s;
					}
					if (s == 'y' || s == 'Y')
						save(students, courses);
					return 0; break;
				default: break;
				}
			} while (c != 6);
	
		}
	}
	return 0;
}


void adminUI(string name) {
	cout << "\nHello, " << name << "\n";
	cout << "What do you want to do \n";
	cout << "1- Add new Student \t\t\t\t\t 2- Add new course\n";
	cout << "3- Add course prerequisite \t\t\t\t 4- View List of all students in a specific course\n";
	cout << "5- View List of all courses of a specific student \t 6-Edit the data of the course \n";
	cout << "7- View all students \t\t\t\t\t 8- view all courses\n";
	cout << "9- log out \t\t\t\t\t\t 10-Exit\n";
}
void studentUI(string name) {
	cout << "\nHello, " << name << "\n";
	cout << "What do you want to do \n";
	cout << "1- View List of all available courses \t\t\t 2- View details of a specific course\n";
	cout << "3- Register for a course \t\t\t\t 4- View all your courses\n";
	cout << "5- Edit your data \t\t\t\t\t 6- log out \n";
	cout << "7- Exit\n";
}
void save(map<int,Student> students, map<int,Course> courses) {
	fstream myFile;
	myFile.open("courses.txt", ios::out);
	if (myFile.is_open()) 
	{
		map<int, Course>::iterator i = courses.begin();
		for (; i != courses.end(); i++)
		{
			myFile << i->second.getCourseName() << "\n";
			myFile << i->second.getCourseCode() << "\n";
			myFile << i->second.getCourseMaxStud() << "\n";
			myFile << i->second.getHours() << "\n";
		}
		myFile.close();
	}
	myFile.open("requiredCourses.txt", ios::out);
	if (myFile.is_open()) 
	{
		map<int, Course>::iterator i = courses.begin();
		for (; i != courses.end(); i++)
		{
			myFile << i->second.getCourseCode() << "\n";
			list<Course> tmp = i->second.getRequired();
			for (list<Course>::iterator i = tmp.begin(); i != tmp.end(); i++)
			{
				myFile << (*i).getCourseCode() << "\n";
			}
			myFile << "end\n";
		}
		myFile.close();
	}
	myFile.open("students.txt", ios::out);
	if (myFile.is_open())
	{
		map<int, Student>::iterator i;
		for (i = students.begin(); i != students.end(); i++)
		{
			myFile << i->second.getName() << "\n";
			myFile << i->second.getID() << "\n";
			myFile << i->second.getPassword() << "\n";
			myFile << i->second.getAcademicYear() << "\n";
			myFile << "inProgressCourses \n";
			list<Course> inProg = i->second.getProgressCourses();
			for (list<Course>::iterator i = inProg.begin(); i != inProg.end(); i++)
			{
				myFile << (*i).getCourseCode() << "\n";
			}
			myFile << "inFinshedCourses \n";
			list<Course> finshed = i->second.getFinshedCourses();
			for (list<Course>::iterator i = finshed.begin(); i != finshed.end(); i++)
			{
				myFile << (*i).getCourseCode() << "\n";
			}
			myFile << "end\n";
		}
		myFile.close();
	}
}

void upLoad(map<int,Student>& students, map<int,Course>& courses) {
	fstream myFile;
	string line;
	myFile.open("courses.txt", ios::in);
	if (myFile.is_open()) 
	{
		string name; int courseCode; int maxStud; int hours; list<Course> requiredCourses;
		int i = 3;
		while (getline(myFile, line)) {
			if (i == 3)
				name = line;
			else if (i == 2) {
				stringstream geek(line);
				geek >> courseCode;
			}
			else if (i == 1) {
				stringstream geek(line);
				geek >> maxStud;
			}
			else if (i == 0) {
				stringstream geek(line);
				geek >> hours;
				i = 4;
				courses[courseCode] = Course(name,courseCode,maxStud,requiredCourses,hours);
			}
			i--;
		}
		myFile.close();
	}
	myFile.open("requiredCourses.txt", ios::in);
	if (myFile.is_open())
	{
		int code;
		int j = 1;
		int edit = 0;
		while (getline(myFile, line)) {
			if (j == 1) {
				stringstream geek(line);
				geek >> code;
				edit = code;
				j = 0;
			}
			else if (j == 0) {
				if (line == "end") {
					j = 1;
				}
				else {
					stringstream geek(line);
					geek >> code;
					courses[edit].addPrerequisite(courses[code]);
				}
			}
		}
		myFile.close();
	}
	myFile.open("students.txt", ios::in);
	if (myFile.is_open())
	{
		string name;int id;string password;list<Course> finishedCourses, inProgressCourses;int academicYear;
		int j = 5;
		while (getline(myFile, line)) 
		{
			if (j == 5) {
				name = line;
				j--;
			}
			else if (j == 4) {
				stringstream geek(line);
				geek >> id;
				j--;
			}
			else if (j == 3) {
				password = line;
				j--;
			}
			else if (j == 2) {
				stringstream geek(line);
				geek >> academicYear;
				j--;
			}
			else if (j == 1) {
				while (getline(myFile, line))
				{
					if (line == "inFinshedCourses ")
						break;
					int code;
					stringstream geek(line);
					geek >> code;
					inProgressCourses.push_back(courses[code]);
					courses[code].increaseNumOfStud();
				}
				j--;
			}
			else if (j == 0) 
			{
				do
				{
					if (line == "end")
						break;
					int code;
					stringstream geek(line);
					geek >> code;
					finishedCourses.push_back(courses[code]);
				} while (getline(myFile, line));
				j = 5;
				students[id]  =Student(name, id, password, finishedCourses, inProgressCourses, academicYear);
				finishedCourses.clear();
				inProgressCourses.clear();
			}
		}
		myFile.close();
	}
}
