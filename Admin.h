#pragma once
#include "Employee.h"
class FileManager;

class Admin :public Employee {
public:
	//All admins Data <ID, admin> 
	static map<int, Admin>admins;
	//cons
	Admin(){}
	Admin(int id, string name, string password, double salary) : Employee(id, name, password, salary) {}
	//meths
	void saveNewEmployeeToFile(Employee& employee);  //.ccp
	void addEmployee(Employee& employee) {
		Employee::employees.insert({ employee.getID(),employee });
		saveNewEmployeeToFile(employee);
		cout << "Employee added successfully.\n";
		this_thread::sleep_for(chrono::seconds(4));
	}
	Employee* searchEmployee(int id) {
		for (auto& i : Employee::employees) {
			if (i.first == id)
				return &i.second;
		}
		return nullptr;
	}
	void listEmployee() {
		for (auto& i : Employee::employees) {
			i.second.displayEmployeeInfo();
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