#pragma once
#include <iostream>
#include <string>
#include "Person.h"
#include "Account.h"
using namespace std;

class Client :public Person {
private:
	//att
	Account account;
	static int number_of_Clients;
public:

	//cons
	Client(int id, string name, string password, double balance, string currency) : Person(id, name, password){
		setBalance(balance);
		setCurrency(currency);
		number_of_Clients++;
	}
	//des
	~Client(){}
	//meths
	void displayClintInfo() {
		Person::displayPersonInfo();
		account.displayAccount();
	}
	//account's meths
	void deposit(double amount) {
		account.deposit(amount);
	}
	void withDraw(double amount) {
		account.withDraw(amount);
	}
	void transFerTo(double amount, Client& recipient) {
		if (amount <=account.getBalance()) {
			account.withDraw(amount);
			recipient.deposit(amount);
		}
	}
	void checkBalance() {
		account.displayAccount();
	}
	void setBalance(double balance) {
		if (Validation::is_min_balance(balance))
			account.setBalance(balance);
		else
			cout << "Balance must be >= 1500\n";
	}
	void setCurrency(string currency) {
		account.setCurrency(currency);
	}

	bool checkAvailableBalance(double amount) {
		return account.checkAvailableBalance(amount);
	}
};

