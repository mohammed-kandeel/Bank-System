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
        }

        else if (choice == "2") { 
            updatePassword(client);
        }

        else if (choice == "3") { 
            system("cls");
            double amount;
            int accChoice;
            cout << "\n======== Deposit ========\n\n";
            cout << "1. EGP Account\n";
            cout << "2. USD Account\n";
            cout << "Choose account type: ";
            cin >> accChoice; cin.ignore();

            cout << "Enter amount to deposit: ";
            cin >> amount; cin.ignore();

            if (accChoice == 1) client->deposit(amount, AccountType::EGP);
            else if (accChoice == 2) client->deposit(amount, AccountType::USD);
            else showError("Invalid account type!");

            system("pause");
        }

        else if (choice == "4") {
            system("cls");
            double amount;
            int accChoice;
            cout << "\n======== Withdraw ========\n\n";
            cout << "1. EGP Account\n";
            cout << "2. USD Account\n";
            cout << "Choose account type: ";
            cin >> accChoice; cin.ignore();

            cout << "Enter amount to withdraw: ";
            cin >> amount; cin.ignore();

            if (accChoice == 1) {
                if (client->checkAvailableBalance(amount, AccountType::EGP))
                    client->withdraw(amount, AccountType::EGP);
                else showError("Insufficient balance!");
            }
            else if (accChoice == 2) {
                if (client->checkAvailableBalance(amount, AccountType::USD))
                    client->withdraw(amount, AccountType::USD);
                else showError("Insufficient balance!");
            }
            else showError("Invalid account type!");

            system("pause");
        }

        else if (choice == "5") { 
            system("cls");
            double amount;
            int accChoice, recipientId;
            cout << "\n======== Transfer ========\n\n";
            cout << "1. EGP Account\n";
            cout << "2. USD Account\n";
            cout << "Choose account type: ";
            cin >> accChoice; cin.ignore();

            cout << "Enter recipient ID: ";
            cin >> recipientId; cin.ignore();

            cout << "Enter amount to transfer: ";
            cin >> amount; cin.ignore();

            auto it = Client::clients.find(recipientId);
            if (it == Client::clients.end()) {
                showError("Recipient not found!");
            }
            else {
                if (accChoice == 1) client->transFerTo(amount, it->second, AccountType::EGP);
                else if (accChoice == 2) client->transFerTo(amount, it->second, AccountType::USD);
                else showError("Invalid account type!");
            }

            system("pause");
        }

        else if (choice == "6") { 
            system("cls");
            cout << "\n======== Account Balance ========\n\n";
            cout << "EGP Balance: " << client->getBalance(AccountType::EGP) << " EGP\n";
            if (client->hasUSDAccount())
                cout << "USD Balance: " << client->getBalance(AccountType::USD) << " USD\n";
            else
                cout << "USD Account: Not Available\n";
            cout << endl;
            system("pause");
        }

        else if (choice == "7") { 
            system("cls");
            client->displayClientTransactionHistory();
            cout << endl;
            system("pause");
        }

        else if (choice == "0") { 
            return false;
        }

        else { 
            showError("Invalid choice! Please try again.\n");
            count++;
            if (maxTry(count)) return false;
        }
    }
}
