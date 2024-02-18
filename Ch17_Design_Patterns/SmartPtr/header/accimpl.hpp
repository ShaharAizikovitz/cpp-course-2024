//====================================================================
// File:        accimpl.hpp
// Description: Declaration of account_impl class, which contains the
//              implementation of a bank account.
//====================================================================

#ifndef ACCOUNT_IMPL_INCLUDED
#define ACCOUNT_IMPL_INCLUDED

#include "account.hpp"
#include <string>

// Implementation class
class account_impl : public account
{
public:
    // Initialise account object with opening_balance
    account_impl(const std::string & number, double opening_balance = 0);

    // Deposit money
    void deposit(double amount);

    // Withdraw money
	bool withdraw(double amount);

    // Return current balance
    double balance() const;

    // Return details
	std::string details() const;

private:
	std::string number;
    double current_balance;
	size_t deposits, withdrawals;
};

#endif 