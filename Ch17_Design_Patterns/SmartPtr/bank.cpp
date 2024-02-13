//====================================================================
// File:        bank.cpp
// Description: Implementation of bank class
//====================================================================

#include "bank.hpp"
#include "accimpl.hpp"

using namespace std;

// Provides singleton behaviour - returns single instance of bank class
bank &bank::instance()
{
	static bank the_bank;
	return the_bank;
}

//implementation of private constructor
bank::bank()
{}

// Bind to data source - in a real system, this function might 
// store a file name or SQL query string maybe, so that accounts 
// can be retrieved when needed
void bank::data_source(const ac_data *t, size_t s)
{
	table = t;
	table_size = s;
}


// Search the table, to find the specified account number.
// Create and return a new account implementation object if found
account_impl *bank::create_account(const string &number) const
{
	for (size_t i = 0; i < table_size; i++)
		if (table[i].account_number == number)
			return new account_impl(table[i].account_number,table[i].account_balance);

	
	// If account number not found, create a new account with
	// specified account number
	return new account_impl(number, 0.00);
}


