//====================================================================
// File:        account.hpp
// Description: Interface class - defines the common interface for the
//              account_proxy and account_impl classes.
//====================================================================

#ifndef ACCOUNT_INCLUDED
#define ACCOUNT_INCLUDED

#include <string>

// Interface class
class account
{
public:
	// Deposit money 
	virtual void deposit(double amount) = 0;

    // Withdraw money
	virtual bool withdraw(double amount) = 0;

    // Return current balance
    virtual double balance() const = 0;

	// Return details of transactions
	virtual std::string details() const = 0;

	// Virtual destructor
	virtual ~account() {}

};

#endif 