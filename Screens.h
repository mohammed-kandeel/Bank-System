#pragma once
#include "ClientManager.h"
#include "EmployeeManager.h"
#include "AdminManager.h"
using namespace std;

class Screens {
private:
	static void invalid(int c) {
		cout << "\nInvalid choice (" << c << "), try again.\n";
	}
	static void logout() {
		cout << "\nYou have been logged out.\n";
	}

	static void showError(string message) {
		cout << "\n" << message << "\n";
		this_thread::sleep_for(chrono::seconds(3));
	}
	static int getnum(string line) {
		string temp;
		int count;
		int num;

		count = 0;
		do {
			system("cls");
			cout << line;
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

	static bool clientLogin(int id, string password) {
		Client* client = getClient(id, password);
		if (client == nullptr) return false;
		while (true) {
			if (!ClientManager::clientOptions(client)) return false;
		}
	}
	static bool employeeLogin(int id, string password) {
		Employee* employee = getEmployee(id, password);
		if (employee == nullptr) return false;
		while (true) {
			if (!EmployeeManager::employeeOptions(employee)) return false;
		}
	}
	static bool adminLogin(int id, string password) {
		Admin* employee = getadmin(id, password);
		if (employee == nullptr) return false;
		while (true) {
			if (!AdminManager::employeeOptions(employee)) return false;
		}
	}

	static Client* getClient(int id, string password) {
		return ClientManager::login(id, password);
	}
	static Employee* getEmployee(int id, string password) {
		return EmployeeManager::login(id, password);
	}
	static Admin* getadmin(int id, string password) {
		return AdminManager::login(id, password);
	}

	static void welcome() {
		cout << "\n\n\n\n\n\n\n\n";
		cout << "  ##      ## ######## ##        ######   #######  ##     ##   ##########   #######     \n";
		cout << "  ##  ##  ## ##       ##       ##    ## ##     ## ###   ###       ##      ##     ##    \n";
		cout << "  ##  ##  ## ##       ##       ##       ##     ## #### ####       ##      ##     ##     \n";
		cout << "  ##  ##  ## ######   ##       ##       ##     ## ## ### ##       ##      ##     ##     \n";
		cout << "  ##  ##  ## ##       ##       ##       ##     ## ##     ##       ##      ##     ##     \n";
		cout << "  ##  ##  ## ##       ##       ##    ## ##     ## ##     ##       ##      ##     ##     \n";
		cout << "   ###  ###  ######## ########  ######   #######  ##     ##       ##       #######      \n";
	}
	static void bankName() {
		//system("CLS");
		system("color 0b");
		cout << "\n\n\n";
		cout << "                                                  ######  #### ########     ########     ###    ##    ## ##    ##\n";
		cout << "                                                 ##    ##  ##  ##     ##    ##     ##   ## ##   ###   ## ##   ##\n";
		cout << "                                                 ##        ##  ##     ##    ##     ##  ##   ##  ####  ## ##  ##\n";
		cout << "                                                 ##        ##  ########     ########  ##     ## ## ## ## ##### \n";
		cout << "                                                 ##        ##  ##     ##    ##     ## ######### ##  #### ##  ##\n";
		cout << "                                                 ##    ##  ##  ##     ##    ##     ## ##     ## ##   ### ##   ##\n";
		cout << "                                                  ######  #### ########     ########  ##     ## ##    ## ##    ##\n";
		this_thread::sleep_for(chrono::seconds(5));
		system("color 0F");
		system("cls");
	}
	static void ThankYou() {
		system("CLS");
		system("color 0b");
		cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
		cout << "                                        ######## ##     ##    ###    ##    ## ##    ##    ##    ##  #######  ##     ##   \n";
		cout << "                                           ##    ##     ##   ## ##   ###   ## ##   ##      ##  ##  ##     ## ##     ##   \n";
		cout << "                                           ##    ##     ##  ##   ##  ####  ## ##  ##        ####   ##     ## ##     ##   \n";
		cout << "                                           ##    ######### ##     ## ## ## ## #####          ##    ##     ## ##     ##   \n";
		cout << "                                           ##    ##     ## ######### ##  #### ##  ##         ##    ##     ## ##     ##   \n";
		cout << "                                           ##    ##     ## ##     ## ##   ### ##   ##        ##    ##     ## ##     ##   \n";
		cout << "                                           ##    ##     ## ##     ## ##    ## ##    ##       ##     #######   #######    \n";
		this_thread::sleep_for(chrono::seconds(3));
		system("color 0F");
		system("cls");
	}

	static void loginOptions() {
		system("cls");
		cout << "=====   Login as   =====\n\n";
		cout << "1. Client\n";
		cout << "2. Employee\n";
		cout << "3. Admin\n";
		cout << "0. Close program\n";
		cout << "\nEnter your choice (0-3): ";
	}
	static int loginAs() {
		string choice;
		while (true) {
			loginOptions();
			getline(cin, choice);

			switch (choice[0]) {
				case '1':  return 1; break;
				case '2':  return 2; break;
				case '3':  return 3; break;
				case '0':  return 0; break;
				default:  showError("Wrong input\n"); break;
			}
		}
	}
	static void loginScreen(int c) {
		int id;
		string password, line;

		switch (c) {
		case 1: line = "=====    Client    =====\n\n"; break;
		case 2: line = "=====   Employee   =====\n\n"; break;
		case 3: line = "=====    Admin     =====\n\n"; break;
		default: return;
		}

		id = getnum(line);
		if (id == -1) return;

		system("cls");
		cout << line;
		cout << "->Id : " << id << endl;
		cout << "->Enter password : ";

		getline(cin, password);

		switch (c) {
		case 1: if (!clientLogin(id, password)) return; break;
		case 2: if (!employeeLogin(id, password)) return; break;
		case 3: if (!adminLogin(id, password)) return; break; 
		}
	}

public:
	static void runApp() {
		FileManager::getAllData();
		welcome();
		bankName();

		while (true) {
			int i = loginAs();
			if (i == 0)
				break;
			loginScreen(i);
		}

		FileManager::updateAllData();
		ThankYou();
	}
};

