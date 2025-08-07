#pragma once
#include <iostream>
#include <string>
using namespace std;

class Person{

protected:
	//atts
	int id;
	string name, password;

public:
	//cons
	Person(int id, string name, string password) {
		this->id = id;
		this->name = name;
		this->password = password;
	}
	//sets
	void setID(int id) {
		this->id = id;
	}
	void setName(string name) {
		this->name = name;
	}
	void setPassword(string password) {
		this->password = password;
	}
	//gets
	int getID() {
		return id;
	}
	string getName() {
		return name;
	}
	string getPassword() {
		return password;
	}
	//meths
	
	void displayPersonInfo() {
		cout << "Name: " << name << endl;
		cout << "ID: " << id << endl;
	}
};

