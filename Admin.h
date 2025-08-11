#pragma once
#include <iostream>
#include <string>
#include "Employee.h"

using namespace std;

class Admin :public Employee {
public:
	//cons
	Admin(int id, string name, string password, double salary, string currency) : Employee(id, name, password, salary, currency) {}
	//des
	~Admin(){}





	//meths
	/*void  add_new_employee(){
		System::add_new_employee();
	}
	void  search_for_employee() {
		System::search_for_employee();
	}
	void  edit_employee() {
		System::edit_employee();
	}
	void  list_all_employees() {
		System::list_all_employees();
	}*/
};