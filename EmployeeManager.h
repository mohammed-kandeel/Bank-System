#pragma once
#include"FileManager.h"

class EmployeeManager{
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
		else return false;
	}
	static bool maxTry(int count) {
		if (count == 3) {
			showError("Too many invalid attempts. Returning to main menu...\n");
			return true;
		}
		else return false;
	}
	static void showClientScreen(string header, Client* client) {
		system("cls");
		cout << header << "--------  Client Info  --------\n";
		client->displayClientInfo();
		cout << "-------------------------------\n";
	}
	template<class T>
	static bool tryParseNumber(string& string, T& num) {
		try { 
			num = stod(string);
			return true;
		}
		catch (invalid_argument&) { return false; }
		catch (out_of_range&) { return false; }
	}

	
	static bool askForUSD() {
		string temp;
		cout << "Would you like to add a USD account for the client? (y/n): ";
		getline(cin, temp);
		return (!(temp.empty()) && (tolower(temp[0]) == 'y'));
	}
	static double getBalance(string line, string accountType) {
		double balance;
		int count = 0;

		string temp;
		do {
			if (maxTry(count)) return -1.0;
			system("cls");
			cout << line << endl;

			cout << endl << accountType << " Account:\n";
			cout << "   ->Enter the client's balance (or press '0' to cancel): ";
			getline(cin, temp);

			if (accountType == "EGP" && cancelOperation(temp)) return -1.0;
			else if (accountType == "USD" && temp == "0") {
				cout << "Continue without creating a USD account.\n";
				this_thread::sleep_for(chrono::seconds(3));
				return -1.0;
			}

			if (!tryParseNumber(temp, balance)) {
				showError("Invalid input. Please enter a valid number.\n");
				count++;
				continue;
			}
			if (!Validation::is_min_balance(balance)) {
				count++;
				showError("Invalid balance, The minimum is 1500. Try Again.\n");
			}
			else
				return balance;
		} while (true);
	}
	static Client* getClient(Employee* employee, string line) {
		int id, count = 0;
		Client* client;
		string temp;

		do {
			system("cls");
			cout << line;
			if (maxTry(count)) return nullptr;
			
			cout << "Enter client ID (or press '0' to cancel): ";
			getline(cin, temp);

			if (cancelOperation(temp)) return nullptr;
			if (!tryParseNumber(temp, id)) {
				showError("Invalid input. Please enter a valid number.\n");
				count++;
				continue;
			}
			client = employee->searchClient(id);
			if (client == nullptr) {
				showError("No client found with this ID. Try Again.\n");
				count++;
			}
			else return client;
		} while (true);
	}

