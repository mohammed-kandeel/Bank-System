#include <iostream>
#include <string>
#include "FileManager.h"
#include "FilesHelper.h"
#include "Client.h"
using namespace std;

int main(){
	Client c2, c(1, "mohamed", "12345678", 15000, 1, 15000);
	c.addDebitCard("EGP", 1, "1-2030");
	c.addDebitCard("USD", 2, "2-2030");
	
	c.addCreditCard("EGP", 3, "3-2030", 10000);
	c.addCreditCard("USD", 4, "4-2030", 10000);

	c.displayClientInfo();

	FileManager::addClient(c);
	FilesHelper::getClients();

	c2 = Client::clients.find(2)->second;
	cout << "\n----------------------------\n";
	c2.displayClientInfo();
}