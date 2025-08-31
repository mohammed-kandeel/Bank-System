#include "FileManager.h"
#include "FilesHelper.h"

void FileManager::addClient(Client& c) {
	FilesHelper::saveClient(c);
}
void FileManager::addEmployee(Employee& e) {
	FilesHelper::saveEmployee("Employees.txt", "LastEmployeeId.txt", e);
}
void FileManager::addAdmin(Admin& a) {
	FilesHelper::saveEmployee("Admins.txt", "LastAdminId.txt", a);
}

// get all persons data from the files
void FileManager::getAllClients() {
	FilesHelper::getClients();
}
void FileManager::getAllEmployees() {
	FilesHelper::getEmployees();
}
void FileManager::getAllAdmins() {
	FilesHelper::getAdmins();
}

//remove all data from the files
void FileManager::removeAllClients() {
	FilesHelper::clearFile("Clients.txt", "LastClientId.txt");
}
void FileManager::removeAllEmployees() {
	FilesHelper::clearFile("Employees.txt", "LastEmployeeId.txt");
}
void FileManager::removeAllAdmins() {
	FilesHelper::clearFile("Admins.txt", "LastAdminId.txt");
}