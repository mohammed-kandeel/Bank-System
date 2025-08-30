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
};