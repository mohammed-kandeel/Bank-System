#include "Admin.h"
#include"FileManager.h"
map<int, Admin>Admin::admins;

void Admin::saveNewEmployeeToFile(Employee& employee) {
	FileManager::addEmployee(employee);
}