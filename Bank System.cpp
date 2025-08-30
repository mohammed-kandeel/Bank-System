#include <iostream>
#include <string>
#include "FileManager.h"
#include "FilesHelper.h"
#include "Client.h"
using namespace std;

int main(){
	FilesHelper::getClients();


	Client c2,c5, c(1, "mohamed", "12345678", 15000, 1, 15000);
	c.setNewCard(AccountType::EGP,CardType::Debit ,1, "1-2030",0);
	c.setNewCard(AccountType::USD,CardType::Debit, 2, "2-2030",0);
	
	c.setNewCard(AccountType::EGP,CardType::Credit, 3, "3-2030", 10000);
	c.setNewCard(AccountType::USD,CardType::Credit, 4, "4-2030", 10000);

	/*c.displayClientInfo();
	FileManager::addClient(c);*/
	

	/*c2 = Client::clients.find(2)->second;
	cout << "\n----------------------------\n";
	c2.displayClientInfo();*/


	/*c5 = Client::clients.find(5)->second;
	cout << "\n----------------------------\n";
	c5.displayClientInfo();*/


	//FilesHelper::clearFile("Client.txt", "LastClientId.txt");
	for (auto i = Client::clients.begin(); i != Client::clients.end(); i++) {

		//FileManager::addClient(i->second);


		//cout << "\n----------------------------\n";
		//i->second.displayClientInfo();
	
	
	}



}