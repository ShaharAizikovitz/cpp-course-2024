//====================================================================
// File:        test_Proxy.cpp
// Description: Test harness for Question 2
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "bank.hpp"
#include "accproxy.hpp"
#include <iostream>
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
	account_proxy proxy(acc_num);

	double amount;
	bool running = true;

	while (running)
	{
		cout << "(balance, details, withdraw, deposit, exit): ";
		string response;
		cin >> response;

		if (response == "balance")
			cout << "Balance is currently " << proxy.balance() << endl;
		if (response == "details")
			cout << proxy.details() << endl;
		else if (response == "withdraw")
		{
			cout << "How much? ";
			cin >> amount;

			if (!proxy.withdraw(amount))
				cout << "Sorry, insufficient funds" << endl;
		}
		else if (response == "deposit")
		{
			cout << "How much? ";
			cin >> amount;
			proxy.deposit(amount);
		}
		else if (response == "exit")
			running = false;
	}

	return 0;
}

TEST_CASE("Proxy", "[Design_Patterns]") {
	cout << "\nProxy Test\n";

	const size_t table_size = 12;
	const ac_data table[table_size] =
	{
		{ "1234", 100 },{ "2468", 200 },{ "2357", 300 },{ "1964", 400 },
		{ "0312", 500 },{ "1901", 600 },{ "0207", 700 },{ "2512", 800 },
		{ "2505", 900 },{ "0102", 1000 },{ "1108", 1100 },{ "3101", 1200 }
	};

	// Set the data source for the bank
	bank::instance().data_source(table, table_size);

	account_proxy proxy("1234");

	REQUIRE(proxy.balance() == 100);
	proxy.deposit(125);
	REQUIRE(proxy.balance() == 225);
	proxy.withdraw(25);
	REQUIRE(proxy.balance() == 200);
	proxy.withdraw(300);
	REQUIRE(proxy.balance() == 200);
	proxy.withdraw(30);
	REQUIRE(proxy.balance() == 170);
	cout << proxy.details() << '\n';
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
*	(balance, details, withdraw, deposit, exit): balance
*	Balance is currently 200
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
