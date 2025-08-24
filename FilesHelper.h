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

	//save one person to file
	static void saveClient(Client& c) {
		int id = getLastId("LastClientId.txt") + 1;
		// (id, name, password, balance ,currency)
		string line = to_string(id) + "&" + c.getName() + "&" + c.getPassword() + "&" + to_string(c.getBalance("EGP"))
			+ "&" + to_string(c.hasUSDAccount()) + "&" + to_string(c.getBalance("USD"))

			//	( hasDebitCard, cardId, expiryDat)
			+ "&" + to_string(c.hasDebitCard("EGP")) + "&" + to_string(c.getIdCard("EGP", "debit")) + "&" + c.getExpiryDateCard("EGP", "debit")
			+ "&" + to_string(c.hasDebitCard("USD")) + "&" + to_string(c.getIdCard("USD", "debit")) + "&" + c.getExpiryDateCard("USD", "debit")

			//	(hasCreditCard, cardId, expiryDate, creditLimit, amountUse)
			+ "&" + to_string(c.hasCreditCard("EGP")) + "&" + to_string(c.getIdCard("EGP", "credit")) + "&" + c.getExpiryDateCard("EGP", "credit") + "&" + to_string(c.getCreditLimit("EGP")) + "&" + to_string(c.getCreditUsed("EGP"))
			+ "&" + to_string(c.hasCreditCard("USD")) + "&" + to_string(c.getIdCard("USD", "credit")) + "&" + c.getExpiryDateCard("USD", "credit") + "&" + to_string(c.getCreditLimit("USD")) + "&" + to_string(c.getCreditUsed("USD"));

		ofstream setClient("Client.txt", ios::app);
		setClient << line << endl;
		setClient.close();
		saveLastId("LastClientId.txt", id);
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
		ifstream file("Client.txt", ios::in);
		string line;

		while (getline(file, line)) {  //Continue reading until reaching the end of the file (EOF), at which point it returns false.
			Client c = Parser::parseToClient(line);
			Client::clients.insert({ c.getID(), c });
		}
		file.close();
	}
	static void getEmployees() {
		ifstream file("Employee.txt", ios::in);
		string line;

		while (getline(file, line)) {  //Continue reading until reaching the end of the file (EOF), at which point it returns false.
			Employee e = Parser::parseToEmployee(line);
			Employee::employees.insert({ e.getID(),e });
		}
		file.close();
	}
	static void getAdmins() {
		ifstream file("Admin.txt", ios::in);
		string line;

		while (getline(file, line)) {  //Continue reading until reaching the end of the file (EOF), at which point it returns false.
			Admin a = Parser::parseToAdmin(line);
			Admin::admins.insert({ a.getID(),a });
		}
		file.close();
	}

	//clear File Data
	static void clearFile(string fileName, string lastIdFile) {
		ofstream removeData(fileName, ios::trunc);
		removeData.close();
		FilesHelper::saveLastId(lastIdFile, 0);
	}
};