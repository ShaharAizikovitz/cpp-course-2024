//====================================================================
// File:        copyconv.cpp
// Description: Test harness for simple_string class
//====================================================================

#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "simplstr.hpp"
#include <iostream>
using namespace std;

//#define test_2

int main()
{
	Catch::Session session; // There must be exactly once instance
	return session.run();
}

TEST_CASE("CopyConstruct", "[simple_string]") {
	cout << "\nDeep Copy Test\n";
	auto name = simple_string{ "Mississippi" };
	simple_string river{ name };
	auto  state = name;

	cout << river << " River" << endl;
	cout << state << " U. S. of A." << endl;

	REQUIRE(strcmp(river, "Mississippi") == 0);
	REQUIRE(strcmp(state, "Mississippi") == 0);
}

TEST_CASE("CopyAssign", "[simple_string]") {
	cout << "\nDeep Assign Test\n";
	auto name = simple_string{ "Mississippi" };
	auto yummy_dessert = simple_string{};
	yummy_dessert = name;

	cout << yummy_dessert << " Mud Pie" << endl << endl;

	REQUIRE(strcmp(yummy_dessert, "Mississippi") == 0);
}