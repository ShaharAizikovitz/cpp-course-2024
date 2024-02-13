//====================================================================
// File:        Test_Statics_Globals.cpp
// Description: Test harness for CurrTime class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Curr_Time.h"
#include "Time_Date.h"
#include <iostream>
#include <exception>

using namespace std;
using namespace TimesDates;

#define test_3
//#define test_4

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
}

TEST_CASE("Constructor", "[Statics_Globals]") {
	cout << "\nConstructor Test\n";
	int error{ 0 };
	try {
		CurrTime_t now = CurrTime();
		now.refreshNow();
		cout << now << '\n';
		REQUIRE(now.print() == currTimeDate().print());
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (length_error & err) {
		if (strcmp(err.what(), "Only one instance allowed") == 0) error = 3;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}

TEST_CASE("CurrTime Delete and Recreate", "[Statics_Globals]") {
	cout << "\nCurrTime Delete and Recreate Test\n";
	int error{ 0 };
	try {
		{auto now = CurrTime().refreshNow(); }
		CurrTime_t now = CurrTime();
		cout << "Sucessful!\n";
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (length_error & err) {
		if (strcmp(err.what(), "Only one instance allowed") == 0) error = 3;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}

#ifndef test_3
TEST_CASE("adjustForDST Hidden dependency", "[Statics_Globals]") {
	cout << "\nadjustForDST Hidden dependency Test\n";
	cout << "\n************* This test should fail for part 1 ***************\n\n";
	int error{ 0 };
	try {
		CurrTime_t now = CurrTime();
		now.setClock(TimeMins{ 1,0 }, DateOnly{ 29,3,15 });
		int dstAdjustment = adjustForDST();
		cout << now << " DST: " << dstAdjustment << '\n';
		REQUIRE(dstAdjustment == 1);
		now.setClock(TimeMins{ 2,0 }, DateOnly{ 25,10,15 });
		dstAdjustment = adjustForDST();
		cout << now << " DST: " << dstAdjustment << '\n';
		REQUIRE(dstAdjustment == -1);
		now.setClock(TimeMins{ 1,0 }, DateOnly{ 25,10,15 });
		dstAdjustment = adjustForDST();
		cout << now << " DST: " << dstAdjustment << '\n';
		REQUIRE(dstAdjustment == 0);
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (length_error & err) {
		if (strcmp(err.what(), "Only one instance allowed") == 0) error = 3;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}

#else

TEST_CASE("adjustForDST Injected dependency", "[Statics_Globals]") {
	cout << "\nadjustForDST Injected dependency Test\n";
	int error{ 0 };
	try {
		CurrTime_t now = CurrTime();
		auto testDate = TimeDate{ { 1,0 },{ 29,3,15 } };
		int dstAdjustment = adjustForDST(testDate);
		cout << testDate << " DST: " << dstAdjustment << '\n';
		REQUIRE(dstAdjustment == 1);
		testDate = TimeDate{ { 2,0 },{ 25,10,15 } };
		dstAdjustment = adjustForDST(testDate);
		cout << testDate << " DST: " << dstAdjustment << '\n';
		REQUIRE(dstAdjustment == -1);
		testDate = TimeDate{ { 1,0 },{ 25,10,15 } };
		dstAdjustment = adjustForDST(testDate);
		cout << testDate << " DST: " << dstAdjustment << '\n';
		REQUIRE(dstAdjustment == 0);
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (length_error & err) {
		if (strcmp(err.what(), "Only one instance allowed") == 0) error = 3;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}

TEST_CASE("CurrTime adjustForDST", "[Statics_Globals]") {
	cout << "\nCurrTime adjustForDST Test\n";
	int error{ 0 };
	try {
		CurrTime_t now = CurrTime();
		now.setClock(TimeMins{ 1,0 }, DateOnly{ 29,3,15 });
		cout << now << '\n';
		REQUIRE(now.print() == "01:00 29/03/15");
		now.checkDST();
		cout << now << '\n';
		REQUIRE(now.print() == "02:00 29/03/15");
		now.setClock(TimeMins{ 2,0 }, DateOnly{ 20,10,15 });
		now.checkDST();
		now.setClock(TimeMins{ 2,0 }, DateOnly{ 25,10,15 });
		cout << now << '\n';
		REQUIRE(now.print() == "02:00 25/10/15");
		now.checkDST();
		cout << now << '\n';
		REQUIRE(now.print() == "01:00 25/10/15");
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (length_error & err) {
		if (strcmp(err.what(), "Only one instance allowed") == 0) error = 3;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}

#endif

TEST_CASE("Singleton", "[Statics_Globals]") {
	cout << "\nSingleton Test\n";
	int error{ 0 };
	try {
		CurrTime_t now = CurrTime();
		now.refreshNow();
		cout << now << '\n';
		{
			CurrTime_t another = CurrTime();
			another.setClock(TimeMins{ 10,30 }, DateOnly{ 16,5,15 });
			cout << another << '\n';
		}
		cout << now << '\n';
		REQUIRE(now.print() == "10:30 16/05/15");
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (length_error & err) {
		if (strcmp(err.what(), "Only one instance allowed") == 0) error = 3;
	}
	catch (...) {
		error = 100;
	}

#if defined test_3 && !defined test_4
	REQUIRE(error == 3); // for tests 3
#else
	REQUIRE(error == 0); // for tests 1,2,4
#endif
}
