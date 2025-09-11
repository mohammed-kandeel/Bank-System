#pragma once
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
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

	static void showError(string message) {
		cout << "\n" << message << "\n";
		this_thread::sleep_for(chrono::seconds(4));
	}
	static bool cancelOperation(string temp) {
		if (temp == "0") {
			system("cls");
			showError("\nOperation cancelled. Returning to main menu...\n");
			return true;
		}
		return false;
	}
	static bool maxTry(int count) {
		if (count == 3) {
			showError("Too many invalid attempts. Returning to main menu...\n");
			return true;
		}
		return false;
	}
	template<class T>
	static bool tryParseNumber(string& input, T& num) {
		try {
			size_t idx;
			num = stod(input, &idx);  // idx = آخر موضع حوِّلته stod
			// لو في أي حاجة زيادة بعد الرقم، اعتبره خطأ
			return idx == input.length();
		}
		catch (invalid_argument&) { return false; }
		catch (out_of_range&) { return false; }
	}
};