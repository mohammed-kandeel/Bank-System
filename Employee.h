#pragma once
#include"Client.h"
#include <map>

#include <chrono>
#include <thread>

class FilesHelper;
class FileManager;

class Employee :public Person {
protected:
	//atts
	double salary;
	string currency;
public:
	//Data
	static map<int,Employee>employees;
	//bool operator<(const Employee& e) const {  // This operator is required in set to compare clients and sort data
	//	return this->id < e.id;
	//}
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
	void saveNewClienttoFile(Client& c); // .ccp

	void addClient(Client& client) {
		Client::clients.insert({ client.getID(),client });
		saveNewClienttoFile(client);
		cout << "Client added successfully.\n";
		this_thread::sleep_for(chrono::seconds(4));
	}
	Client* searchClient(int id) {
		for (auto& i : Client::clients) {
			if (i.first == id)
				return &i.second;
		}
		return nullptr;
	}
	void listClient() {
		for (auto& i : Client::clients) {
			i.second.displayClientInfo();
			cout << "\n----------------------\n\n";
		}
	}
	void editClient(int id, string name, string password, double balance, string accountType) {
		Client* c = searchClient(id);
		if (c == nullptr) return;

		if (name != "-1" && name != "-2") c->setName(name);                           //'-2'  Cancel option / '-1' so many rong input
		else if (password != "-1" && password != "-2") c->setPassword(password);
		else if (balance != -1 && balance != -2) c->setBalance(balance, accountType);
		else return;
	}





	//move  this methods to  EmployeeManager class  phase 3
	int getNewClientIDfromFile(); // .ccp
	Client *getClientInfo() {
		int id, count{};
		string name, password;
		double balance;

		id = 1 + getNewClientIDfromFile();
		cout << "ID: " << id << endl;

		//Name
		count = 0;
		do {
			system("cls");
			cout << "ID: " << id << endl << endl;
			cout << "Enter Client Name (or press '0' to Cancel): ";
			getline(cin, name);

			if (name == "0") {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return nullptr;
			}
			if (!(Validation::is_valid_name(name))) {
				count++;
				if (count == 2)
					return nullptr;
				cout << "Invalid Name, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;
		} while (true);

		//Password
		count = 0;
		do {
			system("cls");
			cout << "ID: " << id << endl;
			cout << "Name: " << name << endl << endl;
			cout << "Enter Password: ";
			getline(cin, password);
			if (!(Validation::is_valid_password(password))) {
				count++;
				if (count == 2)
					return nullptr;
				cout << "Invalid Password, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);

		//Balance
		count = 0;
		do {
			system("cls");
			cout << "ID: " << id << endl;
			cout << "Name: " << name << endl;
			cout << "Password: " << password << endl << endl;
			cout << "Enter Balance: ";
			cin >> balance;
			cin.ignore();
			if (!(Validation::is_min_balance(balance))) {
				count++;
				if (count == 2)
					return nullptr;
				cout << "Invalid Balance, The Min Balance Is 1500, Try Again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;
		} while (true);

		Client* c = new Client(id, name, password, balance);
		system("cls");
		cout << "ID: " << id << endl;
		cout << "Name: " << name << endl;
		cout << "Password: " << password << endl;
		//cout << "Balance: " << balance << " " << c->getCurrency() << endl << endl;
		return c;
	}
};