#pragma once
#include "Employee.h"

class FileManager;

class Admin :public Employee {
public:
	//Data
	static map<int, Admin>admin;
	//cons
	Admin(){}
	Admin(int id, string name, string password, double salary) : Employee(id, name, password, salary) {}
	//des
	~Admin(){}

	void saveNewEmployeeToFile(Employee& employee);  //.ccp
};