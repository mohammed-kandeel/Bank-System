#pragma once
#include <iostream>
#include <string>

#include<vector>

#include "Client.h"
#include "Employee.h"
#include "Admin.h"

#include <chrono>
#include <thread>

#include "Validation.h"
using namespace std;


class System{
private:
static vector<Client>clients;


public:

	/////////////////////////////////////
	static bool searshForId(int id) {
		for (auto c : clients) {
			if (c.getID() == id) {
				return true;
			}
		}
		return false;
	}
	static bool is_valid_name(string name) {
		if (!(name.size() >= 5 && name.size() <= 20))
			return false;

		for (auto i : name) {
			if (!((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i == ' ')))
				return false;
		}
		return true;
	}
	static bool is_valid_password(string password) {
		return(password.size() >= 8 && password.size() <= 20);
	}
	static bool is_min_balance(double amount) {
		return (amount >= 1500);
	}
	static void addClient(Client& c) {
		clients.push_back(c);
	}
	static void createNewClient() {
		
		int count{}, id;
		string name, password, currency;
		double balance;
		//ID
		do{
			cout << "Enter Client ID: ";
			cin >> id;
			cin.ignore();
			if (searshForId(id)) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid ID, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;
			
		} while (true);
		//Name
		count = 0;
		do {
			cout << "Enter Client Name: ";
			getline(cin, name);
			if (is_valid_name(name)) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid Name, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Password
		count = 0;
		do {
			cout << "Enter Password: ";
			getline(cin, password);
			if (is_valid_password(password)) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid Password, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Balance
		count = 0;
		do {
			cout << "Enter Balance: ";
			cin >> balance;
			cin.ignore();
			if (is_min_balance(balance)) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid Balance, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Currency
		cout << "Enter Currency: ";
		getline(cin, currency);

		Client c(id, name, password, balance, currency);

		addClient(c);

		cout << "Client added successfully.\n";
		this_thread::sleep_for(chrono::seconds(2));
	}
	static Client* findClientId(int id) {
		for (auto c : clients) {
			if (c.getID() == id )
				return &c;
			else
				return nullptr;
		}
	}
	/////////////////////////////////////
	

	static void run() {
		Validation::welcom_screan();
		do {
			system("CLS");
			int choice;
			cout << "====    Main Menu   ====\n\n";
			cout << "1. login as Client\n";
			cout << "2. login as Employee\n";
			cout << "3. login as Admin\n";
			cout << "4. Exit\n";
			cout << "\nChoice (1-4): ";
			cin >> choice;

			if (choice == 1)
				login_as_client();
			else if (choice == 4) {
				Validation::EX_screan();
				return;
			}

		} while (true);
	}

	//login
	static void login_as_client() {
		
		int id;
		string password;

		cout << "Enter your ID: ";
		cin >> id;
		cin.ignore();
		

		Client* c = findClientId(id);


		//test
		//Client c(111, "mmm", "123", 1500, "EG"), c2(222, "aaa", "1234", 100, "EG");
		//client_menu(c);
	}
	
	//void  login_as_employee() {}
	//void  login_as_admin() {}
	

	//client_menu
	
		//don--------
	static bool anothe_obration() {
		int count{};
		do {
			system("cls");
			cout << "Do you want to make another transaction (y/n)?\n";
			char choice;
			cin >> choice;

			if (choice == 'y' || choice == 'Y') return true;
			else if (choice == 'n' || choice == 'N') return false;
			else {
				cout << "Wrong input\n";
				this_thread::sleep_for(chrono::seconds(2));
				count++;
			}
			if (count == 3)	return false;

		} while (true);
	}



	static int getValidAmount(const string &titel) {
		int count{};
		int amount;

		do{
		
			system("CLS");
			cout << "====   " << titel << "   ====\n\n";
			cout << "(Note: You can " << titel << " in multiples of 100 only, up to a maximum of 12000)\n";
			cout << "\nEnter amount (or press '1' to return): ";
			cin >> amount;

			if (amount == 1) {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return -1;
			}
			if (amount <= 0 || amount > 12000) {
				cout << "\nInvalid amount.\n";
				this_thread::sleep_for(chrono::seconds(3));
				count++;
				if (count == 2)
					return 0;
			}
			else if (amount % 100 != 0) {
				cout << "\nAmount must be 100 or a multiple of 100.\n";
				this_thread::sleep_for(chrono::seconds(3));
				count++;
				if (count == 2) 
					return 0;
			}
			else 
				return amount;

		} while (true);
	}



	static void deposit(Client& c) {
		system("CLS");

		int amount = getValidAmount("Deposit");
		if (amount <= 0)
			return;

		c.deposit(amount);
		cout << "\nDeposit successful. " << amount << " has been added to your account." << endl;
		
		this_thread::sleep_for(chrono::seconds(3));
	}



	static void withdraw(Client& c) {
		system("CLS");

		int amount = getValidAmount("Withdraw");
		if (amount <= 0)
			return;

		if (c.checkAvailableBalance(amount)) {
			c.withDraw(amount);
			cout << "\nWithdrawal successful. " << amount << " has been withdrawn from your account." << endl;
		}
		else
			cout << "\nTransaction failed: Insufficient balance.\n";
		this_thread::sleep_for(chrono::seconds(3));
	}
	static void balance(Client& c) {
		system("CLS");
		cout << "====   Balance   ====\n\n";
		c.checkBalance();
		cout << endl;
		system("pause");
	}

		//-----------
	

	static void transfer(Client& c) {
	
		system("CLS");

		int amount = getValidAmount("Transfer");
		if (amount <= 0)
			return;

		if (c.checkAvailableBalance(amount)) {
			c.transFerTo(amount,c);
			cout << "\nWithdrawal successful. " << amount << " has been withdrawn from your account." << endl;
		}
		else
			cout << "\nTransaction failed: Insufficient balance.\n";
		this_thread::sleep_for(chrono::seconds(3));



	}

	static 	void  client_menu(Client& c) {
		system("cls");
		int count{};
		do{
			cout << "====    Client Menu   ====\n\n";
			cout << "1. Deposit\n";
			cout << "2. Withdraw\n";
			cout << "3. Balance\n";
			cout << "4. Transfer\n";
			cout << "5. Main Menu\n";
			cout << "\nChoice (1-5): ";

			char choice;
			cin >> choice;

			switch (choice) {
				case '1':deposit(c); break;
				case '2':withdraw(c); break;
				case '3':balance(c); break;
				case '4':transfer(c); break;
				case '5':return; break;
				default: { cout << "Wrong input\n"; count++; } break;
			}
			if (count == 3)
				return;
			if (anothe_obration() == false)
				return;

		} while (true); 
	}














	//Employee_menu
	//void  employee_menu(Employee& e) {

	//}
	


	//Admin_menu
	//void  admin_menu(Admin& a) {

	//}

};

