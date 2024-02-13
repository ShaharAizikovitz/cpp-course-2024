//====================================================================
// File:        bank.hpp
// Description: Declaration of bank class, which acts as an 
//              object factory for accounts.
//====================================================================

#ifndef BANK_INCLUDED
#define BANK_INCLUDED

#include <string>

struct ac_data			// Simple data structure - account data
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
    // The instance() function 
    static bank &instance();

	// Prewritten functions
	void data_source(const ac_data *table, size_t table_size);
	account_impl *create_account(const std::string &num) const;
private:
    const ac_data  *table;
	size_t       table_size;
	bank();				//private constructor
	bank(const bank &);	//disallow copying of the singleton
	bank &operator=(const bank &);
};


#endif 