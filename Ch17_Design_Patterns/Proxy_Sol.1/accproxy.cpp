//====================================================================
// File:        accproxy.cpp
// Description: Implementation of account_proxy class, which acts as a proxy
//              for account_impl 
//====================================================================

#include "accproxy.hpp"
#include "bank.hpp"
#include "accimpl.hpp"

using namespace std;

// Constructor - just remembers the account number
account_proxy::account_proxy(const string &number)
	: account_number(number)
{}


// Deposit money
void account_proxy::deposit(double amount)
{
	load();
	target->deposit(amount);
}


// Withdraw money
bool account_proxy::withdraw(double amount)
{
	load();
	return target->withdraw(amount);
}


// Return current balance
double account_proxy::balance() const
{
	load();
	return target->balance();
}


// Return account details
string account_proxy::details() const
{
	load();
	return target->details();
}


// Load account_impl object if-and-when needed
void account_proxy::load() const
{
	if (!target)
		target.reset(bank::instance().create_account(account_number));
}


