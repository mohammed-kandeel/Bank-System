#include "FileManager.h"
#include "FilesHelper.h"

void FileManager::addClient(Client& c) {
	FilesHelper::saveClient(c);
}
void FileManager::addEmployee(Employee& e) {
	FilesHelper::saveEmployee("Employee.txt", "LastEmployeeId.txt", e);
}
void FileManager::addAdmin(Admin& a) {
	FilesHelper::saveEmployee("Admin.txt", "LastAdminId.txt", a);
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
	FilesHelper::clearFile("Client.txt", "LastClientId.txt");
}
void FileManager::removeAllEmployee() {
	FilesHelper::clearFile("Employee.txt", "LastEmployeeId.txt");
}
void FileManager::removeAllAdmins() {
	FilesHelper::clearFile("Admin.txt", "LastAdminId.txt");
}