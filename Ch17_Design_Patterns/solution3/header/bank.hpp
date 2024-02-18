//====================================================================
// File:        bank.hpp
// Description: Declaration of bank class, which acts as an 
//              object factory for accounts.
//====================================================================

#ifndef BANK_INCLUDED
#define BANK_INCLUDED

#include <string>
#include <memory>

// Simple data structure - holds data for one account
struct ac_data
{
	char account_number[10];
	double account_balance;
};


// Forward declaration
class account_impl;


// Singleton bank class
class bank
{
public:
    static bank &instance();
	void data_source(const ac_data *table, size_t table_size);
	
	std::unique_ptr<account_impl> create_account(const std::string &num) const;

private:
    const ac_data  *table;
	size_t       table_size;
	bank();				//private constructor
	bank(const bank &); //prevent copying
	bank & operator=(const bank &);
};


#endif 