#pragma once
#include <iostream>
#include <string>

#include "Client.h"
#include "Employee.h"
#include "Admin.h"

#include <chrono>
#include <thread>

#include "Validation.h"

class System{
private:



public:


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
	static void  login_as_client() {




		//test
		Client c(111, "mmm", "123", 1500, "EG"), c2(222, "aaa", "1234", 100, "EG");
		client_menu(c);
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
				break;
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

