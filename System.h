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

	void run() {
		system("CLS");

		do{

			Validation::welcom_screan();
			int choice;
			cout << "1. login as Client\n";
			cout << "2. login as Employee\n";
			cout << "3. login as Admin\n";
			cout << "4. Exit\n";
			cin >> choice;

			if (choice == 1)
				login_as_client();
			//else if (choice == 2)
			//	login_as_employee();
			//else if (choice == 3)
			//	login_as_admin();


		} while (true);


	}

	//login
	void  login_as_client() {




		//test
		Client c(111, "mmm", "123", 1500, "EG"), c2(222, "aaa", "1234", 100, "EG");
		client_menu(c);
	}
	//void  login_as_employee() {

	//}
	//void  login_as_admin() {

	//}
	

	//client_menu
	
		//don--------
	bool anothe_obration() {
		system("cls");
		int count{};
		do {
			cout << "Do you want to make another transaction (y/n)?\n";
			char choice;
			cin >> choice;

			if (choice == 'y' || choice == 'Y') return true;
			else if (choice == 'n' || choice == 'N') return false;
			else {
				cout << "Wrong input\n";
				count++;
			}
			if (count == 3)	return false;

		} while (true);
	}
	void deposit(Client& c) {
		system("CLS");
		



		int amount;
		cout << "====   Deposit   ====\n\n";
		cout << "(Note: You can deposit in multiples of 100 only, up to a maximum of 12000)\n";
		cout << "\nEnter amount (or press '1' to return): ";
		cin >> amount;
		
		if (amount == 1) {
			client_menu(c);
		}
		else if (amount <= 0) {
			cout << "\nInvalid amount.\n";
		}
		else if (amount > 12000) {
			cout << "\nInvalid amount.\n";
		}
		else if (amount % 100 != 0) {
			cout << "\nAmount must be 100 or a multiple of 100.\n";
		}
		else{
			c.deposit(amount);
			cout << "\nDeposit successful. " << amount << " has been added to your account." << endl;
		}
		this_thread::sleep_for(chrono::seconds(3));
		anothe_obration() ? client_menu(c) : run();
	}
	void withdraw(Client& c) {
		system("CLS");
		int amount;

		cout << "====   Withdraw   ====\n\n";
		cout << "(Note: You can withdraw in multiples of 100 only, up to a maximum of 12000)\n";
		cout << "\nEnter amount (or press '1' to return): ";
		cin >> amount;

		if (amount == 1) {
			client_menu(c);
		}
		else if (amount <= 0) {
			cout << "\nInvalid amount.\n";
		}
		else if (amount > 12000) {
			cout << "\nInvalid amount.\n";
		}
		else if (amount % 100 != 0) {
			cout << "\nAmount must be 100 or a multiple of 100.\n";
		}
		else if (c.checkAvailableBalance(amount)) {
			c.withDraw(amount);
			cout << "\nWithdrawal successful. " << amount << " has been withdrawn from your account." << endl;
		}
		else
			cout << "\nTransaction failed: Insufficient balance.\n";
		this_thread::sleep_for(chrono::seconds(3));
		anothe_obration() ? client_menu(c) : run();

	}
	void balance(Client& c) {
		system("CLS");
		cout << "====   Balance   ====\n\n";
		c.checkBalance();
		cout << endl;
		system("pause");
		anothe_obration() ? client_menu(c) : run();

	}

		//-----------
	

	void transfer(Client& c) {}


	void  client_menu(Client& c) {
		system("cls");
		int count{};
		do{
			cout << "\nClient Menu:\n";
			cout << "1. Deposit\n";
			cout << "2. Withdraw\n";
			cout << "3. Balance\n";
			cout << "4. Transfer\n";
			cout << "5. Login menu\n";
			cout << "6. Exit\n";
			cout << "\nChoice (1-6): ";

			char choice;
			cin >> choice;

			switch (choice) {
				case '1':deposit(c); break;
				case '2':withdraw(c); break;
				case '3':balance(c); break;
				case '4':transfer(c); break;
				case '5':run(); break;
				case '6':return; break;
				defaul cout << "Wrong input\n"; count++; break;
			}

			if (count == 3)	run();

		} while (true); 
	}

	//Employee_menu
	//void  employee_menu(Employee& e) {

	//}
	


	//Admin_menu
	//void  admin_menu(Admin& a) {

	//}

};

