#pragma once
#include <iostream>
#include <string>
using namespace std;

class Validation{
public:
	static bool is_valid_name(const string& name) {
		if (!(name.size() >= 5 && name.size() <= 20))
			return false;
		if (isspace(name.front()) || isspace(name.back()))
			return false;
		for (char i : name) {
			if (!(isalpha(i) || isspace(i)))
				return false;
		}
		return true;
	}
	static bool is_valid_password(const string& password) {
		return(password.size() >= 8 && password.size() <= 20);
	}
	static bool is_min_balance(const double& amount) {
		return (amount >= 1500);
	}
	static bool is_min_salary(const double& amount) {
		return (amount >= 5000);
	}
};