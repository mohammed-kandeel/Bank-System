#pragma once
#pragma once
#include <iostream>

#include <cstdlib>  

#include "ClientManager.h"
#include "EmployeeManager.h"
#include "AdminManager.h"
using namespace std;

class Screens {
private:
	static void showError(string message) {
		cout << "\n" << message << "\n";
		this_thread::sleep_for(chrono::seconds(3));
	}
	static bool maxTry(int count) {
		if (count == 3) {
			showError("Too many invalid attempts. Returning to main menu...\n");
			return true;
		}
		else return false;
	}
	static bool tryParseNumber(string& input, int& num) {
		try {
			size_t idx;
			num = stod(input, &idx);  // idx = آخر موضع حوِّلته stod
			// لو في أي حاجة زيادة بعد الرقم، اعتبره خطأ
			return idx == input.length();
		}
		catch (invalid_argument&) { return false; }
		catch (out_of_range&) { return false; }
	}
	static bool cancelOperation(string temp) {
		if (temp == "0") {
			system("cls");
			showError("\nOperation cancelled. Returning to main menu...\n");
			return true;
		}
		else return false;
	}




	static void welcome()
	{
		cout << "  ##      ## ######## ##        ######   #######  ##     ##   ##########   #######     \n";
		cout << "  ##  ##  ## ##       ##       ##    ## ##     ## ###   ###       ##      ##     ##    \n";
		cout << "  ##  ##  ## ##       ##       ##       ##     ## #### ####       ##      ##     ##     \n";
		cout << "  ##  ##  ## ######   ##       ##       ##     ## ## ### ##       ##      ##     ##     \n";
		cout << "  ##  ##  ## ##       ##       ##       ##     ## ##     ##       ##      ##     ##     \n";
		cout << "  ##  ##  ## ##       ##       ##    ## ##     ## ##     ##       ##      ##     ##     \n";
		cout << "   ###  ###  ######## ########  ######   #######  ##     ##       ##       #######      \n";
	}
	static void ThankYou()
	{
		cout << "######## ##     ##    ###    ##    ## ##    ##    ##    ##  #######  ##     ##   \n";
		cout << "   ##    ##     ##   ## ##   ###   ## ##   ##      ##  ##  ##     ## ##     ##   \n";
		cout << "   ##    ##     ##  ##   ##  ####  ## ##  ##        ####   ##     ## ##     ##   \n";
		cout << "   ##    ######### ##     ## ## ## ## #####          ##    ##     ## ##     ##   \n";
		cout << "   ##    ##     ## ######### ##  #### ##  ##         ##    ##     ## ##     ##   \n";
		cout << "   ##    ##     ## ##     ## ##   ### ##   ##        ##    ##     ## ##     ##   \n";
		cout << "   ##    ##     ## ##     ## ##    ## ##    ##       ##     #######   #######    \n";

	}


	static void bankName() {
		cout << "===============================" << endl;
		cout << " \n\n";
		cout << "    ######  #### ########     ########     ###    ##    ## ##    ##\n";
		cout << "   ##    ##  ##  ##     ##    ##     ##   ## ##   ###   ## ##   ##\n";
		cout << "   ##        ##  ##     ##    ##     ##  ##   ##  ####  ## ##  ##\n";
		cout << "   ##        ##  ########     ########  ##     ## ## ## ## ##### \n";
		cout << "   ##        ##  ##     ##    ##     ## ######### ##  #### ##  ##\n";
		cout << "   ##    ##  ##  ##     ##    ##     ## ##     ## ##   ### ##   ##\n";
		cout << "    ######  #### ########     ########  ##     ## ##    ## ##    ##\n";
		cout << " \n\n";
		cout << "===============================" << endl;
	}
	/*static void welcome() {
		cout << "  ##      ## ######## ##        ######   #######  ##     ##     ##  ###\n";
		cout << "  ##  ##  ## ##       ##       ##    ## ##     ## ###   ###    ####   ##\n";
		cout << "  ##  ##  ## ##       ##       ##       ##     ## #### ####     ##     ##\n";
		cout << "  ##  ##  ## ######   ##       ##       ##     ## ## ### ##            ##\n";
		cout << "  ##  ##  ## ##       ##       ##       ##     ## ##     ##     ##     ##\n";
		cout << "  ##  ##  ## ##       ##       ##    ## ##     ## ##     ##    ####   ##\n";
		cout << "   ###  ###  ######## ########  ######   #######  ##     ##     ##  ###\n";
	}*/



public:

	// ===== Main Login Options =====
	static void loginOptions() {
		system("cls");
		cout << "\nLogin as: \n";
		cout << "1. Client\n";
		cout << "2. Employee\n";
		cout << "3. Admin\n";
		cout << "0. close program\n";
		cout << "\nEnter your choice (0-3): ";
	}

	static int loginAs() {
		string choice;
		while (true) {
			loginOptions();
			getline(cin, choice);

			switch (choice[0]) {
				case '1': {  return 1; } break;
				case '2': {  return 2; } break;
				case '3': {  return 3; } break;
				case '0': { return -1; } break;
				default: { showError("Wrong input\n"); return -1; } break;
			}
		}
	}

	static int getnum(string line) {
		string temp;
		int count;
		int num;

		count = 0;
		do {
			system("cls");
			cout << line << endl;
			cout << "->Enter ID : ";
			getline(cin, temp);

			if (cancelOperation(temp))
				return-1;
			if (!tryParseNumber(temp, num)) {
				count++;
				if (maxTry(count)) return -1;
				showError("Invalid input. Please enter a valid number.\n");
				continue;
			}
			else
				return num;
		} while (true);
	}




