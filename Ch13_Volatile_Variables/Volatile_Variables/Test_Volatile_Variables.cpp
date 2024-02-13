//====================================================================
// File:        Test_Volatile_Variables.cpp
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

//#define test_2

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
}

TEST_CASE("Memory-Mapped IO", "[Volatile_Variables]") {
	cout << "\nMemory-Mapped IO Test\n";
	int error{ 0 };
	try {
		const volatile auto clockRegister = uint64_t{}; // the mock hardware register
		const volatile auto clockAddr = &clockRegister;

// #2a	Create a local const volatile ClockAsBCD pointer initialised to the hardware address

// #2b	Use placement new to construct a ClockAsBCD object at clockPtr

#ifdef test_2
		setMockClock(clockPtr, currTimeDate());

		CurrTime now(*clockPtr);
		cout << "Now: " << now << '\n';
		REQUIRE(now.print() == currTimeDate().print());

		setMockClock(clockPtr, { {10,30}, { 1,2,15 } });
		now.refreshNow();
		cout << "10:30 01/02/15 : " << now << '\n';
		REQUIRE(now.print() == "10:30 01/02/15");
#endif
	}
	catch (out_of_range & err) {
		if (strcmp(err.what(), "Arg too large") == 0) error = 1;
		else if (strcmp(err.what(), "Arg too small") == 0) error = 2;
	}
	catch (length_error & err) {
		if (strcmp(err.what(), "Only one instance allowed") == 0) error = 3;
	}
	catch (exception & err) {
		cout << err.what();
	}
	catch (...) {
		error = 100;
	}
	REQUIRE(error == 0);
}
