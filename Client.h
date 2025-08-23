#pragma once
#include "Person.h"
#include "Account.h"
#include <map>

class Client :public Person {
private:
	//atts
	Account EGP;
	Account USD;
	bool hasUSD;
public:
	//Data
	static map<int, Client> clients;
	//cons
	Client(){
		hasUSD = false;
	}
	Client(int id, string name, string password, double balance) : Person(id, name, password),EGP(balance,"EGP") {
		hasUSD = false;
	}
	Client(int id, string name, string password, double balanceEGP,bool hasUSD, double balanceUSD) : Person(id, name, password), EGP(balanceEGP, "EGP") {
		this->hasUSD = hasUSD;
		if (hasUSD) {
			USD.setBalance(balanceUSD);
			USD.setCurrency("USD");
		}
	}
	//des
	~Client(){}
	//gets
	double getBalance(string accountType) {
		if (accountType == "EGP")
			return EGP.getBalance();
		else if (accountType == "USD" && hasUSD)
			return USD.getBalance();
		else return 0.0;
	}
	string getCurrency(string accountType) {
		if (accountType == "EGP")
			return EGP.getCurrency();
		else if (accountType == "USD" && hasUSD)
			return USD.getCurrency();
		else return "N/A";
	}
	//key
	bool hasUSDAccount() {
		return hasUSD;
	}
	//sets
	void setBalance(double balance, string accountType) {
		if (accountType == "EGP")
			EGP.setBalance(balance);
		else if (accountType == "USD" && hasUSD)
			USD.setBalance(balance);
	}
	//meths
	void deposit(double amount, string accountType) {
		if (accountType == "EGP")
			EGP.deposit(amount);
		else if (accountType == "USD" && hasUSD)
			USD.deposit(amount);
		else cout << "No USD account available.\n";
	}
	void withDraw(double amount, string accountType) {
		if (accountType == "EGP")
			EGP.withDraw(amount);
		else if (accountType == "USD" && hasUSD)
			USD.withDraw(amount);
		else cout << "No USD account available.\n";
	}
	void transFerTo(double amount, Client& recipient, string accountType) {
		if (this->id == recipient.id) {
			cout << "Cannot transfer to your own account.\n";
			return;
		}
		if (accountType == "EGP") {
			if (amount <= EGP.getBalance()) {
				withDraw(amount, "EGP");
				recipient.deposit(amount, "EGP");
				cout << "Transfer successful! " << amount << " EGP has been transferred to " << recipient.name << ".\n";
			}
			else
				cout << "Transfer failed. You do not have enough balance to complete this transaction.\n";
		}
		else if (accountType == "USD" && hasUSD && recipient.hasUSDAccount()) {
			if (amount <= USD.getBalance()) {
				withDraw(amount, "USD");
				recipient.deposit(amount, "USD");
				cout << "Transfer successful! " << amount << " USD has been transferred to " << recipient.name << ".\n";
			}
			else
				cout << "Transfer failed. You do not have enough balance to complete this transaction.\n";
		}
		else
			cout << "You don't have a USD account.\n";
	}
	bool checkAvailableBalance(double amount, string accountType) {
		if (accountType == "EGP")
			return EGP.checkAvailableBalance(amount);
		else if (accountType == "USD" && hasUSD)
			return USD.checkAvailableBalance(amount);
		else return false;
	}
	void displayClientInfo() {
		Person::displayPersonInfo();
		cout << "Balance: " << EGP.getBalance() << " " << EGP.getCurrency() << endl;
		if(hasUSD)
			cout << "Balance: " << USD.getBalance() << " " << USD.getCurrency() << endl;
	}







	// instapay/vodafonecash
	//void Ewallet(string mobile_number, double amount, string otp, string user_otp)
	//{
	//	if (amount > balance)
	//	{
	//		cout << "invaild amount \n";
	//	}
	//	if (otp != user_otp)
	//	{
	//		cout << "wrong otp \n";
	//	}
	//	else
	//	{
	//		balance -= amount;
	//		cout << "withdrawal from " << mobile_number << " was successful \n";
	//	}
	//}
	//// ?? ???? ?????
	//void receipt()
	//{
	//	char choice;
	//	cin >> choice;
	//	cin.ignore();
	//	cout << "do u want a receipt? (save the environment) ";
	//	// ?????? ????? ?? ??? ??
	//	if (choice == 'y')
	//	{
	//		cout << "printing receipt... \n";
	//	}
	//	else
	//	{
	//		cout << "transaction dn without receipt \n";
	//	}
	//}
};

