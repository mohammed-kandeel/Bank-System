#include "Admin.h"
#include"FilesHelper.h"
#include"FileManager.h"
map<int, Admin>Admin::admin;

void Admin::saveNewEmployeeToFile(Employee& employee) {
	FileManager::addEmployee(employee);
}