//====================================================================
// File:        accimpl.cpp
// Description: Implementation of account_impl class, 
//              which contains the implementation of a bank account.
//====================================================================

#include "accimpl.hpp"
#include <sstream>
#include <iomanip>

using namespace std;

account_impl::account_impl(const string &n, double opening_balance)
	: number(n),
	current_balance(opening_balance),
	deposits(0),
	withdrawals(0)
{}

void account_impl::deposit(double amount)
{
	current_balance += amount;
	deposits++;
}

bool account_impl::withdraw(double amount)
{
	bool result = false;

	if (current_balance >= amount)
	{
		current_balance -= amount;
		withdrawals++;
		result = true;
	}

	return result;
}

double account_impl::balance() const
{
	return current_balance;
}

string account_impl::details() const
{
	using namespace std;
	stringstream s;
	s << setw(13) << left << "Account no:" << setw(10) << right << number << '\n';
	s << setw(13) << left << "Balance:" << setw(10) << right << current_balance << '\n';
	s << setw(13) << left << "Deposits:" << setw(10) << right << deposits << '\n';
	s << setw(13) << left << "Withdrawals:" << setw(10) << right << withdrawals;
	return s.str();
}
