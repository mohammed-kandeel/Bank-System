#pragma once
#include <iostream>
#include <string>
#include "Employee.h"
using namespace std;

class Admin :public Employee {
public:
	//cons
	Admin(){}
	Admin(int id, string name, string password, double salary) : Employee(id, name, password, salary) {}
	//des
	~Admin(){}
};