#pragma once
#include "Employee.h"

class Admin :public Employee {
public:
	//All admins Data <ID, *pointer> 
	static map<int, Admin*>admins;
	static void removeAllAdmins() {
		for (auto& i : Admin::admins) {
			delete i.second;
		}
		Admin::admins.clear();
	}
	//cons
	Admin(){}
	Admin(int id, string name, string password, double salary) : Employee(id, name, password, salary) {}
	//meths
	void addEmployee(Employee* employee) {
		Employee::employees.insert({ employee->getID(),employee });
		cout << "Employee added successfully.\n";
	}
	Employee* searchEmployee(int id) {
		auto it = Employee::employees.find(id);
		if (it != Employee::employees.end())
			return it->second;
		return nullptr;

	}
	void listEmployees() {
		for (auto& i : Employee::employees) {
			i.second->displayEmployeeInfo();
			cout << "\n----------------------\n\n";
		}
	}
	void editEmployee(int id, string name, string password, double salary) {
		Employee* e = searchEmployee(id);
		if (e == nullptr) return;

		if (name != "-1" && name != "-2") e->setName(name);                           //'-2'  Cancel option / '-1' so many rong input
		else if (password != "-1" && password != "-2") e->setPassword(password);
		else if (salary != -1 && salary != -2) e->setSalary(salary);
		else return;
	}
};