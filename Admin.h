#pragma once
#include "Employee.h"



class Admin :public Employee {
public:
	//Data
	static map<int, Admin>admin;
	//bool operator<(const Admin& a) const {  // This operator is required in set to compare clients and sort data
	//	return this->id < a.id;
	//}
	//cons
	Admin(){}
	Admin(int id, string name, string password, double salary) : Employee(id, name, password, salary) {}
	//des
	~Admin(){}



<<<<<<< HEAD
=======


>>>>>>> fb3afa91eb14300cd0687e80579d0bde4c114b27
};