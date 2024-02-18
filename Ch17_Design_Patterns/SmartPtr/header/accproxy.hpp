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


// Smart pointer class account_ptr should implement the following methods...

// Operator -> returns pointer to account object

// Operator * returns reference to account object

#endif 

