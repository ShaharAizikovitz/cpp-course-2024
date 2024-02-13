#pragma once

#include "Time_Date.h"
#include "Bitfield.h"
#include "Curr_Time.h"
#include <thread>

namespace TimesDates {
	/// <summary>
	/// This class constantly updates a mock hardware address, clock, using a separate thread.
	/// "refreshPeriod" is the number of seconds between updates and "rate" is the 
	/// speed of the clock relative to real time. Thus "rate=2" makes the clock run at double real-time.
	/// When the MockClock is constructed, it sets the time to system-time. 
	/// </summary>
	class MockClock
	{
	public:
		MockClock(const volatile ClockAsBCD & clock, int refreshPeriod = 15, int rate = 1);
		void stop();
		void addHr();
		~MockClock();
	private:
		void tick();
		void updateClock();

		volatile ClockAsBCD * clock;
		int refreshPeriod;
		int rate;
		volatile bool _stop;
		time_t acceleratedTime; // ctime in seconds since Unix Time.
		std::thread t;
		static bool _instantiated;
	};

	void ShowHours(CurrTime & clock, MockClock & mockClock);

}
