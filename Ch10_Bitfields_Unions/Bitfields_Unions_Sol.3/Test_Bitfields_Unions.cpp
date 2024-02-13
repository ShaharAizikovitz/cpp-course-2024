//====================================================================
// File:        Test_Bitfields_Unions.cpp
// Description: Test harness for Bitfields class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Date_Only.h"
#include <iostream>
#include <exception>

using namespace std;
using namespace TimesDates;

//#define test_5

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
	constexpr DateOnly christmas{ 25,12,16 };
	constexpr DateOnly noDate{}; // test default constructor
	constexpr DateOnly anotherChristmas{ christmas }; // test synthesised copy constructor
#ifdef test_5
	UBitField<uint16_t, -1, 5> t1;
	UBitField<uint16_t, 1, 16> t2;
	UBitField<uint16_t, 0, 0> t3;
	UBitField<int16_t, 0, 5> t4;
	UBitField<float, 0, 5> t5;
#endif
}

TEST_CASE("Comparison", "[Bitfields_Unions]") {
	cout << "\nComparison Test\n";
	int error{ 0 };
	try {
		auto now = currDate();
		auto copyNow = now;
		auto future = DateOnly{ 20,2,50 };
		auto past = DateOnly{ 10,1,2 };
		const auto christmas = DateOnly{ 25,12,15 };
		cout << "now : " << now << " past: " << past << " future: " << future << '\n';
		REQUIRE(christmas.print() == "25/12/15");
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

TEST_CASE("Modify", "[Bitfields_Unions]") {
	cout << "\nModify Test\n";
	int error{ 0 };
	try {
		auto now = currDate();
		const auto christmas = DateOnly{ 25,12,14 };
		now = christmas;
		cout << "now : " << now << " christmas: " << christmas << '\n';
		REQUIRE(now == christmas);
		now.set_year(12);
		cout << now.print() << '\n';
		REQUIRE(now == DateOnly(25, 12, 12));
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

TEST_CASE("Args Out Of Range", "[Bitfields_Unions]") {
	cout << "\nArgs Out Of Range runtime Test\n";
	int error{ 0 };
	try {
		auto past = DateOnly{ 0,1,2 };
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too small") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too large") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 1);
	
	try {
		auto past = DateOnly{ 5,13,2 };
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too small") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too large") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 2);
}
