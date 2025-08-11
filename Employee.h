#pragma once
#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

class Employee :public Person {
protected:
	double salary;
	string currency;
public:
	//cons
	Employee(int id, string name, string password, double salary, string currency) : Person(id, name, password) {
		setSalary(salary);
		this->currency = currency;
	}
	//des
	~Employee(){}
	//gets
	double getSalary() {
		return salary;
	}
	string getCurrency() {
		return currency;
	}
	//sets
	void setSalary(double salary) {
		if (Validation::is_min_salary(salary))
			this->salary = salary;
		else
			cout << "salary must be >= 5000\n";
	}
	void setCurrency(string currency) {
		this->currency = currency;
	}

	//meths
	/*void add_new_client() {
		System::add_new_client();
	}
	void search_for_client_by_id() {
		System::search_for_client_by_id();
	}
	void list_all_clients() {
		System::list_all_clients();
	}
	void edit_info_client() {
		System::edit_info_client();
	}*/
	void displayEmployeeInfo() {
		Person::displayPersonInfo();
		cout << "Salary: " << salary << " " << currency << endl;
	}
	
};