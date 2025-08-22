#include "Employee.h"
#include"FilesHelper.h"
#include"FileManager.h"
map<int, Employee>Employee::employees;
int Employee::getNewClientIDfromFile() {
	return	FilesHelper::getLastId("LastClientId.txt");
}
void Employee::saveNewClienttoFile(Client& c) {
	FileManager::addClient(c);
}