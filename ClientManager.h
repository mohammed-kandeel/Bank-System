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
		cout << "1. Check My Account Info\n";
		cout << "2. Change My Password\n";
		cout << "3. Put Money In Account\n";
		cout << "4. Take Money Out\n";
		cout << "5. Send Money To Someone\n";
		cout << "6. See How Much Money I Have\n";
		cout << "7. See My Transaction History\n";
		cout << "0. Go Back To Login\n";
		cout << "\nWhat do you want to do? (0-7): ";
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
		int tryCount = 0;
		string userChoice;

		while (true) {
			printClientMenu();
			getline(cin, userChoice);

			if (userChoice == "1") {
				system("cls");
				cout << "\n======== My Account Info ========\n\n";
				client->displayClientInfo();
				cout << endl;
				system("pause");
				return true;
			}
			else if (userChoice == "2") {
				updatePassword(client);
				return true;
			}
			else if (userChoice == "3") {
				cout << "\nDeposit money - will be added later\n";
				system("pause");
				return true;
			}
			else if (userChoice == "4") {
				cout << "\nWithdraw money - will be added later\n";
				system("pause");
				return true;
			}
			else if (userChoice == "5") {
				cout << "\nTransfer money - will be added later\n";
				system("pause");
				return true;
			}
			else if (userChoice == "6") {
				system("cls");
				cout << "\n======== My Money ========\n\n";
				cout << "Egyptian pounds: " << client->getBalance() << " EGP\n";
				if (client->hasUSDAccount()) {
					cout << "US dollars: " << client->getUSDBalance() << " USD\n";
				}
				else {
					cout << "US dollars account: I don't have one\n";
				}
				cout << endl;
				system("pause");
				return true;
			}
			else if (userChoice == "7") {
				cout << "\nTransaction history - will be added later\n";
				system("pause");
				return true;
			}
			else if (userChoice == "0") {
				return false;
			}
			else {
				showError("That's not a valid choice!\n");
				tryCount++;
				if (maxTry(tryCount)) 
					return false;
			}
		}
	}

};