	static void loginScreen(int c) {
		int id;
		string password, line;
		Client* client;
		Employee *employee;
		Admin *admin;


		switch (c) {
			case 1: { line = "=====    Client    =====\n\n"; } break;
			case 2: { line = "=====   Employee   =====\n\n"; } break;
			case 3: { line = "=====    Admin     =====\n\n"; } break;
		}

		id = getnum(line);
		if (id == -1)
			return;

		cout << line;
		cout << "Id :" << id << endl;
		cout << "->Enter password : ";
		getline(cin, password);
		
		switch (c) {
			case 1: { client = ClientManager::login(id, password); } break;
			case 2: { employee = EmployeeManager::login(id, password); } break;
			//case 3: { person=AdminManager } break;
		}
		if (person == nullptr)
			return;

		else {
			while (true) {
				bool keep = false;
				switch (c) {
				case 1: { keep = ClientManager::clientOptions(client); } break;
				case 2: { keep = EmployeeManager::employeeOptions(employee); } break;
				case 3: { line = "=====    Admin     =====\n\n"; } break;
				}
				if (!keep) break;
			}

		}
	}


	static void invalid(int c) {
		cout << "\nInvalid choice (" << c << "), try again.\n";
	}
	static void logout() {
		cout << "\nYou have been logged out.\n";
	}






	// ====== LOGIN SYSTEM ======
	static Client* clientLogin() {
		int id; string pass;
		cout << "Enter Client ID: "; cin >> id;
		cout << "Enter Password: "; cin >> pass;

		auto it = Client::clients.find(id);
		if (it != Client::clients.end() && it->second->getPassword() == pass) {
			return it->second;
		}
		cout << "Invalid client credentials.\n";
		return nullptr;
	}

	static Employee* employeeLogin() {
		int id; string pass;
		cout << "Enter Employee ID: "; cin >> id;
		cout << "Enter Password: "; cin >> pass;

		auto it = Employee::employees.find(id);
		if (it != Employee::employees.end() && it->second->getPassword() == pass) {
			return it->second;
		}
		cout << "Invalid employee credentials.\n";
		return nullptr;
	}

	static Admin* adminLogin() {
		int id; string pass;
		cout << "Enter Admin ID: "; cin >> id;
		cout << "Enter Password: "; cin >> pass;

		auto it = Admin::admins.find(id);
		if (it != Admin::admins.end() && it->second->getPassword() == pass) {
			return it->second;
		}
		cout << "Invalid admin credentials.\n";
		return nullptr;
	}





	// ===== Client Screens =====
	static void showClientMenu(Client* c) {
		system("cls");
		cout << "=== Client Menu ===\n";
		system("pause");
		int choice;
		do {
			system("cls");
			cout << "--- Client Menu ---\n";
			cout << "1. Display Info\n";
			cout << "2. Check Balance\n";
			cout << "3. Deposit\n";
			cout << "4. Withdraw\n";
			cout << "5. Logout\n";
			cout << "Choose: ";
			cin >> choice;

			switch (choice) {
			case 1: c->displayClientInfo(); break;
			case 2: cout << "EGP Balance: " << c->getBalance(AccountType::EGP) << endl; break;
			case 3: {
				double amount; cout << "Enter deposit amount: "; cin >> amount;
				c->deposit(amount, AccountType::EGP);
				break;
			}
			case 4: {
				double amount; cout << "Enter withdraw amount: "; cin >> amount;
				c->withdraw(amount, AccountType::EGP);
				break;
			}
			case 5: logout(); break;
			default: invalid(choice); break;
			}
			system("pause");
		} while (choice != 5);
	}

	// ===== Employee Screens =====
	static void showEmployeeMenu(Employee* e) {
		system("cls");
		cout << "=== Employee Menu ===\n";
		system("pause");
		int choice;
		do {
			system("cls");
			cout << "--- Employee Menu ---\n";
			cout << "1. List Clients\n";
			cout << "2. Add Client\n";
			cout << "3. Logout\n";
			cout << "Choose: ";
			cin >> choice;

			switch (choice) {
			case 1: e->listClient(); break;
			case 2: cout << "(Demo) Add Client\n"; break;
			case 3: logout(); break;
			default: invalid(choice); break;
			}
			system("pause");
		} while (choice != 3);
	}

	// ===== Admin Screens =====
	static void showAdminMenu(Admin* a) {
		system("cls");
		cout << "=== Admin Menu ===\n";
		system("pause");
		int choice;
		do {
			system("cls");
			cout << "--- Admin Menu ---\n";
			cout << "1. List Employees\n";
			cout << "2. Add Employee\n";
			cout << "3. Logout\n";
			cout << "Choose: ";
			cin >> choice;

			switch (choice) {
			case 1: a->listEmployee(); break;
			case 2: cout << "(Demo) Add Employee\n"; break;
			case 3: logout(); break;
			default: invalid(choice); break;
			}
			system("pause");
		} while (choice != 3);
	}

	// ===== Run App =====
	static void runApp() {
		bankName();
		system("pause");
		system("cls");
		welcome();

		int option;
		do {
			loginOptions();
			cin >> option;
			if (option == 1) {
				int role = loginAs();
				if (role == 1) {
					Client* c = clientLogin();
					if (c) showClientMenu(c);
				}
				else if (role == 2) {
					Employee* e = employeeLogin();
					if (e) showEmployeeMenu(e);
				}
				else if (role == 3) {
					Admin* a = adminLogin();
					if (a) showAdminMenu(a);
				}
				else {
					invalid(role);
				}
			}
			else if (option == 2) {
				cout << "Goodbye!\n";
			}
			else {
				invalid(option);
			}
		} while (option != 2);
	}
};

