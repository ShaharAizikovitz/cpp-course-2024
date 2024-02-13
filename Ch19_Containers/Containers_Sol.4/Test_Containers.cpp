//====================================================================
// File:        Test_Containers.cpp
// Description: Test harness for Scheduler class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Events.h"
#include "Curr_Time.h"
#include "Time_Date.h"
#include "Mock_Clock.h"
#include "Scheduler.h"
#include <iostream>
#include <exception>
#include <memory>

using namespace std;
using namespace TimesDates;

#define test_4

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
}

TEST_CASE("Vector Scheduler", "[Containers]") {
	cout << "\nVector Scheduler Test\n";
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

// #4c Modify the Scheduler declaration to avoid move/copy
		//auto Scheduler = Scheduler{ clock };
		Scheduler scheduler(clock);
		scheduler.stop();
		scheduler.start();

		{
			auto fanMotor = make_shared<Motor>("Extractor Fan");
			auto dataLogger = make_shared<Recorder>("PumpRate Logger");
	
			scheduler.addEvent(make_unique<Event<ISwitchable>>(dataLogger, startTime + 20_mins, &Recorder::stop));
			scheduler.addEvent(make_unique<Event<ISwitchable>>(fanMotor, startTime + 15_mins, &Motor::stop));
			scheduler.addEvent(make_unique<Event<ISwitchable>>(dataLogger, startTime + 10_mins, &Recorder::start));
			scheduler.addEvent(make_unique<Event<ISwitchable>>(fanMotor, startTime + 5_mins, &Motor::start));
		}
#ifndef test_4
		for (int i = 0; i < 25; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			scheduler.check();
		}
#endif
#ifdef test_4
		std::this_thread::sleep_for(std::chrono::seconds(15));
		scheduler.stop();
#endif
		REQUIRE(scheduler.isEmpty());
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