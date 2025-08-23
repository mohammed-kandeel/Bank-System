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
		this->balance = balance;
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
		else cout << "Balance must be >= 1500\n";
	}
	void setCurrency(string currency) {
		this->currency = currency;
	}
	//meths
	void deposit(double amount) {
		balance += amount;
	}
	void withDraw(double amount) {
		if (amount <= balance) {
			balance -= amount;
		}
		else cout << "\nInvalid Amount\n";
	}
	bool checkAvailableBalance(double amount) {
		return balance >= amount;
	}
};