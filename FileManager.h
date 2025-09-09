#pragma once
#include"DataSourceInterface.h"
#include"FilesHelper.h"

class FileManager:public DataSourceInterface {
public:
	//save one person to file
	static void addClient(Client& c) {
			FilesHelper::saveClient(c);
	}
	static void addEmployee(Employee& e) {
		FilesHelper::saveEmployee("Employees.txt", "LastEmployeeId.txt", e);
	}
	static void addAdmin(Admin& a) {
		FilesHelper::saveEmployee("Admins.txt", "LastAdminId.txt", a);
	}

	//get all persons data from the files
	static void getAllClients() {
		FilesHelper::getClients();
	}
	static void getAllEmployees() {
		FilesHelper::getEmployees();
	}
	static void getAllAdmins() {
		FilesHelper::getAdmins();
	}

	//remove all data from the files
	static void removeAllClients() {
		FilesHelper::clearFile("Clients.txt", "LastClientId.txt");
	}
	static void removeAllEmployees() {
		FilesHelper::clearFile("Employees.txt", "LastEmployeeId.txt");
	}
	static void removeAllAdmins() {
		FilesHelper::clearFile("Admins.txt", "LastAdminId.txt");
	}

	//update data (remove All data & save All data)
	static void updateClients() {
		FilesHelper::updateClients();
	}
	static void updateEmployees() {
		FilesHelper::updateEmployees();
	}
	static void updateAdmins() {
		FilesHelper::updateAdmins();
	}

	//get all data from the files (Clients & Employees & Admins)
	static void getAllData() {
		getAllClients();
		getAllEmployees();
		getAllAdmins();
	}

	// Update all system data (Clients, Employees, and Admins)
	static void updateAllData() {
		// Save the latest changes to files
		updateClients();
		updateEmployees();
		updateAdmins();

		// Clear all objects from memory
		Client::removeAllClients();
		Employee::removeAllEmployees();
		Admin::removeAllAdmins();
	}

};