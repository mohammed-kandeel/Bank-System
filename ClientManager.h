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
	static bool tryParseNumber(string& string, double& num) {
		try {
			num = stod(string);
			return true;
		}
		catch (invalid_argument&) { return false; }
		catch (out_of_range&) { return false; }
	}
	static void printWhichAccountType() {
		cout << "1. Use EGP Account \n";
		cout << "2. Use USD Account \n";
		cout << "0. Return to Menu\n";
		cout << "\nEnter your choice (0-2): ";
	}
	static AccountType getAccountType(string line, Client* client) {
		int count = 0;
		string temp;
		do {
			system("cls");
			cout << line;
			printWhichAccountType();
			getline(cin, temp);

			if (cancelOperation(temp))
				return AccountType::Non;

			if (temp == "1") 
				return AccountType::EGP;

			else if (temp == "2") {
				if (!client->hasUSDAccount()) {
					showError("You don't have a USD account.\n");
					return AccountType::Non;
				}
				return AccountType::USD;
			}
			else {
				count++;
				if (maxTry(count)) return AccountType::Non;
				showError("Invalid input. Please enter a valid number.\n");
				continue;
			}
		} while (true);
	}

	static void Deposit(string line, Client* client, AccountType accountType) {
		int count;
		string temp;
		double amount;

		count = 0;
		do {
			system("cls");
			cout << line << endl;
			cout << "->Enter amount (or press '0' to return to main menu): ";
			getline(cin, temp);

			if (cancelOperation(temp))
				return;
			if (!tryParseNumber(temp, amount)) {
				showError("\nInvalid input. Please enter a valid number.\n");
				count++;
				continue;
			}
			else {
				client->deposit(amount, accountType);
				cout << "\nDeposit completed successfully!\nReturning to main menu...\n	";
				this_thread::sleep_for(chrono::seconds(3));
				return;
			}
		} while (true);
	}
	static void Withdraw(string line, Client* client, AccountType accountType) {
		int count;
		string temp;
		double amount;

		count = 0;
		do {
			system("cls");
			cout << line << endl;
			cout << "->Enter amount (or press '0' to return to main menu): ";
			getline(cin, temp);

			if (cancelOperation(temp))
				return;
			if (!tryParseNumber(temp, amount)) {
				showError("\nInvalid input. Please enter a valid number.\n");
				count++;
				continue;
			}
			if (client->getBalance(accountType) > amount || amount <= 0) {
				showError("\nInvalid input. Please enter a valid number.\n");
				count++;
				continue;
			}
			else {
				client->withdraw(amount, accountType);
				cout << "\nwithdraw completed successfully!\nReturning to main menu...\n	";
				this_thread::sleep_for(chrono::seconds(3));
				return;
			}
		} while (true);
	}


public:
	static void printClientMenu() {
		system("cls");
		cout << "========  Client Menu  ========\n\n";
		cout << "1. Use Account\n";
		cout << "2. Use Card\n";
		cout << "0. Return to Main Menu\n";
		cout << "\nEnter your choice (0-2): ";
	}
	static void printAccountMenu() {
		system("cls");
		cout << "========  Account Menu (Client)  ========\n\n";
		cout << "1. Deposit\n";
		cout << "2. Withdraw\n";
		cout << "3. Transfer To\n";
		cout << "4. View Balance\n";
		cout << "5. View Transaction History\n";
		cout << "6. Update Password\n";
		cout << "0. Return to Client Menu\n";
		cout << "\nEnter your choice (0-6): ";
	}
	static void printCardType() {
		system("cls");
		cout << "========  Card Menu (Client)  ========\n\n";
		cout << "1. Credit Card\n";
		cout << "2. Debit Card\n";
		cout << "0. Return to Client Menu\n";
		cout << "\nEnter your choice (0-2): ";
	}
	static void Deposit(Client* client) {
		string line;
		AccountType accountType;

		line = "\n========  Deposit  ========\n\n";
		accountType = getAccountType(line, client);
		line += "->Use " + (client->accountTypeToString(accountType)) + " Account\n";

		if (accountType == AccountType::Non) return;
		Deposit(line, client, accountType);
	}









	static void printClientMenu2() {
		system("cls");
		cout << "=====   Client Menu   =====\n\n";
		cout << "1. Account Information\n";
		cout << "2. Change Password\n";
		cout << "3. Deposit Funds\n";
		cout << "4. Withdraw Funds\n";
		cout << "5. Transfer Funds\n";
		cout << "6. Account Balance\n";
		cout << "7. view Transaction History\n";
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
};
