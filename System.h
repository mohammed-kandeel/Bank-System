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

	}
	//void  login_as_employee() {

	//}
	//void  login_as_admin() {

	//}
	

	//client_menu
	
		//don--------
	bool anothe_obration() {
		int count{};
		do {
			system("cls");
			cout << "Do you want to make another transaction\n";
			cout << " 1. Yes\n";
			cout << " 2. No\n";
			string choice;
			cin >> choice;

			if (choice == "1" || choice == "yes" || choice == "YES") return true;
			else if (choice == "2" || choice == "no" || choice == "NO") return false;
			else {
				cout << "Wrong input\n";
				count++;
			}
			if (count == 3)	return false;

		} while (true);
	}
		
		//don--------
	void deposit(Client& c) {
		double amount;
		cout << "====   Deposit   ====\n\n";
		cout << "Enter amount: ";
		cin >> amount;

		c.deposit(amount);
		cout << "Deposit successful. " << amount << " has been added to your account." << endl;
		this_thread::sleep_for(chrono::seconds(3));
		anothe_obration() ? client_menu(c) : run();
	}
		//-----------

	void withdraw(Client& c){
		double amount;
		cout << "Enter amount: ";
		cin >> amount;

		if (c.checkAvailableBalance(amount)) {
			c.withDraw(amount);
			cout << "Withdrawal successful. " << amount << " has been withdrawn from your account." << endl;
		}
		else
			cout << "Transaction failed: Insufficient balance.\n";
	}
	void balance(Client& c) {}
	void transfer(Client& c) {}


	void  client_menu(Client& c) {
		int count{};
		do{

			cout << "\nClient Menu:\n1";
			cout << "1. Deposit\n";
			cout << "2. Withdraw\n";
			cout << "3. Balance\n";
			cout << "4. Transfer\n";
			cout << "5. Login menu\n";
			cout << "6. Exit\n";
			
			string choice;
			cin >> choice;

			if (choice == "1" || choice == "deposit") deposit(c);
			else if (choice == "2" || choice == "withdraw") withdraw(c);
			else if (choice == "3" || choice == "balance") balance(c);
			else if (choice == "4" || choice == "transfer") transfer(c);
			else {
				cout << "Wrong input\n";
				count++;
			}

			if (count == 3)	run();

		} while (true); 
	}


	//void  employee_menu(Employee& e) {

	//}
	//void  admin_menu(Admin& a) {

	//}




	//cout << "Transaction failed: Insufficient balance.\n";
};

