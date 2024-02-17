//====================================================================
// File:        Test_Strong_Primitive_Types.cpp
// Description: Test harness for strongTypeDef class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "strong_Typedef.hpp"
#include <iostream>
using namespace std;

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
	return 0;
}

Area area(Length w, Length h) { return w*h; }

TEST_CASE("strongTypeDef", "[strongTypeDef]") {
	cout << "\nstrongTypeDef Test\n";

	auto len = Length{ 2 };			// create variables of distinct int types.
	auto width = Length{ 5 };   
	auto a1 = Area{};

	a1 = area(len, width);
	REQUIRE (a1 == 10);
}

TEST_CASE("Wrong Arg Type", "[strongTypeDef]") {
	cout << "\nWrong Arg Type Test\n";

	auto len = Length{ 2 };
	auto width = Length{ 5 };   // create variables of distinct int types.
	auto a1 = Area{};
	auto a2 = Area{};

	a1 = area(a1, width);	
	a1 = area(6, width);	// can be called with int

	a2 = len + 6 + a1; 	    // however, can freely mix different types!!
	REQUIRE(a1 == 30);
	REQUIRE(a2 == 38);
}

