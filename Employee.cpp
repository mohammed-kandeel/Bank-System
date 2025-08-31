#include "Employee.h"
#include"FilesHelper.h"
map<int, Employee*>Employee::employees;

int Employee::getNewClientIDfromFile() {
	return	FilesHelper::getLastId("LastClientId.txt");
}
int Employee::getNewCardIDfromFile() {
	return	FilesHelper::getLastId("LastCardId.txt");
}