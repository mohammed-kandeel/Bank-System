#pragma once

#include<fstream>
#include"Parser.h"

class FilesHelper {
public:
	//save & get last id of new person
	static int getLastId(string fileName);  // .ccp
	static void saveLastId(string fileName, int id) {
		ofstream saveId(fileName, ios::trunc);
		saveId << id;
		saveId.close();
	}
	static void saveCardId(Client& c) {
		int bigID = 0;

		if (c.hasDebitCard(AccountType::EGP) && c.getIdCard(AccountType::EGP, CardType::Debit) > bigID)
			bigID = c.getIdCard(AccountType::EGP, CardType::Debit);
		
		if (c.hasUSDAccount() && c.hasDebitCard(AccountType::USD) && c.getIdCard(AccountType::USD, CardType::Debit) > bigID)
			bigID = c.getIdCard(AccountType::USD, CardType::Debit);
		
		if (c.hasCreditCard(AccountType::EGP) && c.getIdCard(AccountType::EGP, CardType::Credit)>bigID) 
			bigID = c.getIdCard(AccountType::EGP, CardType::Credit);
		
		if (c.hasCreditCard(AccountType::USD) && c.getIdCard(AccountType::USD, CardType::Credit) > bigID)
			bigID = c.getIdCard(AccountType::USD, CardType::Credit);

		if (bigID > getLastId("LastCardId.text")) {
			ofstream saveId("LastCardId.txt", ios::trunc);
			saveId << bigID;
			saveId.close();
		}
	}

	//save one person to file
	static void saveClient(Client& c) {
		//int id = getLastId("LastClientId.txt") + 1;
	
		string line = 
			// (id, name, password, EGP_balance)
			to_string(c.getID()) + "&" + c.getName() + "&" + c.getPassword() + "&" + to_string(c.getBalance(AccountType::EGP))

			//(bool, USD_balance)
			+ "&" + to_string(c.hasUSDAccount()) + "&" + to_string(c.getBalance(AccountType::USD))

			//	( hasDebitCard, cardId, expiryDat)
			+ "&" + to_string(c.hasDebitCard(AccountType::EGP)) + "&" + to_string(c.getIdCard(AccountType::EGP,CardType::Debit)) + "&" + c.getExpiryDateCard(AccountType::EGP, CardType::Debit)
			+ "&" + to_string(c.hasDebitCard(AccountType::USD)) + "&" + to_string(c.getIdCard(AccountType::USD, CardType::Debit)) + "&" + c.getExpiryDateCard(AccountType::USD, CardType::Debit)

			//	(hasCreditCard, cardId, expiryDate, creditLimit, amountUse)
			+ "&" + to_string(c.hasCreditCard(AccountType::EGP)) + "&" + to_string(c.getIdCard(AccountType::EGP, CardType::Credit)) + "&" + c.getExpiryDateCard(AccountType::EGP, CardType::Credit) + "&" + to_string(c.getCreditLimit(AccountType::EGP)) + "&" + to_string(c.getCreditUsed(AccountType::EGP))
			+ "&" + to_string(c.hasCreditCard(AccountType::USD)) + "&" + to_string(c.getIdCard(AccountType::USD, CardType::Credit)) + "&" + c.getExpiryDateCard(AccountType::USD, CardType::Credit) + "&" + to_string(c.getCreditLimit(AccountType::USD)) + "&" + to_string(c.getCreditUsed(AccountType::USD));
			
		vector<string>history = c.getTransactionHistory();
		while (!history.empty()) {
			line += "&" + history.back();//(history.end());
			history.pop_back();
		}

		ofstream setClient("Clients.txt", ios::app);
		setClient << line << endl;
		setClient.close();
		saveLastId("LastClientId.txt", c.getID());
		saveCardId(c);
	}
	static void saveEmployee(string fileName, string lastIdFile, Employee& e) {
		int id = getLastId(lastIdFile) + 1;
		// (id, name, password, salary ,currency)
		string line = to_string(id) + "&" + e.getName() + "&" + e.getPassword() + "&" + to_string(e.getSalary()) + "&" + e.getCurrency();

		ofstream setEmployee(fileName, ios::app);
		setEmployee << line << endl;
		setEmployee.close();
		saveLastId(lastIdFile, id);
	}

	// get all persons data from the files
	static void getClients() {
		ifstream file("Clients.txt", ios::in);
		string line;

		while (getline(file, line)) {  //Continue reading until reaching the end of the file (EOF), at which point it returns false.
			Client* c = new Client(Parser::parseToClient(line));
			Client::clients.insert({ c->getID(), c });
		}
		file.close();
	}
	static void getEmployees() {
		ifstream file("Employees.txt", ios::in);
		string line;

		while (getline(file, line)) {  //Continue reading until reaching the end of the file (EOF), at which point it returns false.
			Employee *e = new Employee(Parser::parseToEmployee(line));
			Employee::employees.insert({ e->getID(),e });
		}
		file.close();
	}
	static void getAdmins() {
		ifstream file("Admins.txt", ios::in);
		string line;

		while (getline(file, line)) {  //Continue reading until reaching the end of the file (EOF), at which point it returns false.
			Admin* a = new Admin(Parser::parseToAdmin(line));
			Admin::admins.insert({ a->getID(),a });
		}
		file.close();
	}

	//clear File Data
	static void clearFile(string fileName, string lastIdFile) {
		ofstream removeData(fileName, ios::trunc);
		removeData.close();
		FilesHelper::saveLastId(lastIdFile, 0);
		if (fileName == "Clients.txt")
			FilesHelper::saveLastId("LastCardId.txt", 0);
	}

	//update data (remove All data & save All data)
	static void updateClients() {
		FilesHelper::clearFile("Clients.txt", "LastClientId.txt");
		for (auto& i : Client::clients) {
			saveClient(*i.second);
		}
	}
	static void updateEmployees() {
		FilesHelper::clearFile("Employees.txt", "LastEmployeeId.txt");
		for (auto& i : Employee::employees) {
			saveEmployee("Employees.txt", "LastEmployeeId.txt",*i.second);
		}
	}
	static void updateAdmins() {
		FilesHelper::clearFile("Admins.txt", "LastAdminId.txt");
		for (auto& i : Admin::admins) {
			saveEmployee("Admins.txt", "LastAdminId.txt", *i.second);

		}
	}
};