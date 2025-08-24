#pragma once
#include "PaymentMethod.h"

class DebitCard : public PaymentMethod {
public:
    //cons
    DebitCard(){}
    DebitCard(int id, string expiryDate, Account* account): PaymentMethod(id, expiryDate, account) {}
    //meths
    void deposit(double amount) {
        if (!isExpired("01-2025"))   
            account->deposit(amount);
        else
            cout << "Debit card expired!\n";
    }
    void withdraw(double amount) {
        if (!isExpired("01-2025"))
            account->withDraw(amount);
        else
            cout << "Debit card expired!\n";
    }
};