#pragma once
#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

class Employee :public Person {
protected:
	//atts
	double salary;
	string currency;
public:
	//cons
	Employee(){}
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
	void displayEmployeeInfo() {
		Person::displayPersonInfo();
		cout << "Salary: " << salary << " " << currency << endl;
	}
};