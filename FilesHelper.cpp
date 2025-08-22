#include "FilesHelper.h"
#include "Employee.h"

int FilesHelper::getLastId(string fileName) {
	int id;
	ifstream getId(fileName, ios::in);
	getId >> id;
	getId.close();
	return id;
}