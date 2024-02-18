//====================================================================
// File:        accproxy.hpp
// Description: Declaration of account_proxy class, which acts as a proxy
//              for account_impl 
//====================================================================

#ifndef ACCOUNT_PROXY_INCLUDED
#define ACCOUNT_PROXY_INCLUDED

#include "account.hpp"
#include "accimpl.hpp"
#include <memory>
#include <string>

// Forward declaration
class account_impl;


// Proxy class
class account_proxy : public account
{
public:
	// Constructor - just remembers the account number
	account_proxy(const std::string &number);

    // Deposit money
    void deposit(double amount);
    
	// Withdraw money
	bool withdraw(double amount);

    // Return current balance
    double balance() const;

	// Return details of transactions
	std::string details() const;

private:
	// Load account_impl object if-and-when needed
	void load() const;
	
	// Initialised from constructor argument
	std::string account_number;

	// Target account_imp object, null initially
	mutable std::unique_ptr<account_impl> target;
};

#endif 

