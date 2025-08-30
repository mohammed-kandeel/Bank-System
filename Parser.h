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
		Client c;

		//( 0id, 1name, 2password, 3balance);
		c.setID(stoi(sline[0]));
		c.setName(sline[1]);
		c.setPassword(sline[2]);
		c.setBalance(1500, stod(sline[3]), AccountType::EGP);
		
		//		      bool	    double
		//	(1500, 4hasUSD, 5balanceUSD)
		if (sline[4] == "1") {
			c.setHasUSD(true);
			c.setBalance(1500, stod(sline[5]), AccountType::USD);
		}
		//			bool			int			string
		//	( 6hasDebitCardEGP, 7cardIdEGP,  8expiryDateEGP)
		//	( 9hasDebitCardUSD, 10cardIdUSD, 11expiryDateUSD)
		if (sline[6] == "1") c.setNewCard(AccountType::EGP, CardType::Debit, stoi(sline[7]), sline[8], 0.0);
		if (sline[9] == "1") c.setNewCard(AccountType::USD, CardType::Debit, stoi(sline[10]), sline[11], 0.0);

		//			bool				int			string				double			double
		//	(12hasCreditCardEGP, 13cardIdEGP, 14expiryDateEGP, 15creditLimitEGP, 16amountUsedEGP)
		//	(17hasCreditCardUSD, 18cardIdUSD, 19expiryDateUSD, 20creditLimitUSD, 21amountUsedUSD)
		if (sline[12] == "1") {
			c.setNewCard(AccountType::EGP, CardType::Credit, stoi(sline[13]), sline[14], stod(sline[15]));
			c.setUsedCreditCard(AccountType::EGP, CardType::Credit, stod(sline[16]));
		}
		if (sline[17] == "1") {
			c.setNewCard(AccountType::USD, CardType::Credit, stoi(sline[18]), sline[19], stod(sline[20]));
			c.setUsedCreditCard(AccountType::USD, CardType::Credit, stod(sline[21]));
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