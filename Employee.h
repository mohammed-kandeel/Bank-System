#pragma once
#include"Client.h"
#include <map>

#include <chrono>
#include <thread>

class FilesHelper;

class Employee :public Person {
protected:
	//atts
	double salary;
	string currency;
public:
	//All employees Data <ID, *pointer> 
	static map<int,Employee*>employees;
	static void removeAllEmployees() {
		for (auto& i : Employee::employees) {
			delete i.second;
		}
		Employee::employees.clear();
	}
	//cons
	Employee(){
		this->salary = 0.0;
		this->currency = "EG";
	}
	Employee(int id, string name, string password, double salary) : Person(id, name, password) {
		setSalary(salary);
		this->currency = "EG";
	}
	//des
	~Employee(){}
	//gets
	double getSalary() {
		return salary;
	}
	string getCurrency() {
		return currency;
	}
	//sets
	void setSalary(double salary) {
		if (Validation::is_min_salary(salary))
			this->salary = salary;
		else
			cout << "salary must be >= 5000\n";
	}
	//meths
	void displayEmployeeInfo() {
		Person::displayPersonInfo();
		cout << "Salary: " << salary << " " << currency << endl;
	}
	void addClient(Client* client) {
		Client::clients.insert({ client->getID(),client });
		cout << "Client added successfully.\n";
	}

	void addDebitCard(Client* client, AccountType accountType, int cardId, string expiryDate) {
		client->setNewCard(accountType, CardType::Debit, cardId, expiryDate, 0);

	}
	void addCreditCard(Client* client, AccountType accountType, int cardId, string expiryDate, double creditLimit) {
		client->setNewCard(accountType, CardType::Credit, cardId, expiryDate, creditLimit);
	}
	void addUSDAccount(Client* client, double balance) {
		client->setHasUSD(true);
		client->setBalance(balance, AccountType::USD);
	}

	Client* searchClient(int id) {
		for (auto& i : Client::clients) {
			if (i.first == id)
				return i.second;
		}
		return nullptr;
	}
	void listClient() {
		for (auto& i : Client::clients) {
			i.second->displayClientInfo();
			cout << "\n----------------------\n\n";
		}
	}
	void listClientWithTransactions() {
		for (auto& i : Client::clients) {
			i.second->displayClientInfo();
			i.second->displayClientTransactionHistory();
			cout << "\n----------------------\n\n";
		}
	}
	void editClient(int id, string name, string password, double balance, AccountType accountType) {
		Client* c = searchClient(id);
		if (c == nullptr) return;

		if (name != "-1" ) c->setName(name);                           // '-1' not editing
		else if (password != "-1") c->setPassword(password);
		else if (balance != -1 ) c->setBalance(balance, accountType);
		else return;
	}
};