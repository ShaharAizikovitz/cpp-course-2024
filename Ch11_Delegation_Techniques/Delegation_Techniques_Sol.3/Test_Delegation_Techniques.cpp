//====================================================================
// File:        Test_Delegation_Techniques.cpp
// Description: Test harness for TimeDate class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Time_Date.h"
#include <iostream>
#include <exception>

using namespace std;
using namespace TimesDates;

#define test_2

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();

// #3 Create an initialised TimeDate object and then call the separate base-class print functions on it.
	const auto myDate = TimeDate{ {12,20},{2,5,15} };
	cout << "Time: " << myDate.TimeMins::print() << " Date: " << myDate.DateOnly::print() << '\n';
}

TEST_CASE("Constructor", "[Delegation_Techniques]") {
	cout << "\nConstructor Test\n";
	int error{ 0 };
	try {
		const auto christmas = TimeDate{ { 13,30 },{25,12,15} };
		cout << "Christmas: " << christmas.print() << '\n';
		REQUIRE(christmas.print() == "13:30 25/12/15");
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}

TEST_CASE("Base Query", "[Delegation_Techniques]") {
	cout << "\nBase Query Test\n";
	int error{ 0 };
	try {
		const auto christmas = TimeDate{ { 13,30 },{ 25,12,15 } };
		const auto xmasDate = DateOnly{ christmas };
		const auto xmasDinnerTime = TimeMins{ christmas };
		cout << "Christmas Day: " << xmasDate.print() << " Christmas Dinner: " << xmasDinnerTime.print() << '\n';
		REQUIRE(xmasDate.print() == "25/12/15");
		REQUIRE(xmasDinnerTime.print() == "13:30");
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}

#ifdef test_2
TEST_CASE("Base Modification", "[Delegation_Techniques]") {
	cout << "\nBase Modification Test\n";
	int error{ 0 };
	try {
		const auto christmas = DateOnly{ 25,12,15 };
		auto dinnerTime = TimeMins{ 13,30 };
		auto christmasDinnerTime = TimeDate{ dinnerTime,christmas };
		christmasDinnerTime.time() = { 15,0 };
		cout << "Christmas Day: " << christmas.print() << " Christmas Dinner: " << christmasDinnerTime.print() << '\n';
		REQUIRE(christmasDinnerTime.print() == "15:00 25/12/15");
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);

}
#endif

TEST_CASE("Comparisons", "[Delegation_Techniques]") {
	cout << "\nComparisons Test\n";
	int error{ 0 };
	try {
		auto now = currTimeDate();
		auto copyNow = now;
		auto future = TimeDate{ { 1,30 },{ 20,2,50 } };
		auto past = TimeDate{ { 1,30 },{ 10,1,2 } };
		cout << "now : " << now << " past: " << past << " future: " << future << '\n';
		REQUIRE(past < now);
		REQUIRE(future > now);
		REQUIRE(copyNow == now);
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}
