#pragma once
#include"Validation.h"
class Account{
private:
	//atts
	double balance;
	string currency;
public:
	//cons
	Account() {
		this->balance = 0.0;
	}
	Account(double balance, string currency) {
		setBalance(balance);
		this->currency = currency;
	}
	//gets
	double getBalance() {
		return balance;
	}
	string getCurrency() {
		return currency;
	}
	//sets
	void setBalance(double balance) {
		if (Validation::is_min_balance(balance))
			this->balance = balance;
	}
	void setBalance(double balance, double balanceFile) {
		if (Validation::is_min_balance(balance))
			this->balance = balanceFile;
	}
	void setCurrency(string currency) {
		this->currency = currency;
	}
	//meths
	void deposit(double amount) {
		if (amount >= 0) {
			balance += amount;
		}
		else 
			cout << "Deposit amount must be positive.\n";
	}
	void withDraw(double amount) {
		if (amount > 0 && amount <= balance) {
			balance -= amount;
		}
		else cout << "Invalid withdrawal amount.\n";
	}
	bool checkAvailableBalance(double amount) {
		return balance >= amount;
	}
};