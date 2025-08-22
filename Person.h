#pragma once
#include"Validation.h"
using namespace std;

class Person{
protected:
	//atts
	int id;
	string name, password;

public:
	//cons
	Person() {
		this->id = 0;
	}
	Person(int id, string name, string password) {
		this->id = id;
		setName(name);
		setPassword(password);
	}
	//des
	~Person(){}
	//sets
	void setID(int id) {
		this->id = id;
	}
	void setName(string name) {
		if (Validation::is_valid_name(name))
			this->name = name;
		else 
			cout << "Invalid name. Name must contain only letters and be between 8 and 20 characters.\n";
	}
	void setPassword(string password) {
		if (Validation::is_valid_password(password))
			this->password = password;
		else
			cout << "Invalid password.\nPassword must be between 8 and 20 characters.\n";
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
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Password: " << password << endl;
	}
};