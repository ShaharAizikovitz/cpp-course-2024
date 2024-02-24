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
#include <memory>

using namespace std;
using namespace TimesDates;

#define test_2
#define test_4

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
}

#if !defined test_2
TEST_CASE("Event Functors", "[Functional_Abstraction]") {
	cout << "\nEvent Functors Test\n";
	int error{ 0 };
	try {
		const volatile auto clockRegister = uint64_t{}; // the mock hardware register
		const volatile auto clockAddr = &clockRegister;

		const volatile auto clockPtr = reinterpret_cast<const volatile ClockAsBCD *>(clockAddr);

		new(const_cast<ClockAsBCD *>(clockPtr)) ClockAsBCD();

		auto sysTime = currTimeDate().print();

		MockClock mockClock(*clockPtr, 10, 120); // increment two minutes every second.
		CurrTime clock(*clockPtr);
		auto startTime = TimeDate{ clock.now() };

		IEvent * eventQueue[4];
		{
			auto fanMotor = make_shared<Motor>("Extractor Fan");
			auto pumpMotor = make_shared<Motor>("Borehole Pump");
			auto dataLogger = make_shared<Recorder>("PumpRate Logger");
			auto doctorWho = make_shared<Recorder>("TV Prog");

			eventQueue[0] = new StartMotor{ fanMotor, startTime + 5_mins };
			eventQueue[1] = new StartRecording{ dataLogger, startTime + 10_mins };
			eventQueue[2] = new StopMotor{ fanMotor, startTime + 15_mins };
			eventQueue[3] = new StopRecording{ dataLogger, startTime + 20_mins };
		}

		for (int i = 0; i < 25; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			cout << "One minute later " << clock.refreshNow() << '\n';
			for (auto & action : eventQueue) {
				if (action) {
					if (clock.now() == *action) {
						// #1b Amend the test to call the functor instead of go().
						//action->go();
						(*action)();
						cout << '\n' << action->print() << "\n\n";
						delete action;
						action = nullptr;
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
#endif
#if defined test_2 && !defined test_4

TEST_CASE("Member Functors", "[Functional_Abstraction]") {
	cout << "\nMember Functors Test\n";
	int error{ 0 };
	try {
		const volatile auto clockRegister = uint64_t{}; // the mock hardware register
		const volatile auto clockAddr = &clockRegister;

		const volatile auto clockPtr = reinterpret_cast<const volatile ClockAsBCD *>(clockAddr);

		new(const_cast<ClockAsBCD *>(clockPtr)) ClockAsBCD();

		auto sysTime = currTimeDate().print();

		MockClock mockClock(*clockPtr, 10, 120); // increment two minutes every second.
		CurrTime clock(*clockPtr);
		auto startTime = TimeDate{ clock.now() };

		IEvent * eventQueue[4];
		{
			auto fanMotor = make_shared<Motor>("Extractor Fan");
			auto pumpMotor = make_shared<Motor>("Borehole Pump");
			auto dataLogger = make_shared<Recorder>("PumpRate Logger");
			auto doctorWho = make_shared<Recorder>("TV Prog");

// #2b Modify the test to work with this new functor.
			//eventQueue[0] = new StartMotor{ fanMotor, startTime + 5_mins };
			//eventQueue[1] = new StartRecording{ dataLogger, startTime + 10_mins };
			//eventQueue[2] = new StopMotor{ fanMotor, startTime + 15_mins };
			//eventQueue[3] = new StopRecording{ dataLogger, startTime + 20_mins };
			eventQueue[0] = new Event{ fanMotor, startTime + 5_mins, &Motor::start };
			eventQueue[1] = new Event{ dataLogger, startTime + 10_mins,&Recorder::start };
			eventQueue[2] = new Event{ fanMotor, startTime + 15_mins, &Motor::stop };
			eventQueue[3] = new Event{ dataLogger, startTime + 20_mins,&Recorder::stop };
		}

		for (int i = 0; i < 25; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			cout << "One minute later " << clock.refreshNow() << '\n';
			for (auto & action : eventQueue) {
				if (action) {
					if (clock.now() == *action) {
						// #1b Amend the test to call the functor instead of go().
						//action->go();
						(*action)();
						cout << '\n' << action->print() << "\n\n";
						delete action;
						action = nullptr;
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
#endif
#ifdef test_4
TEST_CASE("Templated Functor", "[Functional_Abstraction]") {
	cout << "\nTemplated Functor Test\n";
	int error{ 0 };
	try {
		const volatile auto clockRegister = uint64_t{}; // the mock hardware register
		const volatile auto clockAddr = &clockRegister;

		const volatile auto clockPtr = reinterpret_cast<const volatile ClockAsBCD *>(clockAddr);

		new(const_cast<ClockAsBCD *>(clockPtr)) ClockAsBCD();

		auto sysTime = currTimeDate().print();

		MockClock mockClock(*clockPtr, 10, 120); // increment two minutes every second.
		CurrTime clock(*clockPtr);
		auto startTime = TimeDate{ clock.now() };

		IEvent * eventQueue[4];
		{
			auto fanMotor = make_shared<Motor>("Extractor Fan");
			auto pumpMotor = make_shared<Motor>("Borehole Pump");
			auto dataLogger = make_shared<Recorder>("PumpRate Logger");
			auto doctorWho = make_shared<Recorder>("TV Prog");

// #4b Modify the test to work with the templated functor.
			//eventQueue[0] = new StartMotor{ fanMotor, startTime + 5_mins };
			//eventQueue[1] = new StartRecording{ dataLogger, startTime + 10_mins };
			//eventQueue[2] = new StopMotor{ fanMotor, startTime + 15_mins };
			//eventQueue[3] = new StopRecording{ dataLogger, startTime + 20_mins };
			eventQueue[0] = new Event<ISwitchable>{ fanMotor, startTime + 5_mins, &Motor::start };
			eventQueue[1] = new Event<ISwitchable>{ dataLogger, startTime + 10_mins,&Recorder::start };
			eventQueue[2] = new Event<ISwitchable>{ fanMotor, startTime + 15_mins, &Motor::stop };
			eventQueue[3] = new Event<ISwitchable>{ dataLogger, startTime + 20_mins,&Recorder::stop };
		}

		for (int i = 0; i < 25; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			cout << "One minute later " << clock.refreshNow() << '\n';
			for (auto & action : eventQueue) {
				if (action) {
					if (clock.now() == *action) {
						// #1b Amend the test to call the functor instead of go().
						//action->go();
						(*action)();
						cout << '\n' << action->print() << "\n\n";
						delete action;
						action = nullptr;
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
#endif