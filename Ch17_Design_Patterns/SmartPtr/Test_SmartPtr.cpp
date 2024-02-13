//====================================================================
// File:        test3.cpp
// Description: Test harness for Question 3
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include <iostream>
#include "bank.hpp"
#include "accproxy.hpp"

#include <string>
using namespace std;

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();

	// Sample data, from which account_impl objects will be created
	const size_t table_size = 12;
	const ac_data table[table_size] =
	{
		{ "1234", 100 },{ "2468", 200 },{ "2357", 300 },{ "1964", 400 },
		{ "0312", 500 },{ "1901", 600 },{ "0207", 700 },{ "2512", 800 },
		{ "2505", 900 },{ "0102", 1000 },{ "1108", 1100 },{ "3101", 1200 }
	};


	// Set the data source for the bank
	bank::instance().data_source(table, table_size);


	// Create  proxy object
	string acc_num;
	cout << "\nYou may interact with the bank if you wish. Otherwise close the console window.\n\n";
	cout << "Please enter account number ";
	cin >> acc_num;
	account_ptr acc(acc_num);

	double amount;
	bool running = true;

	while (running)
	{
		cout << "(balance, details, withdraw, deposit, exit): ";
		string response;
		cin >> response;

		if (response == "balance")
			cout << "Balance is currently " << acc->balance() << endl;
		if (response == "details")
			cout << acc->details() << endl;
		else if (response == "withdraw")
		{
			cout << "How much? ";
			cin >> amount;

			if (!acc->withdraw(amount))
				cout << "Sorry, insufficient funds" << endl;
		}
		else if (response == "deposit")
		{
			cout << "How much? ";
			cin >> amount;
			acc->deposit(amount);
		}
		else if (response == "exit")
			running = false;
	}

	return 0;
}

TEST_CASE("Smart Pointer", "[Design_Patterns]") {
	cout << "\nSmart Pointer Test\n";

	const size_t table_size = 12;
	const ac_data table[table_size] =
	{
		{ "1234", 100 },{ "2468", 200 },{ "2357", 300 },{ "1964", 400 },
		{ "0312", 500 },{ "1901", 600 },{ "0207", 700 },{ "2512", 800 },
		{ "2505", 900 },{ "0102", 1000 },{ "1108", 1100 },{ "3101", 1200 }
	};

	// Set the data source for the bank
	bank::instance().data_source(table, table_size);

	account_ptr acc("1234");

	REQUIRE(acc->balance() == 100);
	acc->deposit(125);
	REQUIRE(acc->balance() == 225);
	acc->withdraw(25);
	REQUIRE(acc->balance() == 200);
	acc->withdraw(300);
	REQUIRE(acc->balance() == 200);
	acc->withdraw(30);
	REQUIRE(acc->balance() == 170);
	cout << acc->details() << '\n';
}

/*
*	Sample execution...
*
*	Please enter account number 1234
*	(balance, details, withdraw, deposit, exit): details
*	Account no:  1234
*	Balance:     100.000000
*	Deposits:    0
*	Withdrawals: 0
*
*	(balance, details, withdraw, deposit, exit): deposit
*	How much? 100
*	(balance, details, withdraw, deposit, exit): withdraw
*	How much? 50
*	(balance, details, withdraw, deposit, exit): details
*	Account no:  1234
*	Balance:     150.000000
*	Deposits:    1
*	Withdrawals: 1
*
*	(balance, details, withdraw, deposit, exit): exit
*
*/