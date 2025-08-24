#pragma once
#include "PaymentMethod.h"

class CreditCard : public PaymentMethod {
private:
    //atts
    double creditLimit;
    double usedCredit;
public:
    //cons
    CreditCard() {
        creditLimit = 0.0;
        usedCredit = 0.0;
    }
    CreditCard(int id, string expiryDate, Account* account, double creditLimit) : PaymentMethod(id, expiryDate, account) {
        this->usedCredit = 0;
        this->creditLimit = creditLimit;
    }
    //set
    void setCreditLimit(double creditLimit) {
        this->creditLimit = creditLimit;
    }
    //gets
    double getCreditLimit() {
        return creditLimit;
    }
    double getUsedCredit() {
        return usedCredit;
    }
    //meths
    void deposit(double amount) {
        if (account == nullptr) {
            cout << "No linked account!\n";
            return;
        }

        if (!isExpired("01-2025")) {
            if (usedCredit > 0) {
                usedCredit -= amount;
                if (usedCredit < 0) {
                    account->deposit(-usedCredit);
                    usedCredit = 0;
                }
                cout << "Credit payment done!\n";
            }
            else {
                account->deposit(amount);
                cout << "Direct deposit to account!\n";
            }
        }
        else {
            cout << "Credit card expired!\n";
        }
    }
    void withdraw(double amount) {
        if (account == nullptr) {
            cout << "No linked account!\n";
            return;
        }

        if (!isExpired("01-2025")) {
            if (usedCredit + amount <= creditLimit) {
                usedCredit += amount;
                //cout << "Credit used: " << usedCredit << " / " << creditLimit << endl;
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

