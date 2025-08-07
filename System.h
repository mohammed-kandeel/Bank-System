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
	


	bool anothe_obration() {
		int count{};
		do {
			cout << "Do you wont to do another obtion?\n";
			cout << " 1. Yes\n";
			cout << " 2. No\n";
			string choice;
			cin >> choice;

			if (count == 2)
				return false;
			if (choice == "1")
				return true;
			else if (choice == "2")
				return false;
			else {
				cout << "Rong input\n";
				count++;
				this_thread::sleep_for(chrono::seconds(3));
				system("cls");
			}
		} while (true);
	}
	//client_menu
	bool Deposit(Client& c) {
		double amount;
		cout << "Enter amount: ";
		cin >> amount;

		c.deposit(amount);
		cout << "Deposit successful. " << amount << " has been added to your account." << endl;
		this_thread::sleep_for(chrono::seconds(2));
		anothe_obration() ? client_menu(c) : run();
		system("cls");

	}

	void  client_menu(Client& c) {
		do{

			cout << "\nClient Menu:\n1";
			cout << "1. Deposit\n";
			cout << "2. Withdraw\n";
			cout << "3. Balance\n";
			cout << "4. Transfer\n";
			cout << "5. Login menu\n";
			cout << "6. Exit\n";
			
			int choice;
			cin >> choice;
			system("cls");
			if (choice == 1){
				Deposit(c);
			}
			else if (choice == 2) {
				double amount;
				cout << "Enter amount: ";
				cin >> amount;

				if (c.checkAvailableBalance(amount)) {
					c.withDraw(amount);
					cout << "Withdrawal successful. " << amount << " has been withdrawn from your account." << endl;
				}
				else
					cout << "Transaction failed: Insufficient balance.\n";
				system("cls");

			}
			else if (choice == 3){}


		} while (true); 

	}


	//void  employee_menu(Employee& e) {

	//}
	//void  admin_menu(Admin& a) {

	//}




	//cout << "Transaction failed: Insufficient balance.\n";
};

