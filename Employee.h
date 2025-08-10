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
		this->salary = salary;
		this->currency = currency;
	}

	//gets
	double getSalary() {
		return salary;
	}
	string getCurrency() {
		return currency;
	}
	//sets
	void setSalary(double salary) {
		this->salary = salary;
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