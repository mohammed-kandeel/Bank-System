#pragma once
#include "FileManager.h"

class ClientManager {
private:
	static void showError(string message) {
		cout << "\n" << message << "\n";
		this_thread::sleep_for(chrono::seconds(3));
	}
	
	static bool cancelOperation(string temp) {
		if (temp == "0") {
			system("cls");
			showError("\nOperation cancelled. Returning to main menu...\n");
			return true;
		}
		return false;
	}
	
	static bool maxTry(int count) {
		if (count == 3) {
			showError("Too many invalid attempts. Returning to main menu...\n");
			return true;
		}
		return false;
	}

public:
	static void printClientMenu() {
		system("cls");
		cout << "=====   Client Menu   =====\n\n";
		cout << "1. Account Information\n";
		cout << "2. Change Password\n";
		cout << "3. Deposit Funds\n";
		cout << "4. Withdraw Funds\n";
		cout << "5. Transfer Funds\n";
		cout << "6. Account Balance\n";
		cout << "7. Transaction History\n";
		cout << "0. Logout\n";
		cout << "\nSelect an option (0-7): ";
	}
	
	static void updatePassword(Person* person) {
		string newPassword, oldPassword;
		system("cls");
		cout << "\n======== Change Password ========\n\n";

		cout << "Enter your old password (or type 0 to go back): ";
		getline(cin, oldPassword);
		
		if (cancelOperation(oldPassword))
			return;
			
		if (person->getPassword() != oldPassword) {
			showError("\nWrong password! Going back to menu...\n");
			return;
		}

		system("cls");
		cout << "\n======== Change Password ========\n\n";
		cout << "Enter your new password: ";
		getline(cin, newPassword);
		
		if (!Validation::is_valid_password(newPassword)) {
			showError("\nPassword is not good! Going back to menu...\n");
			return;
		}

		person->setPassword(newPassword);
		cout << "\nPassword changed successfully!\n";
		this_thread::sleep_for(chrono::seconds(3));
	}
	
	static Client* login(int id, string password) {
		auto i = Client::clients.find(id);
		if (i == Client::clients.end() || i->second->getPassword() != password) {
			showError("Wrong ID or password. Going back to menu.\n");
			return nullptr;
		}
		return i->second;
	}
	
	static bool clientOptions(Client* client) {
		int count = 0;
		string choice;

		while (true) {
			printClientMenu();
			getline(cin, choice);

			if (choice == "1") {
				system("cls");
				cout << "\n======== Account Information ========\n\n";
				client->displayClientInfo();
				cout << endl;
				system("pause");
				return true;
			}
			else if (choice == "2") {
				updatePassword(client);
				return true;
			}
			else if (choice == "3") {
				system("cls");
				cout << "\nDeposit feature\n";
				system("pause");
				return true;
			}
			else if (choice == "4") {
				system("cls");
				cout << "\nWithdraw feature\n";
				system("pause");
				return true;
			}
			else if (choice == "5") {
				system("cls");
				cout << "\nTransfer feature\n";
				system("pause");
				return true;
			}
			else if (choice == "6") {
				system("cls");
				cout << "\n======== Account Balance ========\n\n";
				cout << "EGP Balance: " << client->getBalance() << " EGP\n";
				if (client->hasUSDAccount()) {
					cout << "USD Balance: " << client->getUSDBalance() << " USD\n";
				}
				else {
					cout << "USD Account: Not Available\n";
				}
				cout << endl;
				system("pause");
				return true;
			}
			else if (choice == "7") {
				system("cls");
				cout << "\nTransaction history\n";
				system("pause");
				return true;
			}
			else if (choice == "0") {
				return false;
			}
			else {
				showError("Invalid choice! Please try again.\n");
				count++;
				if (maxTry(count)) 
					return false;
			}
		}
	}
};
