#pragma once
#include"Validation.h"
class Account{
private:
	//atts
	double balance;
	string currency;
public:
	//cons
	Account() {
		this->balance = 0.0;
	}
	Account(double balance, string currency) {
		setBalance(balance);
		this->currency = currency;
	}
	//gets
	double getBalance() {
		return balance;
	}
	string getCurrency() {
		return currency;
	}
	//sets
	void setBalance(double balance) {
		if (Validation::is_min_balance(balance))
			this->balance = balance;
		else cout << "Balance must be >= 1500\n";
	}
	void setCurrency(string currency) {
		this->currency = currency;
	}
	//meths
	void deposit(double amount) {
		if (amount >= 0) {
			balance += amount;
		}
		else 
			cout << "Deposit amount must be positive.\n";
	}
	void withDraw(double amount) {
		if (amount > 0 && amount <= balance) {
			balance -= amount;
		}
		else cout << "Invalid withdrawal amount.\n";
	}
	bool checkAvailableBalance(double amount) {
		return balance >= amount;
	}
};






// ================== PaymentMethod ==================
#include<iostream>
#include<string>
using namespace std;
#pragma once
class PaymentMethod {
protected:
    int id;
    string expiryDate;
    Account* account;
public:
    PaymentMethod(int id, string expiryDate, Account* account) {
        this->id = id;
        this->expiryDate = expiryDate;
        this->Account = account;
    }

    // دوال pure virtual
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;

    // check expiry
    bool isExpired(string currentDate) {
        return currentDate > expiryDate;
    }

    virtual ~PaymentMethod() {}
};

// ================== DebitCard ==================
#include<iostream>
#include<string>
#include<PaymentMethod.h>
#pragma once
class DebitCard : public PaymentMethod {
public:
    DebitCard(int id, string expiryDate, Account* account)
        : PaymentMethod(id, expiryDate, account) {
    }

    void deposit(double amount) {
        if (!isExpired("01/2025"))
            account->deposit(amount);
        else
            cout << "Debit card expired!\n";
    }

    void withdraw(double amount) {
        if (!isExpired("01/2025"))
            account->withdraw(amount);
        else
            cout << "Debit card expired!\n";
    }
};



// ================== CreditCard ==================
#include<iostream>
#include<string>
#include<PaymentMethod.h>
#pragma once
class CreditCard : public PaymentMethod {
private:
    double creditLimit;
    double usedCredit;
public:
    CreditCard(int id, string expiryDate, Account* account, double creditLimit)
        : PaymentMethod(id, expiryDate, account), creditLimit(creditLimit), usedCredit(0) {
    }

    void deposit(double amount) {
        if (!isExpired("01/2025")) {
            usedCredit -= amount;
            if (usedCredit < 0) {
                account->deposit(-usedCredit); // 
                usedCredit = 0;
            }
            cout << "Credit payment done!\n";
        }
        else {
            cout << "Credit card expired!\n";
        }
    }

    void withdraw(double amount) {
        if (!isExpired("01/2025")) {
            if (usedCredit + amount <= creditLimit) {
                usedCredit += amount;
                cout << "Credit used: " << usedCredit << "/" << creditLimit << endl;
            }
            else {
                cout << "Credit limit exceeded!\n";
            }
        }
        else {
            cout << "Credit card expired!\n";
        }
    }
};

