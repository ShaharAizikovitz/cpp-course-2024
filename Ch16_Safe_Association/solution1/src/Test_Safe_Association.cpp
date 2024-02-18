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

//#define test_2
//#define test_3

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
}

TEST_CASE("Switchable Objects", "[Safe_Association]") {
	cout << "\nSwitchable Objects Test\n";
	auto fanMotor = Motor("Extractor Fan");
	auto pumpMotor = Motor("Borehole Pump");
	auto dataLogger = Recorder("PumpRate Logger");
	auto doctorWho = Recorder("TV Prog");

	cout << fanMotor.print() << '\n';
	cout << pumpMotor.print() << '\n';
	cout << dataLogger.print() << '\n';
	cout << doctorWho.print() << '\n';

	REQUIRE(fanMotor.print() == "Motor Extractor Fan OFF");
	REQUIRE(pumpMotor.print() == "Motor Borehole Pump OFF");
	REQUIRE(dataLogger.print() == "Recorder PumpRate Logger OFF");
	REQUIRE(doctorWho.print() == "Recorder TV Prog OFF");
}

#if defined test_2 && !defined test_3
TEST_CASE("Association_Without_Custody", "[Safe_Association]") {
	cout << "\nAssociation_Without_Custody Test\n";
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
		auto fanMotor = Motor("Extractor Fan");
		auto pumpMotor = Motor("Borehole Pump");
		auto dataLogger = Recorder("PumpRate Logger");
		auto doctorWho = Recorder("TV Prog");

		eventQueue[0] = new StartMotor{ &fanMotor, startTime + 5_mins };
		eventQueue[1] = new StartRecording{ &dataLogger, startTime + 10_mins };
		eventQueue[2] = new StopMotor{ &fanMotor, startTime + 15_mins };
		eventQueue[3] = new StopRecording{ &dataLogger, startTime + 20_mins };

		for (int i = 0; i < 25; ++i) {
			std::this_thread::sleep_for(std::chrono::milliseconds(500));
			cout << "One minute later " << clock.refreshNow() << '\n';
			for (auto & event : eventQueue) {
				if (event) {
					if (clock.now() == *event) {
						event->go();
						cout << '\n' << event->print() << "\n\n";
						delete event;
						event = nullptr;
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
#ifdef test_3
TEST_CASE("Safe_Association", "[Safe_Association]") {
	cout << "\nSafe_Association Test\n";
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
// #3d Allocate the ISwitchable objects to shared_ptrs, using make_shared.
			//auto fanMotor = new Motor("Extractor Fan");
			//auto pumpMotor = new Motor("Borehole Pump");
			//auto dataLogger = new Recorder("PumpRate Logger");
			//auto doctorWho = new Recorder("TV Prog");
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
			for (auto & event : eventQueue) {
				if (event) {
					if (clock.now() == *event) {
						event->go();
						cout << '\n' << event->print() << "\n\n";
						// if (there are no more events) delete event->switchable(); 
						delete event;
						event = nullptr;
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
