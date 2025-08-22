#pragma once
#include <iostream>
#include <string>
using namespace std;

class Validation{
public:
	static bool is_valid_name(string name) {
		if (!(name.size() >= 5 && name.size() <= 20))
			return false;

		for (auto i : name) {
			if (!((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i == ' ')))
				return false;
		}
		return true;
	}
	static bool is_valid_password(string password) {
		return(password.size() >= 8 && password.size() <= 20);
	}
	static bool is_min_balance(double amount) {
		return (amount >= 1500);
	}
	static bool is_min_salary(double amount) {
		return (amount >= 5000);
	}
};