#pragma once
#include "CreditCard.h"
#include "DebitCard.h"

class AccountCard{
public:
	CreditCard* credit;
	DebitCard* debit;
	AccountCard() {
		credit = nullptr;
		debit = nullptr;
	}	
	AccountCard(const AccountCard& card) {
		if (card.credit)
			this->credit = new CreditCard(*card.credit);
		else
			this->credit = nullptr;

		if (card.debit)
			this->debit = new DebitCard(*card.debit);
		else
			this->debit = nullptr;
	}
	void operator=(const AccountCard& card) {
		if (credit != nullptr)
			delete credit;
		if (debit != nullptr)
			delete debit;

		if (card.credit)
			this->credit = new CreditCard(*card.credit);
		else
			this->credit = nullptr;

		if (card.debit)
			this->debit = new DebitCard(*card.debit);
		else
			this->debit = nullptr;
	}
	~AccountCard() {
		delete credit;
		delete debit;
	}

};