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
	static bool tryParseNumber(string& input, double& num) {
		try {
			size_t idx;
			num = stod(input, &idx);  // idx = آخر موضع حوِّلته stod
			// لو في أي حاجة زيادة بعد الرقم، اعتبره خطأ
			return idx == input.length();
		}
		catch (invalid_argument&) { return false; }
		catch (out_of_range&) { return false; }
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
	static void printCardOprations() {
		system("cls");
		cout << "========  Card Menu (Client)  ========\n\n";
		cout << "1. Deposit\n";
		cout << "2. Withdraw\n";
		cout << "3. View Balance\n";
		cout << "0. Return to Client Menu\n";
		cout << "\nEnter your choice (0-3): ";
	}
	static void printCardType() {
		system("cls");
		cout << "========  Card Menu (Client)  ========\n\n";
		cout << "1. Debit Card\n";
		cout << "2. Credit Card\n";
		cout << "0. Return to Client Menu\n";
		cout << "\nEnter your choice (0-2): ";
	}
	static void printWhichAccountType() {
		cout << "----  Select Account Type  -----\n";
		cout << "1. Use EGP Account \n";
		cout << "2. Use USD Account \n";
		cout << "0. Return to Menu\n";
		cout << "\nEnter your choice (0-2): ";
	}
	static void printClientMenu() {
		system("cls");
		cout << "========  Client Menu  ========\n\n";
		cout << "1. Use Account\n";
		cout << "2. Use Card\n";
		cout << "0. Return to Login Menu\n";
		cout << "\nEnter your choice (0-2): ";
	}

	static CardType getCardType(string line) {
		int count = 0;
		string temp;
		do {
			system("cls");
			cout << line;
			printCardType();
			getline(cin, temp);

			if (cancelOperation(temp))
				return CardType::Non;

			if (temp == "1")
				return CardType::Debit;
			else if (temp == "2") 
				return CardType::Credit;
			else {
				count++;
				if (maxTry(count)) return CardType::Non;
				showError("Invalid input. Please enter a valid number.\n");
				continue;
			}
		} while (true);
	}
	static AccountType getAccountType(string line, Client* client) {
		int count = 0;
		string temp;
		do {
			system("cls");
			cout << line << endl;
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
	static double amountCard(string line, AccountType accountType) {
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
				return-1;
			if (!tryParseNumber(temp, amount)) {
				count++;
				if (maxTry(count)) return -1;
				showError("Invalid input. Please enter a valid number.\n");
				continue;
			}
			else
				return amount;
		} while (true);
	}

	static void cardDeposit(Client* client) {
		string line;
		CardType cardType;
		AccountType accountType;
		double amount;
		line = "========  Card Menu (Client)  ========\n\n-----------  Deposit  ----------\n\n";

		cardType = getCardType(line);
		if (cardType == CardType::Non) return;

		line += "->Use " + (client->cardTypeToString(cardType)) + " Card\n";
		accountType = getAccountType(line, client);
		if (accountType == AccountType::Non) return;

		if (cardType == CardType::Debit && !client->hasDebitCard(accountType)) {
			showError("You don't have a card linked to this account.\nReturning to main menu...\n");
			return;
		}
		if (cardType == CardType::Credit && !client->hasCreditCard(accountType)) {
			showError("You don't have a card linked to this account.\nReturning to main menu...\n");
			return;
		}
		line += "->With " + (client->accountTypeToString(accountType)) + " Account\n";

		amount = amountCard(line, accountType);
		if (amount == -1) return;

		if (cardType == CardType::Debit)
			client->useDebitCard(accountType, amount, Operation::Deposit);
		else if (cardType == CardType::Credit)
			client->useCreditCard(accountType, amount, Operation::Deposit);

		cout << "\nDeposit completed successfully!\nReturning to main menu...\n";
		this_thread::sleep_for(chrono::seconds(3));
	}
	static void cardWithdraw(Client* client) {
		string line;
		CardType cardType;
		AccountType accountType;
		double amount;
		line = "========  Card Menu (Client)  ========\n\n----------   Withdraw  ---------\n\n";
		cardType = getCardType(line);
		if (cardType == CardType::Non) return;

		line += "->Use " + (client->cardTypeToString(cardType)) + " Card\n";
		accountType = getAccountType(line, client);
		if (accountType == AccountType::Non) return;

		if (cardType == CardType::Debit && !client->hasDebitCard(accountType)) {
			showError("You don't have a card linked to this account.\nReturning to main menu...\n");
			return;
		}
		if (cardType == CardType::Credit && !client->hasCreditCard(accountType)) {
			showError("You don't have a card linked to this account.\nReturning to main menu...\n");
			return;
		}
		line += "->With " + (client->accountTypeToString(accountType)) + " Account\n";

		amount = amountCard(line, accountType);
		if (amount == -1) return;

		if (cardType == CardType::Debit) {
			if (amount <= client->getBalance(accountType)) {
				client->useDebitCard(accountType, amount, Operation::Withdraw);
				cout << "\nWithdraw completed successfully!\nReturning to main menu...\n";
				this_thread::sleep_for(chrono::seconds(3));
			}
			else
				showError("You don't have enough balance in your account.\nReturning to main menu...\n");
		}
		else if (cardType == CardType::Credit) {
			if ((client->getCreditUsed(accountType) + amount) <= client->getCreditLimit(accountType)) {
				client->useCreditCard(accountType, amount, Operation::Withdraw);
				cout << "\nWithdraw completed successfully!\nReturning to main menu...\n	";
				this_thread::sleep_for(chrono::seconds(3));
			}
			else
				showError("Your available credit is insufficient.\nReturning to main menu...\n");
		}
	}
	static void viewBalance(Client* client) {
		string line;
		CardType cardType;
		AccountType accountType;
		line = "========  Card Menu (Client)  ========\n\n--------   View Balance  -------\n\n";
		cardType = getCardType(line);
		if (cardType == CardType::Non) return;

		line += "->Use " + (client->cardTypeToString(cardType)) + " Card\n";
		accountType = getAccountType(line, client);
		if (accountType == AccountType::Non) return;

		if (cardType == CardType::Debit && !client->hasDebitCard(accountType)) {
			showError("You don't have a card linked to this account.\nReturning to main menu...\n");
			return;
		}
		if (cardType == CardType::Credit && !client->hasCreditCard(accountType)) {
			showError("You don't have a card linked to this account.\nReturning to main menu...\n");
			return;
		}
		line += "->With " + (client->accountTypeToString(accountType)) + " Account\n";

		if (cardType == CardType::Debit) {
			system("cls");
			cout << "========  Card Menu (Client)  ========\n\n--------   View Balance  -------\n\n";
			cout << "->Balance: " << client->getBalance(accountType) << " " << client->getCurrency(accountType) << endl << endl;
			system("pause");
		}
		else if (cardType == CardType::Credit) {
			system("cls");
			cout << "========  Card Menu (Client)  ========\n\n--------   View Balance  -------\n\n";
			cout << "->Balance: " << client->getBalance(accountType) << " " << client->getCurrency(accountType) << endl;
			cout << "->Credit Limit: " << client->getCreditLimit(accountType) << " " << client->getCurrency(accountType) << endl;
			cout << "->Credit Used: " << client->getCreditUsed(accountType) << " " << client->getCurrency(accountType) << endl << endl;
			system("pause");
		}
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
				count++;
				if (maxTry(count)) return;
				showError("Invalid input. Please enter a valid number.\n");
				continue;
			}
			if (amount <= 0) {
				count++;
				if (maxTry(count)) return;
				showError("Amount must be greater than zero.\n");
				continue;
			}
			else {
				client->deposit(amount, accountType);
				cout << "\nDeposit completed successfully!\nReturning to main menu...\n";
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
				count++;
				if (maxTry(count)) return;
				showError("Invalid input. Please enter a valid number.\n");
				continue;
			}

			if (amount <= 0) {
				count++;
				if (maxTry(count)) return;
				showError("Amount must be greater than zero.\n");
				continue;
			}
			if (client->getBalance(accountType) < amount) {
				showError("Insufficient balance.\nReturning to main menu...\n");
				return;
			}
			else {
				client->withdraw(amount, accountType);
				cout << "\nWithdraw completed successfully!\nReturning to main menu...\n";
				this_thread::sleep_for(chrono::seconds(3));
				return;
			}
		} while (true);
	}

	static bool accountMenu(Client* client) {
		int count = 0;
		string choice;

		while (true) {
			printAccountMenu();
			getline(cin, choice);
			if (choice.empty()) { showError("No input\n"); count++; continue; }

			switch (choice[0]) {
			case '1': { Deposit(client); return true; } break;
				//case '2': { withdraw(client); return true; } break;
				//case '3': { transferTo(client); return true; } break;
				//case '4': { viewBalance(client); return true; } break;
				//case '5': { viewTransactionHistory(client); return true; } break;
				case '6': { updatePassword(client); return true; } break;
				case '0': { return false; } break;
			default: { showError("Wrong input\n"); count++; if (maxTry(count)) return false; } break;
			}
		}
	}
	static bool cardOperations(Client* client) {
		int count = 0;
		string choice;

		while (true) {
			printCardOprations();
			getline(cin, choice);
			if (choice.empty()) { showError("No input\n"); count++; continue; }

			switch (choice[0]) {
			case '1': { cardDeposit(client); return true; } break;
			case '2': { cardWithdraw(client); return true; } break;
			case '3': { viewBalance(client); return true; } break;
			case '0': { return false; } break;
			default: { showError("Wrong input\n"); count++; if (maxTry(count)) return false; } break;
			}
		}
	}

public:
	
	static void Deposit(Client* client) {
		string line;
		AccountType accountType;

		line = "\n========  Deposit  ========\n\n";
		accountType = getAccountType(line, client);
		line += "->Use " + (client->accountTypeToString(accountType)) + " Account\n";

		if (accountType == AccountType::Non) return;
		Deposit(line, client, accountType);
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
	static bool clientMenu(Client* client) {
		int count = 0;
		string choice;

		while (true) {
			printClientMenu();
			getline(cin, choice);
			if (choice.empty()) { showError("No input\n"); count++; continue; }

			switch (choice[0]) {
				case '1': { while (accountMenu(client)); return true; } break;
				case '2': { while (cardOperations(client)); return true; } break;
				case '0': { return false; } break;
				default: { showError("Wrong input\n"); count++; if (maxTry(count)) return false; } break;
			}
		}
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
