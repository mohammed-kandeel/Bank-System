#pragma once
#include "Person.h"
#include <map>

class Client :public Person {
private:
	//atts
	double balance;
	string currency;
	
public:
	//Data
	static map<int, Client> clients;
	//bool operator<(const Client& c) const {  // This operator is required in set to compare clients and sort data
	//	return this->id < c.id;
	//}
	//bool operator=(const Client& c) const {  // This operator is required in set to compare clients
	//	return this->id == c.id;
	//}
	//cons
	Client(){
		this->balance = 0.0;
		this->currency = "EG";
	}
	Client(int id, string name, string password, double balance) : Person(id, name, password){
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
		else cout << "Balance must be >= 1500\n";
	}
	//meths
	void deposit(double amount) {
		balance += amount;
	}
	void withDraw(double amount) {
		if (amount <= balance ) {
			balance -= amount;
		}
		else cout << "\nInvalid Amount\n";
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
	void displayCleintInfo() {
		Person::displayPersonInfo();
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
			cout << "withdrawal from " << mobile_number << " was successful \n";
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