public:
	static string getName(string line, string person) {
		string name;
		int count = 0;
		do {
			system("cls");
			cout << line << endl;

			cout << "\nEnter the "<< person <<"'s name (or press '0' to cancel): ";
			getline(cin, name);

			if (cancelOperation(name)) return "";

			if (!(Validation::is_valid_name(name))) {
				count++;
				if (maxTry(count)) return "";
				showError("Invalid name, try Again.\n");
			}
			else return name;
		} while (true);
	}
	static string getPassword(string line) {
		string password;
		int count = 0;
		do {
			system("cls");
			cout << line << endl;

			cout << "\nSet a password for the client (or press '0' to cancel): ";
			getline(cin, password);

			if (cancelOperation(password)) return "";

			if (!Validation::is_valid_password(password)) {
				count++;
				if (maxTry(count)) return "";
				showError("Invalid password, Try Again.\n");
			}
			else return password;
		} while (true);
	}


	static void printEmployeeMenu() {
		system("cls");
		cout << "=====   Employee Menu   =====\n\n";
		cout << "1. Add New Client\n";
		cout << "2. Issuing New Card for Client\n";
		cout << "3. Open USD Account for Client\n";
		cout << "4. Search for Client\n";
		cout << "5. List All Clients\n";
		cout << "6. Edit Client Information\n";
		cout << "7. Display My Information\n";
		cout << "8. Update My Password\n";
		cout << "0. Return to Login Menu\n";
		cout << "\nEnter your choice (0-8): ";
	}
	static void newClient(Employee* employee) {
		int id, count = 0;
		string name, password, line, temp;
		bool hasUSD = false;
		double EGPbalance, USDbalance = 0;

		 line = "\n========  New Client  ========\n\n";

		id = 1 + FilesHelper::getLastId("LastClientId.txt");
		line += "ID: " + to_string(id);

		//get name
		name = EmployeeManager::getName(line, "client");
		if (name == "") return;
		line += "\nName: " + name;

		//get password
		password = EmployeeManager::getPassword(line);
		if (password == "") return;
		line += "\nPassword: " + password;

		//get EGP balance
		EGPbalance = EmployeeManager::getBalance(line, "EGP");
		if (EGPbalance == -1.0)
			return;
		line += "\nEgyptian account:\n   ->EGP Balance = " + to_string(EGPbalance) + " EGP\n";

		//get USD balance
		system("cls");
		cout << line << endl;
		hasUSD = EmployeeManager::askForUSD();
		if (hasUSD) {
			USDbalance = EmployeeManager::getBalance(line, "USD");
			if (USDbalance == -1.0)
				hasUSD = false;
			else
				line += "Dollar account:\n   ->USD Balance: " + to_string(USDbalance) + " USD\n";
		}
		system("cls");
		cout << line << endl;
		Client* client = new Client(id, name, password, EGPbalance, hasUSD, USDbalance);
		employee->addClient(client);
		FilesHelper::saveLastId("LastClientId.txt", id);
	}
	static void newCard(Employee* employee) {
		double creditLimit = 0;
		int count = 0;
		Client* client;
		string temp, line, card;
		CardType cardType;
		AccountType accountType;
		
		line = "\n======== Issue New Card ========\n\n";
		client = EmployeeManager::getClient(employee, line);
		if (client == nullptr) return;

		//Select Card Type
		do {
			showClientScreen(line, client);
			cout << "\n-----  Select Card Type  ------\n";
			cout << "1. Debit Card\n";
			cout << "2. Credit Card\n";
			cout << "0. Return to Main Menu\n";
			cout << "\nEnter your choice (0-2): ";
			getline(cin, temp);

			if (cancelOperation(temp))
				return;
			if (temp == "1") {
				cardType = CardType::Debit;
				card = "Debit Card";
				break;
			}
			else if (temp == "2") {
				cardType = CardType::Credit;
				card = "Credit Card";
				break;
			}
			else {
				count++;
				if (maxTry(count)) return;
				showError("Invalid choice, Try Again.\n");
			}
		} while (true);

		//Get Credit Limit
		if (cardType == CardType::Credit) {
			count = 0;
			do {
				showClientScreen(line, client);
				cout << "\nSelect Card -> " << card << endl;
				cout << "\n-----  Get Credit Limit  ------\n";
				cout << "Enter Credit Limit: ";
				getline(cin, temp);

				if (!tryParseNumber(temp, creditLimit)) {
					showError("Invalid input. Please enter a valid number.\n");
					count++;
					continue;
				}
				if (creditLimit <= 0) {
					count++;
					showError("Credit limit must be positive.\n");
					continue;
				}
				if (maxTry(count)) return;
				if (creditLimit > 0) {
					card += "\nCredit Limit: " + to_string(creditLimit) + "\n";
					break;
				}
			} while (true);
		}

		//Select Account Type
		count = 0;
		do {
			showClientScreen(line, client);
			cout << "\nSelect Card -> " << card << endl;

			cout << "\n----  Select Account Type  ----\n";
			cout << "1. EGP account\n";
			cout << "2. USD account\n";
			cout << "0. Return to Main Menu\n";
			cout << "\nEnter your choice (0-2): ";
			getline(cin, temp);

			if (cancelOperation(temp)) return;
			if (temp == "1") {
				accountType = AccountType::EGP;
				break;
			}
			else if (temp == "2") {
				accountType = AccountType::USD;
				break;
			}
			else {
				count++;
				if (maxTry(count)) return;
				showError("Invalid choice, Try Again.\n");
			}
		} while (true);

		if (accountType == AccountType::USD && !client->hasUSDAccount()) {
			showError("Client doesn't have a USD account.\nReturning to main menu...\n");
			return;
		}
		if (cardType==CardType::Debit && client->hasDebitCard(accountType)) {
			showError("\n" + client->accountTypeToString(accountType) + " account already has a " + (cardType == CardType::Debit ? "debit" : "credit") + " card.\nReturning to main menu...\n");
			return;
		}
		else if(cardType==CardType::Credit && client->hasCreditCard(accountType)) {
			showError("\n" + client->accountTypeToString(accountType) + " account already has a " + (cardType == CardType::Debit ? "debit" : "credit") + " card.\nReturning to Main menu...\n");
			return;
		}
		else {
			int lastCardId = FilesHelper::getLastId("LastCardId.txt") + 1;
			if (cardType == CardType::Debit)
				employee->addDebitCard(client, accountType, lastCardId, "1-2030");
			if(cardType==CardType::Credit)
				employee->addCreditCard(client, accountType, lastCardId, "1-2030", creditLimit);
			FilesHelper::saveCardId(*client);
			cout << "\nCard issued successfully!\n";
			this_thread::sleep_for(chrono::seconds(3));
		}
	}
	static void openUSDAccount(Employee* employee) {
		string line;
		double USDbalance;

		system("cls");
		line = "\n========  Open USD Account  ========\n\n";
		Client* client = getClient(employee, line);
		if (client == nullptr)
			return;

		if (client->hasUSDAccount()) {
			showError("The client already has a USD account.\nReturning to main menu...\n");
			return;
		}
		int count = 0;
		string temp;
		do {
			if (maxTry(count)) return;

			showClientScreen(line, client);
			cout << endl << "USD Account:\n";
			cout << "   ->Enter the client's balance (or press '0' to cancel): ";
			getline(cin, temp);

			if (temp == "0") {
				cout << "Continue without creating a USD account.\n";
				this_thread::sleep_for(chrono::seconds(3));
				return;
			}
			if (!tryParseNumber(temp, USDbalance)) {
				showError("\nInvalid input. Please enter a valid number.\n");
				count++;
				continue;
			}
			if (!Validation::is_min_balance(USDbalance)) {
				count++;
				showError("\nInvalid balance, The minimum is 1500. Try Again.\n");
			}
			else {
				employee->addUSDAccount(client, USDbalance);
				cout << "\nUSD account opened successfully!\n";
				system("pause");
				return;
			}
				
		} while (true);
	}
	static void searchForClient(Employee* employee) {
		string line = "\n========  Search For Client  ========\n\n";
		Client* client = getClient(employee, line);
		if (client == nullptr) return;
		system("cls");
		line += "Client found\n";
		showClientScreen(line, client);
		system("pause");
	}
	static void listAllClients(Employee* employee) {
		system("cls");
		cout << "\n========  List All Clients  ========\n\n";
		cout << "Do you want to display the transaction history along with the client's information? (y/n): ";
		char chois;
		cin >> chois;
		cin.ignore();
		system("cls");
		if (tolower(chois) == 'y'){
			employee->listClientWithTransactions();
			system("pause");
		}
		else{
			employee->listClient();
			system("pause");
		}

	}
	static void editClientInfo(Employee* employee) {
		int count;
		string line, temp;

		system("cls");
		line = "\n========  Edit Client Info  ========\n\n";
		Client* client = getClient(employee, line);
		if (client == nullptr)
			return;

		count = 0;
		do {
			showClientScreen(line, client);

			cout << "\n-----  Edit Menu  ------\n";
			cout << "1. Edit Name\n";
			cout << "2. Edit Password\n";
			cout << "3. Edit Balance\n";
			cout << "0. Return to Main Menu\n";
			cout << "\nEnter your choice (0-3): ";
			getline(cin, temp);

			if (cancelOperation(temp)) return;
			if (temp != "1" && temp != "2" && temp != "3") {
				count++;
				if (maxTry(count)) return;
				showError("\nInvalid choice, Try Again.\n");
			}
			else break;
		} while (true);

		//name
		if (temp == "1") {
			string name;
			count = 0;
			do {
				showClientScreen(line, client);
				cout << "\nEnter new client's name (or press '0' to cancel): ";
				getline(cin, name);

				if (cancelOperation(name)) return;

				if (!(Validation::is_valid_name(name))) {
					count++;
					if (maxTry(count)) return;
					showError("\nInvalid choice, Try Again.\n");
				}
				else {
					employee->editClient(client->getID(), name, "-1", -1, AccountType::EGP);  // '-1' not editing
					showClientScreen(line, client);
					cout << "\nName updated successfully!\n";
					system("pause");
					return;
				}
			} while (true);
		}
		//Password
		else if (temp == "2") {
		
			string password;
			count = 0;
			do {
				showClientScreen(line, client);
				cout << "\nSet a new password for the client (or press '0' to cancel): ";
				getline(cin, password);

				if (cancelOperation(password)) return;

				if (!Validation::is_valid_password(password)) {
					count++;
					if (maxTry(count)) return;
					showError("\nInvalid choice, Try Again.\n");
				}
				else {
					employee->editClient(client->getID(), "-1", password, -1, AccountType::EGP);  // '-1' not editing
					showClientScreen(line, client);
					cout << "\nPassword updated successfully!\n";
					system("pause");
					return;
				}
			} while (true);
		}
		//Balance
		else if (temp == "3") {
			
			//Select Account Type
			AccountType accountType;
			count = 0;
			do {
				showClientScreen(line, client);
				cout << "----  Select Account Type  ----\n";
				cout << "1. EGP account\n";
				cout << "2. USD account\n";
				cout << "0. Return to Main Menu\n";
				cout << "\nEnter your choice (0-2): ";
				getline(cin, temp);

				if (cancelOperation(temp))
					return;

				if (temp == "1") {
					accountType = AccountType::EGP;
					break;
				}
				else if (temp == "2") {
					accountType = AccountType::USD;
					break;
				}
				else {
					count++;
					if (maxTry(count)) return;
					showError("\nInvalid choice, Try Again.\n");
				}
			} while (true);

			double balance;
			count = 0;
			do {
				if (maxTry(count)) return;

				showClientScreen(line, client);
				cout << endl << ((accountType == AccountType::EGP) ? "EGP" : "USD") << " Account:\n";
				cout << "   ->Enter new client's balance (or press '0' to cancel): ";
				getline(cin, temp);

				if (cancelOperation(temp)) return;
				if (!tryParseNumber(temp, balance)) {
					showError("\nInvalid input. Please enter a valid number.\n");
					count++;
					continue;
				}
				if (!Validation::is_min_balance(balance)) {
					count++;
					showError("\nInvalid balance, The minimum is 1500. Try Again.\n");
				}
				else {
					employee->editClient(client->getID(), "-1", "-1", balance, accountType);  // '-1' not editing
					showClientScreen(line, client);
					cout << "\nBalance updated successfully!\n";
					system("pause");
					return;
				}
			} while (true);
		}
	}
	static void displayMyInformation(Employee* employee) {
		system("cls");
		cout << "\n======== Display My Info ========\n\n";
		employee->displayEmployeeInfo();
		cout << endl;
		system("pause");
	}
	static void updateMyPassword(Employee* employee) {
		string newPassword, oldPassword;
		system("cls");
		cout << "\n======== Update My Password ========\n\n";

		cout << "Enter your current password (or 0 to cancel): ";
		getline(cin, oldPassword);
		if (cancelOperation(oldPassword))
			return;
		if ((employee->getPassword() != oldPassword)) {
			showError("\nInvalid password!\nReturning to main menu...\n");
			return;
		}

		system("cls");
		cout << "\n======== Update My Password ========\n\n";
		cout << "Enter The New Password: ";
		getline(cin, newPassword);
		if (!Validation::is_valid_password(newPassword)) {
			showError("Invalid password format!\nReturning to main menu...\n");
			return;
		}

		employee->setPassword(newPassword);
		cout << "\nPassword updated successfully!\n";
		this_thread::sleep_for(chrono::seconds(3));
	}
	static Employee* login(int id, string password) {
		auto i = Employee::employees.find(id);
		if (i == Employee::employees.end() || i->second->getPassword() != password) {
			showError("Wrong ID or password.\nReturning to main menu...\n");
			return nullptr;
		}
		return i->second;
	}
	static bool employeeOptions(Employee* employee) {
		int count = 0;
		string choice;

		while (true) {
			printEmployeeMenu();
			getline(cin, choice);

			switch (choice[0]) {
				case '1': { newClient(employee); return true; } break;
				case '2': { newCard(employee); return true; } break;
				case '3': { openUSDAccount(employee); return true; } break;
				case '4': { searchForClient(employee); return true; } break;
				case '5': { listAllClients(employee); return true; } break;
				case '6': { editClientInfo(employee); return true; } break;
				case '7': { displayMyInformation(employee); return true; } break;
				case '8': { updateMyPassword(employee); return true; } break;
				case '0': { return false; } break;
				default: { showError("Wrong input\n"); count++; if (maxTry(count)) return false; } break;
			}
		}
	}
};