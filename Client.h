#pragma once
#include "Person.h"
#include <vector>
#include <string>
#include "Account.h"
#include "AccountCard.h"
#include <map>

enum class CardType { Credit, Debit };
enum class AccountType { EGP, USD ,Non };
enum class Operation { Deposit, Withdraw };


class Client :public Person {
private:
	//atts
	Account EGP;
	Account USD;
	bool hasUSD;
	map < AccountType, AccountCard > cards; // <account type , card>   --->   <EGP, credit>
	vector<string>transactionHistory; // size (7)
	int maxTransactions = 7;
	
	//private meths
	Account& accountTypeToAccount(AccountType accountType) {
		switch (accountType) {
			case AccountType::EGP:return EGP;
			case AccountType::USD:return USD;
			default: throw invalid_argument("Invalid account type");
		}
	}
	void setNewDebitCard(AccountType accountType, int cardId, string expiryDate, Account* account) {
		if (!hasDebitCard(accountType) && ((accountType == AccountType::EGP) || (accountType == AccountType::USD && hasUSDAccount())))
			cards[accountType].debit = new DebitCard(cardId, expiryDate, account);
	}
	void setNewCreditCard(AccountType accountType, int cardId, string expiryDate, Account* account, double creditLimit) {
		if (!hasCreditCard(accountType) && ((accountType == AccountType::EGP) || (accountType == AccountType::USD && hasUSDAccount())))
			cards[accountType].credit = new CreditCard(cardId, expiryDate, account, creditLimit);
	}

public:
	//All clients Data <ID, *pointer> 
	static map<int, Client*> clients;
	static void removeAllClients() {
		for (auto& i : Client::clients) {
			delete i.second;
		}
		Client::clients.clear();
	}
	//cons
	Client(){
		hasUSD = false;
	}
	Client(int id, string name, string password, double balance) : Person(id, name, password),EGP(balance,"EGP") {
		hasUSD = false;
	}
	Client(int id, string name, string password, double balanceEGP,bool hasUSD, double balanceUSD) : Person(id, name, password), EGP(balanceEGP, "EGP"), USD(balanceUSD,"USD") {
		this->hasUSD = hasUSD;
	}
	//key
	bool hasUSDAccount() {
		return hasUSD;
	}
	bool hasDebitCard(AccountType accountType) {
		if (((accountType == AccountType::EGP) || (accountType == AccountType::USD && hasUSDAccount()))) {
			auto it = cards.find(accountType);
			return it != cards.end() && it->second.debit != nullptr;
		}
		return false;
	}
	bool hasCreditCard(AccountType accountType) {
		if(((accountType == AccountType::EGP) || (accountType == AccountType::USD && hasUSDAccount()))){
			auto it = cards.find(accountType);
			return it != cards.end() && it->second.credit != nullptr;
		}
		return false;
	}
	bool checkAvailableBalance(double amount, AccountType accountType) {
		if (accountType == AccountType::EGP)
			return EGP.checkAvailableBalance(amount);
		else if (accountType == AccountType::USD && hasUSD)
			return USD.checkAvailableBalance(amount);
		else return false;
	}
	//gets
	double getBalance(AccountType accountType) {
		if (accountType == AccountType::EGP)
			return EGP.getBalance();
		else if (accountType == AccountType::USD && hasUSDAccount())
			return USD.getBalance();
		else return 0.0;
	}
	string getCurrency(AccountType accountType) {
		if (accountType == AccountType::EGP)
			return EGP.getCurrency();
		else if (accountType == AccountType::USD && hasUSDAccount())
			return USD.getCurrency();
		else return "N/A";
	}
	int getIdCard(AccountType accountType, CardType cardType) {
		auto it = cards.find(accountType);
		if (it == cards.end())
			return 0; //Account type not found or Wrong input

		if (cardType == CardType::Credit && hasCreditCard(accountType))
			return it->second.credit->getIdCard();
		else if (cardType == CardType::Debit && hasDebitCard(accountType))
			return it->second.debit->getIdCard();
		else  return 0; //Account type not found or Wrong input
	}
	string getExpiryDateCard(AccountType accountType, CardType cardType) {
		auto it = cards.find(accountType);
		if (it == cards.end())
			return "N/A"; //Account type not found

		if (cardType == CardType::Credit && hasCreditCard(accountType))
			return it->second.credit->getExpiryDateCard();
		else if (cardType == CardType::Debit && hasDebitCard(accountType))
			return it->second.debit->getExpiryDateCard();
		else   return "N/A"; //Wrong input
	}
	double getCreditLimit(AccountType accountType) {
		auto it = cards.find(accountType);
		if (it == cards.end())
			return 0.0; //Account type not found 

		if (!hasCreditCard(accountType))
			return 0.0;//No Credit card
		return it->second.credit->getCreditLimit();
	}
	double getCreditUsed(AccountType accountType) {
		auto it = cards.find(accountType);
		if (it == cards.end())
			return 0.0; //Account type not found 
		if (!hasCreditCard(accountType))
			return 0.0; //No Credit card
		return it->second.credit->getUsedCredit();
	}
	Account* getAccountType(AccountType accountType) {
		if (accountType == AccountType::EGP) return &EGP;
		else if (accountType == AccountType::USD && hasUSD) return &USD;
		else return nullptr;
	}
	const vector<string>&getTransactionHistory() {
		return transactionHistory;
	}
	//sets
	void setBalance(double balance, AccountType accountType) {
		if (accountType == AccountType::EGP){
			EGP.setBalance(balance);
			EGP.setCurrency("EGP");
		}
		else if (accountType == AccountType::USD && hasUSD){
			USD.setBalance(balance);
			USD.setCurrency("USD");
		}
	}
	void setBalance(double balance, double balanceFile, AccountType accountType) {
		if (accountType == AccountType::EGP) {
			EGP.setBalance(balance, balanceFile);
			EGP.setCurrency("EGP");
		}
		else if (accountType == AccountType::USD && hasUSD) {
			USD.setBalance(balance);
			USD.setCurrency("USD");
		}
	}
	void setHasUSD(bool hasUSD) {
		this->hasUSD = hasUSD;
	}
	void setNewCard(AccountType accountType, CardType cardType, int cardId, string expiryDate, double creditLimit) {
		Account* account = getAccountType(accountType);

		if (account == nullptr) {
			cout << "Account not found.\n";
			return;
		}
		if (cardType == CardType::Debit) {
			if (hasDebitCard(accountType)) {
				cout << accountTypeToString(accountType) << " account already have a debit card.\n";
				return;
			}
			setNewDebitCard(accountType, cardId, expiryDate, account);
		}
		else if (cardType == CardType::Credit) {
			if (hasCreditCard(accountType)) {
				cout << accountTypeToString(accountType) << " account already have a credit card.\n";
				return;
			}
			setNewCreditCard(accountType, cardId, expiryDate, account, creditLimit);
		}
	}
	void setUsedCreditCard(AccountType accountType, CardType cardType, double amount) {
		if (amount <= 0)
			return;
		if (!((accountType == AccountType::EGP) || (accountType == AccountType::USD && hasUSDAccount()))) 
			return;
		if (!hasCreditCard(accountType))
			return;
		auto it = cards.find(accountType);
		it->second.credit->setusedCredit(amount);
	}
	//meths
	void displayClientInfo() {
		Person::displayPersonInfo();
		cout << "\nEgyptian account:\n";
		cout << "   ->Balance: " << EGP.getBalance() << " " << EGP.getCurrency() << endl;
		if (hasDebitCard(AccountType::EGP))
			cout << "   ->Has debit card\n";
		if (hasCreditCard(AccountType::EGP)) {
			cout << "   ->Has credit card\n";
			cout << "       ->Credit Limit: " << getCreditLimit(AccountType::EGP) << " " << EGP.getCurrency() << endl;
			cout << "       ->Credit used: " << getCreditUsed(AccountType::EGP) << " " << EGP.getCurrency() << endl;
		}
		if (hasUSD) {
			cout << "\nDollar account:\n";
			cout << "   ->Balance: " << USD.getBalance() << " " << USD.getCurrency() << endl;
			if (hasDebitCard(AccountType::USD))
				cout << "   ->Has debit card\n";
			if (hasCreditCard(AccountType::USD)) {
				cout << "   ->Has credit card\n";
				cout << "      ->Credit Limit: " << getCreditLimit(AccountType::USD) << " " << USD.getCurrency() << endl;
				cout << "      ->Credit used: " << getCreditUsed(AccountType::USD) << " " << USD.getCurrency() << endl;
			}
		}
	}
	void displayClientTransactionHistory() {
		cout << "\nTransaction History:\n";
		for (auto i : transactionHistory) {
			cout << "   ->" << i << endl;
		}
	}
	void add_transaction(string Transaction) {
		if (transactionHistory.size() == maxTransactions)
			transactionHistory.pop_back();
		transactionHistory.insert(transactionHistory.begin(), Transaction);
	}
	string accountTypeToString(AccountType accountType) {
		switch (accountType) {
		case AccountType::EGP:return "EGP";
		case AccountType::USD:return "USD";
		}
		return "unKnown";
	}
	//meths account
	void deposit(double amount, AccountType accountType) {
		if (accountType == AccountType::EGP) {
			EGP.deposit(amount);
			add_transaction("Deposit: " + to_string(amount) + " " + EGP.getCurrency() + " To EGP Account");
		}
		else if (accountType == AccountType::USD && hasUSD) {
			USD.deposit(amount);
			add_transaction("Deposit: " + to_string(amount) + " " + USD.getCurrency() + " To USD Account");
		}
		else cout << "You don't have a USD account.\n";

	}
	void withdraw(double amount, AccountType accountType) {
		if (accountType == AccountType::EGP) {
			EGP.withDraw(amount);
			add_transaction("Withdrawal: " + to_string(amount) + " EGP From EGP Account");
		}
		else if (accountType == AccountType::USD && hasUSD) {
			USD.withDraw(amount);
			add_transaction("Withdrawal: " + to_string(amount) + " USD From USD Account");
		}
		else cout << "You don't have a USD account.\n";
	}
	void transFerTo(double amount, Client* recipient, AccountType accountType) {
		if (this->id == recipient->id) {
			cout << "Cannot transfer to your own account.\n";
			return;
		}
		if (accountType == AccountType::EGP) {
			if (amount <= EGP.getBalance()) {
				withdraw(amount, AccountType::EGP);
				recipient->deposit(amount, AccountType::EGP);
				cout << "Transfer successful! " << amount << " EGP has been transferred to " << recipient->name << ".\n";
				add_transaction("Transferred: " + to_string(amount) + " EGP To " + recipient->name + " (From EGP Account)");
				recipient->add_transaction("Received: " + to_string(amount) + " EGP From " + this->name + " (To EGP Account)");
			}
			else cout << "Transfer failed. You do not have enough balance to complete this transaction.\n";
		}
		else if (accountType == AccountType::USD && hasUSDAccount() && recipient->hasUSDAccount()) {
			if (amount <= USD.getBalance()) {
				withdraw(amount, AccountType::USD);
				recipient->deposit(amount, AccountType::USD);
				cout << "Transfer successful! " << amount << " USD has been transferred to " << recipient->name << ".\n";
				add_transaction("Transferred: " + to_string(amount) + " USD To " + recipient->name + " (From USD Account)");
				recipient->add_transaction("Received: " + to_string(amount) + " USD From " + this->name + " (To USD Account)");
			}
			else cout << "Transfer failed. You do not have enough balance to complete this transaction.\n";
		}
		else {
			if (!hasUSDAccount()) cout << "You don't have a USD account.\n";
			else cout << "recipient doesn't have a USD account.\n";
		}
	}
	//meths DebitCard & CreditCard
	void useDebitCard(AccountType accountType, double amount, Operation operation) {
		if (accountType == AccountType::USD && !hasUSD) {
			cout << "You don't have a USD account.\n";
			return;
		}
		if (!hasDebitCard(accountType)) {
			cout << "No debit card for this account.\n";
			return;
		}
		auto it = cards.find(accountType);
		if (operation == Operation::Deposit) {
			it->second.debit->deposit(amount);
			add_transaction("Deposit By Debit Card In: " + accountTypeToString(accountType) + " Account (" + to_string(amount) + " " + accountTypeToAccount(accountType).getCurrency() + " )");
		}
		else if (operation == Operation::Withdraw) {
			it->second.debit->withdraw(amount);
			add_transaction("Debit Card Withdrawal: " + to_string(amount) + " " + accountTypeToAccount(accountType).getCurrency() + " From " + accountTypeToString(accountType) + " Account");
		}
		else cout << "Invalid operation.\n";
	}
	void useCreditCard(AccountType accountType, double amount, Operation operation) {
		if (accountType == AccountType::USD && !hasUSD) {
			cout << "You don't have a USD account.\n";
			return;
		}
		if (!hasCreditCard(accountType)) {
			cout << "No credit card for this account.\n";
			return;
		}
		auto it = cards.find(accountType);
		if (operation == Operation::Deposit && it->second.credit != nullptr) {
			it->second.credit->deposit(amount);
			add_transaction("Deposit By Credit Card In: " + accountTypeToString(accountType) + " Account (" + to_string(amount) + " " + accountTypeToAccount(accountType).getCurrency() + " )");
		}
		else if (operation == Operation::Withdraw && it->second.credit != nullptr) {
			it->second.credit->withdraw(amount);
			add_transaction("Credit Card Withdrawal: " + to_string(amount) + " " + accountTypeToAccount(accountType).getCurrency() + " From " + accountTypeToString(accountType) + " Account");
		}
		else cout << "Invalid operation.\n";
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

