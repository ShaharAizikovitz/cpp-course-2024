//====================================================================
// File:        Test_Multithreading.cpp
// Description: Test harness for CurrTime class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Curr_Time.h"
#include "Time_Date.h"
#include "Mock_Clock.h"
#include <iostream>
#include <exception>
#include <string>

using namespace std;

#ifdef _WIN32
	#include <conio.h>
	const auto crlf = string {"\n"};
# else
	#include <ncurses.h>
	#define _getch getch
	const auto crlf = string {"\n\r"};
#endif

using namespace TimesDates;

#define test_1

int main()
{
#ifndef _WIN32
	initscr();
	timeout(1); // call getch() without blocking to initialise terminal
	getch();
	timeout(-1); // make getch() wait for input
	nl();
	refresh();
#endif
	Catch::Session session; // There must be exactly once instance
	session.run();
	cout << crlf << "********* If a test fails, try re-running it *************" << crlf;
#ifndef _WIN32
	addstr("\n\r Esc to quit");
	refresh();
	while (27 != getch()){};
	endwin();
#endif
}

TEST_CASE("Mock Clock", "[Multithreading]") {
	cout << crlf << "Mock Clock Test" << crlf;
	int error{ 0 };
	try {
		const volatile auto clockRegister = uint64_t{}; // the mock hardware register
		const volatile auto clockAddr = &clockRegister;

		const volatile auto clockPtr = reinterpret_cast<const volatile ClockAsBCD *>(clockAddr);

		new(const_cast<ClockAsBCD *>(clockPtr)) ClockAsBCD();

		auto sysTime = currTimeDate().print();

		MockClock mockClock(*clockPtr, 10, 60); // increment one minute every second.
		CurrTime clock(*clockPtr);

		cout << "Now: " << clock << '\n' << crlf;
		cout << "********* If this test fails, try re-running it *************" << crlf;
		REQUIRE(clock.print() == sysTime);

		auto fastTime = clock.now();
#ifdef test_1
		for (int i = 0; i < 5; ++i) {
			std::this_thread::sleep_for(std::chrono::seconds(1));
			cout << "One minute later " << clock.refreshNow() << crlf;
		}
		fastTime.time() += 5_mins;
		cout << "\nNow " << clock << " should equal FastTime: " << fastTime << crlf;
		REQUIRE(clock.now() == fastTime);
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

TEST_CASE("Monitor Keyboard", "[Multithreading]") {
	cout << "\nMonitor Keyboard Test\n\r";
	int error{ 0 };
	try {
		const volatile auto clockRegister = uint64_t{}; // the mock hardware register
		const volatile auto clockAddr = &clockRegister;

		const volatile auto clockPtr = reinterpret_cast<const volatile ClockAsBCD *>(clockAddr);

		new(const_cast<ClockAsBCD *>(clockPtr)) ClockAsBCD();

		MockClock mockClock(*clockPtr, 600, 1800); // increment one hour every 2 seconds.

		CurrTime clock(*clockPtr);
		ShowHours(clock, mockClock);
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

