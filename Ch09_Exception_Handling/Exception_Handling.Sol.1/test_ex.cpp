//====================================================================
// File:        test_ex.hpp
// Description: Test harness for exceptions in array class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "array.hpp"
#include <iostream>
#include <string>
#include <exception>

using namespace std;

//#define TEST_2

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
}

TEST_CASE("Add to Empty Array", "[Exceptions]") {
	cout << "\nAdd to Empty Array Test\n";
	mine::array<string> words; // default zero-size array
	int error{ 0 };
	try {
		words[0] = "Empty";
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Subscript out of range") == 0) error = 1;
		else if (strcmp(err.what(), "index past end of array") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 1);
}

#ifdef TEST_2
TEST_CASE("Add to Resized Array", "[Exceptions]") {
	cout << "\nAdd to Resized Array Test\n";
	mine::array<string> words(2); //  array of max 2 elements
	int error{ 0 };
	try {
		words.resize(2);
		words[0] = "Fred";
		words[1] = "Blogs";
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Subscript out of range") == 0) error = 1;
		else if (strcmp(err.what(), "index past end of array") == 0) error = 2;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}

TEST_CASE("Assign to Negative Index", "[Exceptions]") {
	cout << "\nAssign to Negative Index\n";
	mine::array<string> words(2); //  array of max 2 elements
	int error{ 0 };
	try {
		words.resize(2);
		words[0] = "Fred";
		words[-1] = "Blogs";
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Subscript out of range") == 0) error = 1;
		else if (strcmp(err.what(), "index past end of array") == 0) error = 2;
	}
	catch (domain_error & err) {
		if (strcmp(err.what(), "Negative subscript") == 0) error = 3;
	}
	catch (length_error & err) {
		if (strcmp(err.what(), "attempt to resize above maximum possible") == 0) error = 4;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 3);
}

TEST_CASE("Resize beyond Max", "[Exceptions]") {
	cout << "\nResize beyond Max\n";
	mine::array<string> words(2); //  array of max 2 elements
	int error{ 0 };
	try {
		words.resize(3);
		words[0] = "Fred";
		words[1] = "Blogs";
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Subscript out of range") == 0) error = 1;
		else if (strcmp(err.what(), "index past end of array") == 0) error = 2;
	}
	catch (domain_error & err) {
		if (strcmp(err.what(), "Negative subscript") == 0) error = 3;
	}
	catch (length_error & err) {
		if (strcmp(err.what(), "attempt to resize above maximum possible") == 0) error = 4;
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 4);
}
#endif