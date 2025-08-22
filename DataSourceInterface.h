#pragma once
#include"Admin.h"

class DataSourceInterface {
public:
	//save one person to file
	virtual void addClient(Client& c) = 0;
	virtual void addEmployee(Employee& e) = 0;
	virtual void addAdmin(Admin& a) = 0;

	// get all persons data from the files
	virtual void getAllClients() = 0;
	virtual void getAllEmployees() = 0;
	virtual void getAllAdmins() = 0;

	//remove all data from the files
	virtual void removeAllClients() = 0;
	virtual void removeAllEmployees() = 0;
	virtual void removeAllAdmins() = 0;
};