#pragma once
#include <iostream>
#include <string>

#include<vector>

#include "Client.h"
#include "Employee.h"
#include "Admin.h"

#include <chrono>
#include <thread>

using namespace std;

class System{
private:

	static vector<Client>clients;
	static vector<Employee>employee;
	static vector<Admin>admin;

	static void delate() {
		Admin a(12345671, "aa", "12345678", 6000, "EG");
		admin.push_back(a);
		Admin a2(12345672, "ali ali", "12345678", 6500, "EG");
		admin.push_back(a2);
		Admin a3(12345673, "mahmoud", "12345678", 7000, "EG");
		admin.push_back(a3);
		Admin a4(12345674, "mohamed esam", "12345678", 7500, "EG");
		admin.push_back(a4);

		Employee e(12345671, "mohamed", "12345678", 6000, "EG");
		employee.push_back(e);
		Employee e2(12345672, "ali ali", "12345678", 6500, "EG");
		employee.push_back(e2);
		Employee e3(12345673, "mahmoud", "12345678", 7000, "EG");
		employee.push_back(e3);
		Employee e4(12345674, "mohamed esam", "12345678", 7500, "EG");
		employee.push_back(e4);


		Client c(12345671, "mohamed", "12345678", 6000, "EG");
		clients.push_back(c);
		Client c2(12345672, "ali ali", "12345678", 6500, "EG");
		clients.push_back(c2);
		Client c3(12345673, "mahmoud", "12345678", 7000, "EG");
		clients.push_back(c3);
		Client c4(12345674, "mohamed esam", "12345678", 7500, "EG");
		clients.push_back(c4);

	}

public:
	static  void run() {
		delate();
		int count{};
		char choice;

		do {
			//welcom_screan();
			//system("CLS");
			cout << "====    Main Menu   ====\n\n";
			cout << "1. login as Client\n";
			cout << "2. login as Employee\n";
			cout << "3. login as Admin\n";
			cout << "4. Exit\n";
			cout << "\nChoice (1-4): ";

			cin >> choice;
			switch (choice) {
				case '1':login_as_client(); break;
				case '2':login_as_employee(); break;
				case '3':login_as_admin(); break;
				case '4': { EX_screan(); return; } break;
				default: { cout << "Wrong input\n"; count++; } break;
			}
			if (count == 3) {
				EX_screan();
				return;
			}
		} while (true);
	}
	//keys
	/////////////////////////////////////
	static bool searchForIdClient(int id) {
		for (auto& c : clients) {
			if (c.getID() == id) {
				return true;
			}
		}
		return false;
	}
	static Client* find_client(int id) {
		for (auto& c : clients) {
			if (c.getID() == id)
				return &c;
		}
		return nullptr;
	}


	static bool searchForIdEmployee(int id) {
		for (auto& e : employee) {
			if (e.getID() == id) {
				return true;
			}
		}
		return false;
	}
	static Employee* find_employee(int id) {
		for (auto& e : employee) {
			if (e.getID() == id)
				return &e;
		}
		return nullptr;
	}

	static bool searchForIdAdmin(int id) {
		for (auto& a : admin) {
			if (a.getID() == id) {
				return true;
			}
		}
		return false;
	}
	static Admin* find_admin(int id) {
		for (auto& a : admin) {
			if (a.getID() == id)
				return &a;
		}
		return nullptr;
	}

	static bool is_valid_name(string name) {
		if (!(name.size() >= 5 && name.size() <= 20))
			return false;

		for (auto i : name) {
			if (!((i >= 'a' && i <= 'z') || (i >= 'A' && i <= 'Z') || (i == ' ')))
				return false;
		}
		return true;
	}
	static bool is_valid_password(string password) {
		return(password.size() >= 8 && password.size() <= 20);
	}
	static bool is_min_balance(double amount) {
		return (amount >= 1500);
	}
	static bool is_min_salary(double amount) {
		return (amount >= 5000);
	}
	/////////////////////////////////////

