#pragma once
#include "Account.h"

class PaymentMethod{
protected:
    //atts
    int id;
    string expiryDate; //month-year
    Account* account;
public:
    //cons
    PaymentMethod() {
        id = 0;
        expiryDate = "mm-yyyy";
        account = nullptr;
    }
    PaymentMethod(int id, string expiryDate, Account* account) {
        this->id = id;
        this->expiryDate = expiryDate;
        this->account = account;
    }
    //keys
    bool isExpired(string currentDate) {
        return currentDate >= expiryDate;
    }
    //sets
    void setIdCard(int id) {
        this->id = id;
    }
    void setExpiryDateCard(string idexpiryDate){
        this->expiryDate = expiryDate;
    }
    //gets
    int getIdCard() {
        return id;
    }
    string getExpiryDateCard() {
        return expiryDate;
    }
    //meths
    virtual void deposit(double amount) = 0;
    virtual void withdraw(double amount) = 0;
};

