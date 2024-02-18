//====================================================================
// File:        accproxy.hpp
// Description: Declaration of account_ptr and account_proxy classes, 
//              which acts as a proxies for account_impl 
//====================================================================

#ifndef ACCOUNT_PROXY_INCLUDED
#define ACCOUNT_PROXY_INCLUDED

#include "account.hpp"
#include "accimpl.hpp"
#include <memory>
#include <string>

// Forward declaration
class account_impl;


// Smart pointer class
class account_ptr
{
public:
	// Constructor - just remembers the account number
	account_ptr(const std::string & number);

	// Operator -> returns pointer to account object
	account * operator->() const;

	// Operator * returns reference to account object
	account & operator*() const;

private:
	// Load account_impl object if-and-when needed
	void load() const;
	
	// Initialised from constructor argument
	std::string account_number;

	// Target account_imp object, null initially
	mutable std::unique_ptr<account_impl> target;
};

#endif 

