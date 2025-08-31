#pragma once
#include"DataSourceInterface.h"
#include"FilesHelper.h"

class FileManager:public DataSourceInterface {
public:
	//save one person to file
	static void addClient(Client& c);         //.ccp
	static void addEmployee(Employee& e);    //.ccp
	static void addAdmin(Admin& a);         //.ccp

	//get all persons data from the files
	static void getAllClients();      //.ccp
	static void getAllEmployees();   //.ccp
	static void getAllAdmins();     //.ccp

	//remove all data from the files
	static void removeAllClients();    //.ccp
	static void removeAllEmployees();  //.ccp
	static void removeAllAdmins();   //.ccp

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

	//update all data (Clients & Employees & Admins)
	static void updateAllData() {
		updateClients();
		updateEmployees();
		updateAdmins();
	}
};