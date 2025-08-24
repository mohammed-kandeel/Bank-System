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
		Client c(stoi(sline[0]), sline[1], sline[2], stod(sline[3]));//(id, name, password, balance);
		
		//		bool	double
		//	(4 hasUSD,5 balanceUSD)
		if (sline[4] == "1") {
			c.setHasUSD(true);
			c.setBalance(stod(sline[5]),"USD");
		}
		//			bool			int			string
		//	(6 hasDebitCardEGP,7 cardIdEGP,8 expiryDateEGP)
		//	(9 hasDebitCardUSD,10 cardIdUSD,11 expiryDateUSD)
		if (sline[6] == "1") c.addDebitCard("EGP", stoi(sline[7]), sline[8]);
		if (sline[9] == "1") c.addDebitCard("USD", stoi(sline[10]), sline[11]);

		//			bool				int			string				double			double
		//	(12hasCreditCardEGP, 13cardIdEGP, 14expiryDateEGP, 15creditLimitEGP, 16amountUsedEGP)
		//	(17hasCreditCardUSD, 18cardIdUSD, 19expiryDateUSD, 20creditLimitUSD, 21amountUsedUSD)
		if (sline[12] == "1") {
			c.addCreditCard("EGP", stoi(sline[13]), sline[14], stod(sline[15]));
			c.useCreditCard("EGP", stod(sline[16]), "withdraw");
		}
		if (sline[17] == "1") {
			c.addCreditCard("USD", stoi(sline[18]), sline[19], stod(sline[20]));
			c.useCreditCard("USD", stod(sline[21]), "withdraw");
		}
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