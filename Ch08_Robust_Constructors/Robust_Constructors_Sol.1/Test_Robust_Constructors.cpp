//====================================================================
// File:        Test_Strong_Primitive_Types.cpp
// Description: Test harness for strongTypeDef class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "TimeOnly.h"
#include <iostream>
#include <exception>

using namespace std;
using namespace TimesDates;

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
//#6 Define some constexpr TimeMins objects initialising with both in-range and out-of-range values. 
	constexpr auto now = TimeMins{ 500, 0 };
	//constexpr auto future = TimeMins{ 600,0 };
	//constexpr auto past = TimeMins{ -600,0 }
}

TEST_CASE("Args in range", "[Robust Constructors]") {
	cout << "\nArgs in range runtime Test\n";
	int error{ 0 };
	try {
		auto now = currTime();
		auto future = TimeMins{ 500, 0 };
		auto past = TimeMins{ -500, 0 };
		cout << "now : " << now.print() << " past: " << past.print() << " future: " << future.print() << '\n';
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

TEST_CASE("Arg too large", "[Robust Constructors]") {
	cout << "\nArgs too large runtime Test\n";
	int error{ 0 };
	try {
		auto now = currTime();
		auto future = TimeMins{ 600, 0 };
		auto past = TimeMins{ -500, 0 };
		cout << "now : " << now.print() << " past: " << past.print() << " future: " << future.print() << '\n';
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 1);
}

TEST_CASE("Arg too small", "[Robust Constructors]") {
	cout << "\nArgs too small runtime Test\n";
	int error{ 0 };
	try {
		auto now = currTime();
		auto future = TimeMins{ 500, 0 };
		auto past = TimeMins{ -600, 0 };
		cout << "now : " << now.print() << " past: " << past.print() << " future: " << future.print() << '\n';
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 2);
}

TEST_CASE("Using Custom Literals", "[Robust Constructors]") {
	cout << "\nUsing Custom Literals\n";
	//constexpr TimeMins softEgg = TimeMins{ 3 };
	//constexpr TimeMins hardEgg = { 3,0 };
	constexpr TimeMins softEgg = 3_mins;
	constexpr TimeMins hardEgg = 3_hrs;
	REQUIRE(softEgg.mins() == 3);
	REQUIRE(hardEgg.mins() == 0);
	REQUIRE(hardEgg.hrs() == 3);
}
