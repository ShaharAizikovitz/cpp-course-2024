//====================================================================
// File:        Test_Polymorphism.cpp
// Description: Test harness for CurrTime class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Events.h"
#include "Curr_Time.h"
#include "Time_Date.h"
#include "Mock_Clock.h"
#include <iostream>
#include <exception>

using namespace std;
using namespace TimesDates;

#define test_1

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
}

TEST_CASE("Polymorphism", "[Polymorphism]") {
	cout << "\nPolymorphism Test\n";
	int error{ 0 };
	try {
		const volatile auto clockRegister = uint64_t{}; // the mock hardware register
		const volatile auto clockAddr = &clockRegister;

		const volatile auto clockPtr = reinterpret_cast<const volatile ClockAsBCD *>(clockAddr);

		new(const_cast<ClockAsBCD *>(clockPtr)) ClockAsBCD();

		auto sysTime = currTimeDate().print();

		MockClock mockClock(*clockPtr, 10, 120); // increment two minute every second.
		CurrTime clock(*clockPtr);
		auto startTime = TimeDate{clock.now()};

		IEvent * eventQueue[4];
		eventQueue[0] = new StartMotor{ startTime + 5_mins};
		eventQueue[1] = new StartRecording{ startTime + 10_mins };
		eventQueue[2] = new StopMotor{ startTime + 15_mins};
		eventQueue[3] = new StopRecording{ startTime + 20_mins };
			
		for (int i = 0; i < 25; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			cout << "One minute later " << clock.refreshNow() << '\n';
// #2 Change the for-loop to a range-for
			for (int i = 0; i < sizeof(eventQueue) / sizeof(IEvent *); ++i) {
				IEvent * action = eventQueue[i];
				if (action) {
					if (clock.now() == *action) {
						action->go();
						cout << '\n' << action->print() << "\n\n";
						delete action;
						eventQueue[i] = nullptr;
					}
				}
			}
		}

		REQUIRE(eventQueue[0] == nullptr);
		REQUIRE(eventQueue[1] == nullptr);
		REQUIRE(eventQueue[2] == nullptr);
		REQUIRE(eventQueue[3] == nullptr);
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

