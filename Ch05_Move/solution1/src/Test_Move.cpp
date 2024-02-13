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
	string close;
	std::cin >> close;
}

TEST_CASE("CopyConstruct", "[simple_string]") {
	cout << "\nDeep Copy Test\n";
	auto name = simple_string{ "Mississippi" };
	simple_string river{ name };
	auto  state = name;

	REQUIRE(river == "Mississippi");
	REQUIRE(state == "Mississippi");
}

TEST_CASE("CopyAssign", "[simple_string]") {
	cout << "\nDeep Assign Test\n";
	auto name = simple_string{ "Mississippi" };
	auto yummy_dessert = simple_string{};
	yummy_dessert = name;

	REQUIRE(yummy_dessert == "Mississippi");
}

TEST_CASE("MoveConstruct", "[simple_string]") {
	cout << "\nMove Construct Test\n";
	auto name = simple_string("Mississippi");
	auto river = name.clone();
	auto longRiver = name.rv_clone();
	REQUIRE(river == "Mississippi");
}

TEST_CASE("MoveAssign", "[simple_string]") {
	cout << "\nMove Assign Test\n";
	auto yummy_dessert = simple_string{};
	yummy_dessert = simple_string{ "Mississippi" };

	REQUIRE(yummy_dessert == "Mississippi");
}

#ifdef test_2
TEST_CASE("From char*", "[Factory]") {
	cout << "\nFactory from Char*\n";
	auto yummy_dessert = make_simple_string("Mississippi");

	REQUIRE(yummy_dessert == "Mississippi");
}

TEST_CASE("From L_Value", "[Factory]") {
	cout << "\nFactory from L-Value\n";
	auto name = simple_string{ "Mississippi" };
	auto yummy_dessert = make_simple_string(name);

	REQUIRE(yummy_dessert == "Mississippi");
}

TEST_CASE("From R_Value", "[Factory]") {
	cout << "\nFactory from R-Value\n";
	auto name = simple_string{ "Mississippi" };
	auto yummy_dessert = make_simple_string(name.rv_clone());

	REQUIRE(yummy_dessert == "Mississippi");
}

TEST_CASE("Assign From R_Value", "[Factory]") {
	cout << "\nFactory Assign from R-Value\n";
	auto name = simple_string{ "Mississippi" };
	auto yummy_dessert = simple_string{};
	yummy_dessert = make_simple_string(name);

	REQUIRE(yummy_dessert == "Mississippi");
}
#endif