	//Employee
	/////////////////////////////////////
	static void add_new_client() {
		int count{}, id;
		string name, password, currency;
		double balance;
		//ID
		do {
			system("cls");
			cout << "Enter Client ID (or press '1' to Cancel): ";
			cin >> id;
			cin.ignore();

			if (id == 1) {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (searchForIdClient(id)) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid ID, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Name
		count = 0;
		do {
			system("cls");
			cout << "Enter Client Name (or press '1' to Cancel): ";
			getline(cin, name);

			if (name == "1") {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (!(is_valid_name(name))) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid Name, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Password
		count = 0;
		do {
			system("cls");
			cout << "Enter Password: ";
			getline(cin, password);
			if (!(is_valid_password(password))) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid Password, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Balance
		count = 0;
		do {
			system("cls");
			cout << "Enter Balance: ";
			cin >> balance;
			cin.ignore();
			if (!(is_min_balance(balance))) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid Balance, The Min Balance Is 1500, Try Again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Currency
		system("cls");
		cout << "Enter Currency: ";
		getline(cin, currency);

		Client c(id, name, password, balance, currency);
		clients.push_back(c);
		system("cls");
		cout << "Client added successfully.\n";
		this_thread::sleep_for(chrono::seconds(2));
		return;
	}
	static void search_for_client_by_id() {
		int count{}, id;
		do {
			system("cls");
			cout << "Enter Client ID (or press '1' to Cancel): ";
			cin >> id;
			cin.ignore();

			if (id == 1) {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (!(searchForIdClient(id))) {
				count++;
				if (count == 2) {
					cout << "Can not find this ID\n";
					this_thread::sleep_for(chrono::seconds(2));
					return;
				}
				cout << "Invalid ID, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else {
				system("cls");
				Client* c = find_client(id);
				cout << "Found. Client Tnfo...\n";
				c->displayClintInfo();
				system("pause");
				return;
			}
		} while (true);
	}
	static void list_all_clients() {
		system("cls");
		cout << "---------  All Clients  ----------\n\n";
		for (auto& c : clients) {
			c.displayClintInfo();
			cout << "\n--------------------\n\n";
		}
		system("pause");
	}
	static void edit_info_client() {
		int id;
		Client* c;

		system("cls");
		cout << "Enter Client ID (or press '1' to Cancel): ";
		cin >> id;
		cin.ignore();

		if (id == 1) {
			system("cls");
			cout << "Operation cancelled. Returning to menu...\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		if (!(searchForIdClient(id))) {
			cout << "Can not find this Client\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}

		system("cls");
		c = find_client(id);
		cout << "Found. Client Tnfo...\n";
		c->displayClintInfo();

		int count{};
		do {
			cout << "====     Info Of Client    ====\n\n";
			cout << "1. Name\n";
			cout << "2. password\n";
			cout << "3. Balance\n";
			cout << "4. currency\n";
			cout << "5. Main Menu\n";
			cout << "\nChoice (1-5): ";

			char choice;
			cin >> choice;
			cin.ignore();

			switch (choice) {
				case '1': {
					string name;
					system("cls");
					c->displayClintInfo();
					cout << "Enter New Client Name (or press '1' to Cancel): ";
					getline(cin, name);

					if (name == "1") {
						system("cls");
						cout << "Operation cancelled. Returning to menu...\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					if (!(is_valid_name(name))) {
						cout << "Invalid Name.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					else {
						c->setName(name);
						cout << "Name updated successfully.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}

				}; break;
				case '2': {
					string password;
					system("cls");
					c->displayClintInfo();
					cout << "Enter Password (or press '1' to Cancel): ";
					getline(cin, password);

					if (password == "1") {
						system("cls");
						cout << "Operation cancelled. Returning to menu...\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					if (!(is_valid_password(password))) {
						cout << "Invalid Password.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					else {
						c->setPassword(password);
						cout << "Password updated successfully.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}

				}; break;
				case '3': {
					double balance;
					system("cls");
					c->displayClintInfo();
					cout << "Enter Balance (or press '1' to Cancel): ";
					cin >> balance;
					cin.ignore();

					if (balance == 1) {
						system("cls");
						cout << "Operation cancelled. Returning to menu...\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					if (!(is_min_balance(balance))) {
						cout << "Invalid Balance, The Min Balance Is 1500, Try Again.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					else {
						c->setBalance(balance);
						cout << "Balance updated successfully.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
				}; break;
				case '4': {
					string currency;
					system("cls");
					c->displayClintInfo();
					cout << "Enter Currency (or press '1' to Cancel): ";
					getline(cin, currency);

					if (currency == "1") {
						system("cls");
						cout << "Operation cancelled. Returning to menu...\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					c->setCurrency(currency);
					cout << "Currency updated successfully.\n";
					this_thread::sleep_for(chrono::seconds(2));
					return;
				}; break;
				case '5':return; break;
				default: { cout << "Wrong input\n"; count++; } break;
			}
			if (count == 3)
				return;
			if (anothe_obration() == false)
				return;
		} while (true);
	}

	static void login_as_employee() {
		system("cls");
		int id;
		cout << "Enter your ID (or press '1' to Cancel): ";
		cin >> id;
		cin.ignore();

		if (id == 1) {
			system("cls");
			cout << "Operation cancelled. Returning to menu...\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		if (!(searchForIdEmployee(id))) {
			cout << "Can not find this ID\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		Employee* e = find_employee(id);

		string password;
		int count = 0;
		do {
			cout << "Enter your Password (or press '1' to Cancel):";
			getline(cin, password);

			if (password == "1") {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (!(e->getPassword() == password)) {
				system("cls");
				cout << "Invalid Password, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
				count++;
				if (count == 3)
					return;
			}
			else {
				employee_menu(*e);
				return;
			}
		} while (true);
	}
	static void employee_menu(Employee& e) {
		int count{};
		do {
			system("cls");
			cout << "====    Employee Menu   ====\n\n";
			cout << "1. Add New Client\n";
			cout << "2. Search For Client By ID\n";
			cout << "3. List All Clients\n";
			cout << "4. Edit Info Client\n";
			cout << "5. Display Your Info \n";
			cout << "6. Main Menu\n";
			cout << "\nChoice (1-6): ";

			char choice;
			cin >> choice;

			switch (choice) {
				case '1': {add_new_client(); } break;
				case '2': {search_for_client_by_id();} break;
				case '3': {list_all_clients();} break;
				case '4': {edit_info_client();} break;
				case '5': { system("cls"); e.displayEmployeeInfo(); system("pause"); } break;
				case '6':return; break;
				default: { cout << "Wrong input\n"; count++; } break;
			}
			if (count == 3)
				return;
			if (anothe_obration() == false)
				return;

		} while (true);
	}
	/////////////////////////////////////
	
	//Admin
	/////////////////////////////////////
	static void  add_new_employee(){
		int count{}, id;
		string name, password, currency;
		double salary;
		//ID
		do {
			system("cls");
			cout << "Enter Employee ID (or press '1' to Cancel): ";
			cin >> id;
			cin.ignore();

			if (id == 1) {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (searchForIdEmployee(id)) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid ID, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Name
		count = 0;
		do {
			system("cls");
			cout << "Enter Employee Name (or press '1' to Cancel): ";
			getline(cin, name);

			if (name == "1") {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (!(is_valid_name(name))) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid Name, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Password
		count = 0;
		do {
			system("cls");
			cout << "Enter Password (or press '1' to Cancel): ";
			getline(cin, password);

			if (password == "1") {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (!(is_valid_password(password))) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid Password, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Balance
		count = 0;
		do {
			system("cls");
			cout << "Enter Salary (or press '1' to Cancel): ";
			cin >> salary;
			cin.ignore();

			if (salary == 1) {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (!(is_min_salary(salary))) {
				count++;
				if (count == 2)
					return;
				cout << "Invalid Salary,The Min Salary Ts 5000, Try Again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else
				break;

		} while (true);
		//Currency
		system("cls");
		cout << "Enter Currency (or press '1' to Cancel): ";
		getline(cin, currency);

		if (currency == "1") {
			system("cls");
			cout << "Operation cancelled. Returning to menu...\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		Employee e(id, name, password, salary, currency);
		employee.push_back(e);
		system("cls");
		cout << "Employee added successfully.\n";
		this_thread::sleep_for(chrono::seconds(2));
		return;
	}
	static void  search_for_employee_by_id(){
		int count{}, id;
		do {
			system("cls");
			cout << "Enter Employee ID (or press '1' to Cancel): ";
			cin >> id;
			cin.ignore();

			if (id == 1) {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (!(searchForIdEmployee(id))) {
				count++;
				if (count == 2) {
					cout << "Can not find this ID\n";
					this_thread::sleep_for(chrono::seconds(2));
					return;
				}
				cout << "Invalid ID, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
			}
			else {
				system("cls");
				Employee* e = find_employee(id);
				cout << "Found. Employee Tnfo...\n";
				e->displayEmployeeInfo();
				system("pause");
				return;
			}
		} while (true);
	
	}
	static void  list_all_employees(){
		system("cls");
		cout << "---------  All Employee  ----------\n\n";
		for (auto& e : employee) {
			e.displayEmployeeInfo();
			cout << "\n--------------------\n\n";
		}
		system("pause");
	}
	static void  edit_employee() {
		int id;
		Employee* e;

		system("cls");
		cout << "Enter Employee ID (or press '1' to Cancel): ";
		cin >> id;
		cin.ignore();

		if (id == 1) {
			system("cls");
			cout << "Operation cancelled. Returning to menu...\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		if (!(searchForIdEmployee(id))) {
			cout << "Can not find this Client\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}

		system("cls");
		e = find_employee(id);
		cout << "Found. Client Tnfo...\n";
		e->displayEmployeeInfo();

		int count{};
		do {
			cout << "====     Info Of Employee    ====\n\n";
			cout << "1. Name\n";
			cout << "2. password\n";
			cout << "3. Salary\n";
			cout << "4. currency\n";
			cout << "5. Main Menu\n";
			cout << "\nChoice (1-5): ";

			char choice;
			cin >> choice;
			cin.ignore();

			switch (choice) {
				case '1': {
					string name;
					system("cls");
					e = find_employee(id);
					cout << "Enter New Employee Name (or press '1' to Cancel): ";
					getline(cin, name);

					if (name == "1") {
						system("cls");
						cout << "Operation cancelled. Returning to menu...\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					if (!(is_valid_name(name))) {
						cout << "Invalid Name.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					else {
						e->setName(name);
						cout << "Name updated successfully.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}

				}; break;
				case '2': {
					string password;
					system("cls");
					e = find_employee(id);
					cout << "Enter Password (or press '1' to Cancel): ";
					getline(cin, password);

					if (password == "1") {
						system("cls");
						cout << "Operation cancelled. Returning to menu...\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					if (!(is_valid_password(password))) {
						cout << "Invalid Password.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					else {
						e->setPassword(password);
						cout << "Password updated successfully.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}

				}; break;
				case '3': {
					double salary;
					system("cls");
					e = find_employee(id);
					cout << "Enter Balance (or press '1' to Cancel): ";
					cin >> salary;
					cin.ignore();

					if (salary == 1) {
						system("cls");
						cout << "Operation cancelled. Returning to menu...\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					if (!(is_min_salary(salary))) {
						cout << "Invalid Salary,The Min Salary Ts 5000, Try Again.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					else {
						e->setSalary(salary);
						cout << "Salary updated successfully.\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
				}; break;
				case '4': {
					string currency;
					system("cls");
					e = find_employee(id);
					cout << "Enter Currency (or press '1' to Cancel): ";
					getline(cin, currency);
					e->setCurrency(currency);

					if (currency == "1") {
						system("cls");
						cout << "Operation cancelled. Returning to menu...\n";
						this_thread::sleep_for(chrono::seconds(2));
						return;
					}
					cout << "Currency updated successfully.\n";
					this_thread::sleep_for(chrono::seconds(2));
					return;
				}; break;
				case '5':return; break;
				default: { cout << "Wrong input\n"; count++; } break;
			}
			if (count == 3)
				return;
			if (anothe_obration() == false)
				return;

		} while (true);
	}

	static void  admin_menu(Admin& a) {
		int count{};
		do {
			system("cls");
			cout << "====    Admin Menu   ====\n\n";
			cout << "1. Add New Client\n";
			cout << "2. Search For Client By ID\n";
			cout << "3. List All Clients\n";
			cout << "4. Edit Info Client\n";
			cout << "5. Add New Employee \n";
			cout << "6. Search For Employee By ID\n";
			cout << "7. List All Employees \n";
			cout << "8. Edit Employee \n";
			cout << "9. Display Your Info \n";
			cout << "0. Main Menu\n";
			cout << "\nChoice (0-9): ";

			char choice;
			cin >> choice;

			switch (choice) {
				case '1':add_new_client(); break;
				case '2':search_for_client_by_id(); break;
				case '3':list_all_clients(); break;
				case '4':edit_info_client(); break;
				case '5':add_new_employee(); break;
				case '6':search_for_employee_by_id(); break;
				case '7':list_all_employees(); break;
				case '8':edit_employee(); break;
				case '9': { system("cls"); a.displayEmployeeInfo();system("pause");}break;
				case '0':return; break;
				default: { cout << "Wrong input\n"; count++; } break;
			}
			if (count == 3)
				return;
			if (anothe_obration() == false)
				return;

		} while (true);
	}
	static void login_as_admin() {
		system("cls");
		int id;
		cout << "Enter your ID (or press '1' to Cancel): ";
		cin >> id;
		cin.ignore();

		if (id == 1) {
			system("cls");
			cout << "Operation cancelled. Returning to menu...\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		if (!(searchForIdAdmin(id))) {
			cout << "Can not find this ID\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		Admin* a = find_admin(id);

		string password;
		int count = 0;
		do {
			cout << "Enter your Password (or press '1' to Cancel): ";
			getline(cin, password);

			if (password == "1") {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return;
			}
			if (!(a->getPassword() == password)) {
				system("cls");
				cout << "Invalid Password, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
				count++;
				if (count == 3)
					return;
			}
			else {
				admin_menu(*a);
				return;
			}
		} while (true);
	}
	////////////////////////////////////

	//client
	///////////////////////////////////////
	static bool anothe_obration() {
		int count{};
		do {
			system("cls");
			cout << "Do you want to make another transaction (y/n) or (1/0)?\n";
			char choice;
			cin >> choice;

			if (choice == 'y' || choice == 'Y' || choice == '1') return true;
			else if (choice == 'n' || choice == 'N' || choice == '0') return false;
			else {
				cout << "Wrong input\n";
				this_thread::sleep_for(chrono::seconds(2));
				count++;
			}
			if (count == 3)	return false;

		} while (true);
	}
	static int getValidAmount(const string& titel) {
		int count{};
		int amount;

		do {

			system("CLS");
			cout << "====   " << titel << "   ====\n\n";
			cout << "(Note: You can " << titel << " in multiples of 100 only, up to a maximum of 12000)\n";
			cout << "\nEnter amount (or press '1' to return): ";
			cin >> amount;
			cin.ignore();

			if (amount == 1) {
				system("cls");
				cout << "Operation cancelled. Returning to menu...\n";
				this_thread::sleep_for(chrono::seconds(2));
				return -1;
			}
			if (amount <= 0 || amount > 12000) {
				cout << "\nInvalid amount.\n";
				this_thread::sleep_for(chrono::seconds(3));
				count++;
				if (count == 2)
					return 0;
			}
			else if (amount % 100 != 0) {
				cout << "\nAmount must be 100 or a multiple of 100.\n";
				this_thread::sleep_for(chrono::seconds(3));
				count++;
				if (count == 2)
					return 0;
			}
			else
				return amount;

		} while (true);
	}
	static void deposit(Client& c) {
		system("CLS");

		int amount = getValidAmount("Deposit");
		if (amount <= 0)
			return;

		c.deposit(amount);
		cout << "\nDeposit successful. " << amount << " has been added to your account." << endl;

		this_thread::sleep_for(chrono::seconds(3));
	}
	static void withdraw(Client& c) {
		system("CLS");

		int amount = getValidAmount("Withdraw");
		if (amount <= 0)
			return;

		if (c.checkAvailableBalance(amount)) {
			c.withDraw(amount);
			cout << "\nWithdrawal successful. " << amount << " has been withdrawn from your account." << endl;
		}
		else
			cout << "\nTransaction failed: Insufficient balance.\n";
		this_thread::sleep_for(chrono::seconds(3));
	}
	static void balance(Client& c) {
		system("CLS");
		cout << "====   Balance   ====\n\n";
		c.checkBalance();
		cout << endl;
		system("pause");
	}
	static void transfer(Client& c) {
		system("CLS");
		int amount, recipientId;


		cout << "Enter Recipient ID (or press '1' to return): ";
		cin >> recipientId;
		cin.ignore();

		if (recipientId == 1) {
			system("cls");
			cout << "Operation cancelled. Returning to menu...\n";
			this_thread::sleep_for(chrono::seconds(2));
			return ;
		}
		if (recipientId == c.getID()) {
			cout << "Cannot transfer to your own account.\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}

		if (!(searchForIdClient(recipientId))) {
			cout << "Can not find this Account\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		Client* re;
		re = find_client(recipientId);

		amount = getValidAmount("Transfer");
		if (amount <= 0)
			return;

		if (c.checkAvailableBalance(amount)) {
			c.transFerTo(amount, *re);
			cout << "\nWithdrawal successful. " << amount << " has been withdrawn from your account." << endl;
		}
		else
			cout << "\nTransaction failed: Insufficient balance.\n";

		this_thread::sleep_for(chrono::seconds(2));

	}

	static void  client_menu(Client& c) {
		int count{};
		do {
			system("cls");
			cout << "====    Client Menu   ====\n\n";
			cout << "1. Deposit\n";
			cout << "2. Withdraw\n";
			cout << "3. Balance\n";
			cout << "4. Transfer\n";
			cout << "5. Main Menu\n";
			cout << "\nChoice (1-5): ";

			char choice;
			cin >> choice;

			switch (choice) {
			case '1':deposit(c); break;
			case '2':withdraw(c); break;
			case '3':balance(c); break;
			case '4':transfer(c); break;
			case '5':return; break;
			default: { cout << "Wrong input\n"; count++; } break;
			}
			if (count == 3)
				return;
			if (anothe_obration() == false)
				return;

		} while (true);
	}
	static void login_as_client() {
		system("cls");
		int id;
		cout << "Enter your ID (or press '1' to return): ";
		cin >> id;
		cin.ignore();

		if (id == 1) {
			system("cls");
			cout << "Operation cancelled. Returning to menu...\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}

		if (!(searchForIdClient(id))) {
			cout << "Can not find this ID\n";
			this_thread::sleep_for(chrono::seconds(2));
			return;
		}
		Client* c = find_client(id);

		string password;
		int count = 0;
		do {
			cout << "Enter your Password: ";
			getline(cin, password);

			if (!(c->getPassword() == password)) {
				system("cls");
				cout << "Invalid Password, try again.\n";
				this_thread::sleep_for(chrono::seconds(2));
				count++;
				if (count == 3)
					return;
			}
			else {
				client_menu(*c);
				return;
			}
		} while (true);
	}
	///////////////////////////////////////
	
	//screan
	///////////////////////////////////////
	/*static void welcom_screan() {
		system("CLS");
		system("color 0b");


		cout << "\n\n\n\n\n\n\n\n\n\n\n"
			"##         ##         ##  ## ## ##  ##        ## ##     ## ##         ##           ##         ## ## ##  ## ##         \n" <<
			" ##      ##  ##      ##   ##        ##       ##       ##     ##     ##  ##       ##  ##          ##   ##     ##     \n" <<
			"  ##    ##    ##    ##    ## ## ##  ##      ##       ##       ##   ##     ##    ##    ##         ##  ##       ##    \n" <<
			"   ##  ##      ##  ##     ##        ##       ##       ##     ##   ##       ##  ##      ##        ##   ##     ##      \n" <<
			"     ##          ##       ## ## ##  ## ## ##  ## ##     ## ##    ##          ##         ##       ##     ## ##         \n\n\n\n";

		cout
			<< "                                                                  ## ##   ## ## ##   ## ## ##     ## ## ##       ##        ##     ##  ##   ##\n"
			<< "                                                                 ##          ##      ##     ##    ##     ##    ##  ##     ## ##   ##  ##  ##\n"
			<< "                                                                ##           ##      ## ## ##     ## ## ##    ## ## ##    ##  ##  ##  ## ##\n"
			<< "                                                                 ##          ##      ##     ##    ##     ##  ##      ##   ##   ## ##  ##  ##\n"
			<< "                                                                  ## ##   ## ## ##   ## ## ##     ## ## ##  ##        ##  ##     ##   ##   ##\n\n";

		this_thread::sleep_for(chrono::seconds(3));
		system("color 0F");
		system("cls");

	}*/
	static void EX_screan() {
		system("CLS");
		system("color 0B");
		cout << "\n\n\n\n\n\n\n\n\n\n\n"
			<< "\n######## ##     ##    ###    ##    ## ##    ##    ##    ##  #######  ##     ##    ########  #######  ########     ##     ##  ######  #### ##    ##  ######  "
			<< "\n   ##    ##     ##   ## ##   ###   ## ##   ##      ##  ##  ##     ## ##     ##    ##       ##     ## ##     ##    ##     ## ##    ##  ##  ###   ## ##    ## "
			<< "\n   ##    ##     ##  ##   ##  ####  ## ##  ##        ####   ##     ## ##     ##    ##       ##     ## ##     ##    ##     ## ##        ##  ####  ## ##       "
			<< "\n   ##    ######### ##     ## ## ## ## #####          ##    ##     ## ##     ##    ######   ##     ## ########     ##     ##  ######   ##  ## ## ## ##   ####"
			<< "\n   ##    ##     ## ######### ##  #### ##  ##         ##    ##     ## ##     ##    ##       ##     ## ##   ##      ##     ##       ##  ##  ##  #### ##    ## "
			<< "\n   ##    ##     ## ##     ## ##   ### ##   ##        ##    ##     ## ##     ##    ##       ##     ## ##    ##     ##     ## ##    ##  ##  ##   ### ##    ## "
			<< "\n   ##    ##     ## ##     ## ##    ## ##    ##       ##     #######   #######     ##        #######  ##     ##     #######   ######  #### ##    ##  ######  ";

		cout
			<< "\n\n\n"
			<< "\n                                                      ######## ##     ## ########    ########     ###    ##    ## ##    ## #### ##    ##  ######       ######  ##    ##  ######  ######## ######## ##     ##  "
			<< "\n                                                         ##    ##     ## ##          ##     ##   ## ##   ###   ## ##   ##   ##  ###   ## ##    ##     ##    ##  ##  ##  ##    ##    ##    ##       ###   ###  "
			<< "\n                                                         ##    ##     ## ##          ##     ##  ##   ##  ####  ## ##  ##    ##  ####  ## ##           ##         ####   ##          ##    ##       #### ####  "
			<< "\n                                                         ##    ######### ######      ########  ##     ## ## ## ## #####     ##  ## ## ## ##   ####     ######     ##     ######     ##    ######   ## ### ##  "
			<< "\n                                                         ##    ##     ## ##          ##     ## ######### ##  #### ##  ##    ##  ##  #### ##    ##           ##    ##          ##    ##    ##       ##     ##  "
			<< "\n                                                         ##    ##     ## ##          ##     ## ##     ## ##   ### ##   ##   ##  ##   ### ##    ##     ##    ##    ##    ##    ##    ##    ##       ##     ## ### "
			<< "\n                                                         ##    ##     ## ########    ########  ##     ## ##    ## ##    ## #### ##    ##  ######       ######     ##     ######     ##    ######## ##     ## ### ";

		this_thread::sleep_for(chrono::seconds(3));
		system("CLS");
		system("color 0F");
	}
	///////////////////////////////////////
};

