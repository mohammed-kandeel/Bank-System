#pragma once
#include "Admin.h"

#include<vector>
#include<sstream>

class Parser{
public:
	//Cut the line into parts and return a vector of data to build a Person object.
	static vector<string> split(string line) {
		// (id, name, password, balance or salary ,currency)
		vector<string> sline;
		stringstream ss(line);

		string value;
		while (getline(ss, value, '&')) {
			sline.push_back(value);
		}
		return sline;
	}

	//Return a Person object with its data.
	static Client parseToClient(string line) {
		vector<string> sline = split(line);
		Client c(stoi(sline[0]), sline[1], sline[2], stod(sline[3]));
		return c;
	}
	static Employee parseToEmployee(string line) {
		vector<string> sline = split(line);
		Employee e(stoi(sline[0]), sline[1], sline[2], stod(sline[3]));
		return e;
	}
	static Admin parseToAdmin(string line) {
		vector<string> sline = split(line);
		Admin a(stoi(sline[0]), sline[1], sline[2], stod(sline[3]));
		return  a;
	}
};