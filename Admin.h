#pragma once
#include "Employee.h"

class Admin :public Employee {
public:
	//cons
	Admin(){}
	Admin(int id, string name, string password, double salary) : Employee(id, name, password, salary) {}
	//des
	~Admin(){}
};