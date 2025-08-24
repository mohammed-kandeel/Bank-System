#pragma once
#include "Person.h"
#include "Account.h"
#include "AccountCard.h"
#include <map>

class Client :public Person {
private:
	//atts
	Account EGP;
	Account USD;
	bool hasUSD;
	map < string, AccountCard > cards; // <account type , card>   --->   <EGP, credit>
	//string tractionHistory[7];
	
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
	~Client(){
		for (auto& i : cards) {
			delete i.second.credit;
			delete i.second.debit;
		}
	}
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
		if (accountType == "EGP"){
			EGP.setBalance(balance);
			EGP.setCurrency("EGP");
		}
		else if (accountType == "USD" && hasUSD){
			USD.setBalance(balance);
			USD.setCurrency("USD");
		}
	}
	void setHasUSD(bool hasUSD) {
		this->hasUSD = hasUSD;
	}
	//meths
	void displayClientInfo() {
		Person::displayPersonInfo();
		cout << "Balance: " << EGP.getBalance() << " " << EGP.getCurrency() << endl;
		if (hasUSD)
			cout << "Balance: " << USD.getBalance() << " " << USD.getCurrency() << endl;
	}

	//meths account
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

	//meths DebitCard & CreditCard
	bool hasDebitCard(string accountType) {
		auto it = cards.find(accountType);
		return it != cards.end() && it->second.debit != nullptr;
	}
	bool hasCreditCard(string accountType) {
		auto it = cards.find(accountType);
		return it != cards.end() && it->second.credit != nullptr;
	}
	
	int getIdCard(string accountType,string cardType) {
		auto it = cards.find(accountType);
		if (it == cards.end()) 
			return 0; //Account type not found or Wrong input
		
		if (cardType == "credit" && hasCreditCard(accountType)) 
			return it->second.credit->getIdCard();
		else if (cardType == "debit" && hasDebitCard(accountType)) 
			return it->second.debit->getIdCard();
		else  return 0; //Account type not found or Wrong input
	}
	string getExpiryDateCard(string accountType, string cardType) {
		auto it = cards.find(accountType);
		if (it == cards.end()) 
			return "N/A"; //Account type not found
		
		if (cardType == "credit" && hasCreditCard(accountType)) 
			return it->second.credit->getExpiryDateCard();
		else if (cardType == "debit" && hasDebitCard(accountType)) 
			return it->second.debit->getExpiryDateCard();
		else   return "N/A"; //Wrong input
	}
	
	double getCreditLimit(string accountType) {
		auto it = cards.find(accountType);
		if (it == cards.end()) 
			return 0.0; //Account type not found 
		
		if (!hasCreditCard(accountType))
			return 0.0;//No Credit card
		return it->second.credit->getCreditLimit();
	}
	double getCreditUsed(string accountType) {
		auto it = cards.find(accountType);
		if (it == cards.end()) 
			return 0.0; //Account type not found 
		if (!hasCreditCard(accountType))
			return 0.0; //No Credit card
		return it->second.credit->getUsedCredit();
	}

	void addDebitCard(string accountType, int cardId, string expiryDate) {
		Account* account;
		if (accountType == "EGP")
			account = &EGP;
		else if (accountType == "USD" && hasUSD)
			account = &USD;
		else {
			cout << "Account not found.\n";
			return;
		}

		auto it = cards.find(accountType);
		if (it == cards.end()) {
			cout << "Account type not found\n";
			return;
		}
		if (hasDebitCard(accountType)) {
			cout << accountType << " already has a debit card.\n";
			return;
		}
		it->second.debit = new DebitCard(cardId, expiryDate, account);
	}
	void addCreditCard(string accountType, int cardId, string expiryDate, double creditLimit) {
		Account* account;
		if (accountType == "EGP")
			account = &EGP;
		else if (accountType == "USD" && hasUSD)
			account = &USD;
		else {
			cout << "Account not found.\n";
			return;
		}
		auto it = cards.find(accountType);
		if (it == cards.end()) {
			cout << "Account type not found\n";
			return;
		}
		if (hasCreditCard(accountType)) {
			cout << accountType << " already has a debit card.\n";
			return;
		}
		it->second.credit = new CreditCard(cardId, expiryDate, account, creditLimit);
	}
	void useDebitCard(string accountType, double amount, string operation) {
		if (!hasDebitCard(accountType)) {
			cout << "No debit card for this account.\n";
			return;
		}
		auto it = cards.find(accountType);
		if (operation == "deposit") {
			it->second.debit->deposit(amount);
		}
		else if (operation == "withdraw") {
			it->second.debit->withdraw(amount);
		}
		else {
			cout << "Invalid operation.\n";
		}
	}
	void useCreditCard(string accountType, double amount, string operation) {
		if (!hasCreditCard(accountType)) {
			cout << "No credit card for this account.\n";
			return;
		}
		auto it = cards.find(accountType);
		if (operation == "deposit") {
			it->second.credit->deposit(amount);
		}
		else if (operation == "withdraw") {
			it->second.credit->withdraw(amount);
		}
		else {
			cout << "Invalid operation.\n";
		}
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

