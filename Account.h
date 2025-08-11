#pragma once
#include <iostream>
#include <string>
#include"Validation.h"
using namespace std;

class Account{
protected:
	//atts
	double balance;
	string currency;

public:
	//cons
	Account() {
		balance = 0;
	};
	Account(double balance, string currency) {
		this->balance = balance;
		this->currency = currency;
	}
	//des
	~Account() {}
	//sets
	void setBalance(double balance) {
		this->balance = balance;
	}
	void setCurrency(string currency) {
		this->currency = currency;
	}
	//gets
	double getBalance() {
		return balance;
	}
	string getCurrency() {
		return currency;
	}
	//meths
	void deposit(double amount) {
		if (amount > 0)
			balance += amount;
	}
	void withDraw(double amount) {
		if (amount<=balance)
			balance -= amount;
	}
	void displayAccount() {
		cout << "Balance: " << balance << " " << currency << endl;
	}
	bool checkAvailableBalance(double amount) {
		return balance >= amount;
	}

};