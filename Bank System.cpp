#include <iostream>
#include <string>
#include "FileManager.h"
#include "Client.h"
using namespace std;

int main(){
	FileManager::getAllData();

	//Client *c=new Client(1, "mohamed", "12345678", 1500, 1, 1500);
	//c->setNewCard(AccountType::EGP,CardType::Debit ,1, "1-2030",0);
	//c->setNewCard(AccountType::USD,CardType::Debit, 2, "2-2030",0);
	//c->setNewCard(AccountType::EGP,CardType::Credit, 3, "3-2030", 10000);
	//c->setNewCard(AccountType::USD,CardType::Credit, 4, "4-2030", 10000);

	//Client *c2=new Client(2, "aliaaa", "12345678", 5000, 1, 5000);
	//c2->setNewCard(AccountType::EGP, CardType::Debit, 8, "5-2030", 0);
	//c2->setNewCard(AccountType::USD, CardType::Debit, 7, "6-2030", 0);
	//c2->setNewCard(AccountType::EGP, CardType::Credit, 5, "7-2030", 10000);
	//c2->setNewCard(AccountType::USD, CardType::Credit, 6, "8-2030", 10000);
	
	//Client::clients.insert({ 1,c });
	//Client::clients.insert({ 2,c2 });
	
	Client::clients.at(1)->useDebitCard(AccountType::EGP, 100, Operation::Withdraw);
	Client::clients.at(2)->useDebitCard(AccountType::EGP, 200, Operation::Withdraw);
	//Client::clients.at(1)->transFerTo(200, Client::clients.at(2), AccountType::EGP);
	Client::clients.at(1)->displayClientInfo();
	Client::clients.at(1)->displayClientTransactionHistory();

	cout << "\n\n---------------------------------\n\n";
	
	Client::clients.at(2)->displayClientInfo();
	Client::clients.at(2)->displayClientTransactionHistory();
	//cout<<Client::clients.at(1)->getBalance(AccountType::EGP);
	//cout<<Client::clients.rbegin()->first;   //??? ( ?? ?? ) ?????

	FileManager::updateAllData();
}