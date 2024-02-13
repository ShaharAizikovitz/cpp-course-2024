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

class account_impl;	   // Forward declaration



// Q1 - Define your account_proxy class here, inherited from account 

// Member functions:   
//    Constructor - just remembers the account number
//    deposit()   - deposit money
//    withdraw()  - withdraw money
//    balance()   - return current balance
//    details     - return account details
// Data members:
//    account number (so that account_impl can be created later)
//    unique_ptr to account_impl object



#endif 

