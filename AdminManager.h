#pragma once
#include"EmployeeManager.h"

class AdminManager{

	static void printAdminMenu() {
		system("cls");
		cout << "=====   Admin Menu   =====\n\n";
		cout << " 1. Add New Client\n";
		cout << " 2. Issuing New Card for Client\n";
		cout << " 3. Open USD Account for Client\n";
		cout << " 4. Search for Client\n";
		cout << " 5. List All Clients\n";
		cout << " 6. Edit Client Information\n";

		cout << " 7. Add New Employee\n";
		cout << " 8. Search for Employee\n";
		cout << " 9. Edit Employee Information\n";
		cout << "10. List All Employees\n";

		cout << "11. Display My Information\n";
		cout << "12. Update My Password\n";
		cout << " 0. Return to Login Menu\n";
		cout << "\nEnter your choice (0-12): ";
	}
	//static void addNewEmployee(Admin* admin) {

	//	int id, count = 0;
	//	string name, password, line, temp;
	//	double salary;

	//	line = "\n========  New Employee  ========\n\n";

	//	id = 1 + FilesHelper::getLastId("LastEmployeeId.txt");
	//	line += "ID: " + to_string(id);

	//	//get name
	//	name = EmployeeManager::getName(line, "Employee");
	//	if (name == "") return;
	//	line += "\nName: " + name;

	//	//get password
	//	password = EmployeeManager::getPassword(line,"Employee");
	//	if (password == "") return;
	//	line += "\nPassword: " + password;

	//	//get EGP balance
	//	EGPbalance = EmployeeManager::getBalance(line, "EGP");
	//	if (EGPbalance == -1.0)
	//		return;
	//	line += "\nEgyptian account:\n   ->EGP Balance = " + to_string(EGPbalance) + " EGP\n";

	//	//get USD balance
	//	system("cls");
	//	cout << line << endl;
	//	hasUSD = EmployeeManager::askForUSD();
	//	if (hasUSD) {
	//		USDbalance = EmployeeManager::getBalance(line, "USD");
	//		if (USDbalance == -1.0)
	//			hasUSD = false;
	//		else
	//			line += "Dollar account:\n   ->USD Balance: " + to_string(USDbalance) + " USD\n";
	//	}
	//}







};

