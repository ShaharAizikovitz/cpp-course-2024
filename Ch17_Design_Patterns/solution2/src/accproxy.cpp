//====================================================================
// File:        accproxy.cpp
// Description: Implementation of account_ptr and account_proxy classes, 
//              which acts as a proxies for account_impl  
//====================================================================

#include "accproxy.hpp"
#include "bank.hpp"
#include "accimpl.hpp"

using namespace std;

//====================================================================
// account_ptr implementation
//====================================================================

// Constructor - just remembers the account number
account_ptr::account_ptr(const string & number)
	: account_number(number)
{}



// Operator -> returns pointer to account object
account * account_ptr::operator->() const
{
	load();
	return target.get();
}


// Operator * returns reference to account object
account & account_ptr::operator*() const
{
	load();
	return *target;
}


// Load account_impl object if-and-when needed
void account_ptr::load() const
{
	if (!target)
		target.reset(bank::instance().create_account(account_number));
}


