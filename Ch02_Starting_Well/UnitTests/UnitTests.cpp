// UnitTests.cpp : Defines the entry point for the console application.
//

#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include <catch.hpp>
#include "Factorial.h"
#include "SafeVector.h"

TEST_CASE("Factorials are computed", "[factorial]") {
	REQUIRE(Factorial(1) == 1);
	REQUIRE(Factorial(2) == 2);
	REQUIRE(Factorial(3) == 6);
	REQUIRE(Factorial(10) == 3628800);
}

TEST_CASE("Factorial 0", "[factorial]") {
	REQUIRE(Factorial(0) == 1);
}

TEST_CASE("Array Tested","[Array]") {
	int myArr[] = { 1, 2, 3 };
	REQUIRE(myArr[1] == 2);
}

TEST_CASE("SafeVector In bounds", "[SafeVector]") {
	auto saveVect = SafeVector{ 4, 5, 6 };
	REQUIRE(saveVect[1] == 5);
}

TEST_CASE("SafeVector Out of bounds", "[SafeVector]") {
	auto saveVect = SafeVector{ 4, 5, 6 };
	REQUIRE(saveVect[4] != 4);
}