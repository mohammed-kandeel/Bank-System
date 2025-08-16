#pragma once
#include <iostream>
#include <string>
#include "Person.h"
using namespace std;

class Client :public Person {
private:
	//atts
	double balance;
	string currency;
	
public:

	//cons
	Client() {
		this->balance = 0.0;
		this->currency = "EG";
	}
	Client(int id, string name, string password, double balance) : Person(id, name, password){
		this->balance = balance;
		this->currency = currency;
		setBalance(balance);
		this->currency = "EG";
	}
	//des
	~Client(){}
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
		else
			cout << "Balance must be >= 1500\n";
	}
	//void setCurrency(string currency) {
	//	this->currency = currency;
	//}
	//meths
	void deposit(double amount) {
		if (amount > 0){
			balance += amount;
			cout << "\nDeposit successful. " << amount << " has been added to your account." << endl;
		}
		else
			cout << "\nAmount must be 100 or a multiple of 100.\n";
	}
	void withDraw(double amount) {
		if (amount <= balance) {
			balance -= amount;
			cout << "\nDeposit successful. " << amount << " has been added to your account." << endl;
		}
		else
			cout << "\nAmount must be 100 or a multiple of 100.\n";
	}
	void transFerTo(double amount, Client& recipient) {

		if (this->id == recipient.id) {
			cout << "Cannot transfer to your own account.\n";
			return;
		}
		if (amount <= balance) {
			withDraw(amount);
			recipient.deposit(amount);
			cout << "Transfer successful! " << amount << " has been transferred to " << recipient.name << ".\n";
		}
		else
			cout << "Transfer failed. You do not have enough balance to complete this transaction.\n";
	}
	bool checkAvailableBalance(double amount) {
		return balance >= amount;
	}
	void displayClintInfo() {
		displayPersonInfo();
		cout << "Balance: " << balance << " " << currency << endl;
	}







	// instapay/vodafonecash
	void Ewallet(string mobile_number, double amount, string otp, string user_otp)
	{
		if (amount > balance)
		{
			cout << "invaild amount \n";
		}
		if (otp != user_otp)
		{
			cout << "wrong otp \n";
		}
		else
		{
			balance -= amount;
			cout << "withdrawal from " << mobile_number << " was successfu \n";
		}
	}
	// ?? ???? ?????
	void receipt()
	{
		char choice;
		cin >> choice;
		cin.ignore();
		cout << "do u want a receipt? (save the environment) ";
		// ?????? ????? ?? ??? ??
		if (choice == 'y')
		{
			cout << "printing receipt... \n";
		}
		else
		{
			cout << "transaction dn without receipt \n";
		}
	}
};

