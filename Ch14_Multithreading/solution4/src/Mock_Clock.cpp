#include "Mock_Clock.h"
#include <chrono>
#include <ctime>
#include <iostream>
#include <thread>
#include <future>
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

namespace TimesDates {
	// static definitions
	bool MockClock::_instantiated = false;

// #2 Implement the constructor to launch a thread calling tick().
	MockClock::MockClock(const volatile ClockAsBCD & clock, int refreshPeriod, int rate)
		: clock{ &const_cast<ClockAsBCD &>(clock) },
		refreshPeriod{ inRange(refreshPeriod,1,std::numeric_limits<int>::max()) },
		rate{ inRange(rate,1,refreshPeriod * 1000)},
		t{ std::thread(&MockClock::tick, this) }
	{
		_instantiated = _instantiated ? throw std::length_error("Only one instance allowed") : true;
		updateClock();
		cout << "MockClock Started" << crlf;
	}

	void  MockClock::tick() {
// #1a Create a std::chrono::duration variable of length "refreshPeriod * 1000 / rate" in milliseconds
		auto sleep = std::chrono::milliseconds(refreshPeriod * 1000 / rate);

// #1b Create a loop that exits when _stop is true and then prints a message to the console.
		while (!_stop) {
// #1c Inside the loop call updateClock() and sleep the thread for the period you created in #1a
			std::this_thread::sleep_for(sleep);
			updateClock();
		}
		std::cout << "clock stopped" << crlf;
	}

	void MockClock::stop() { 
// #3 implement stop() ensuring that the thread has terminated.
		_stop = true; 
		t.join(); 
	}

	MockClock::~MockClock() { 
		if (!_stop) stop();
		_instantiated = false;
		cout << "MockClock Destructed" << crlf;
	}

	void MockClock::addHr() {
		acceleratedTime += 3600;
	}

	void MockClock::updateClock() {
		if (acceleratedTime == 0) {
			auto now = std::chrono::system_clock::now();
			// convert to calendar time
			auto n_tt = std::chrono::system_clock::to_time_t(now);
			acceleratedTime = n_tt; 
		}
// #4c  Protect with an exclusive lock. A lock_guard is a suitable choice
		lock_guard<shared_timed_mutex> write_lock(clock_mutex);
		acceleratedTime += refreshPeriod;
		auto fieldTime = localtime(&acceleratedTime);
		// load the BCD bitfield
		clock->_year = toBCD(fieldTime->tm_year - 100); // tm_year counts from 1900
		clock->_month = toBCD(fieldTime->tm_mon + 1); // tm_mon counts from 0
		clock->_day = toBCD(fieldTime->tm_mday);
		clock->_hr = toBCD(fieldTime->tm_hour);
		clock->_min = toBCD(fieldTime->tm_min);
	}

	char getKey() {
		char c = _getch();
		return c;
	}

	void ShowHours(CurrTime & clock, MockClock & mockClock) {

// #5a Launch getKey() asynchronously to wait for keyboard input. Use std::async.
		cout << "\n\nPress h to jump forward one hour. Any other key quits.\n" << crlf;

// #5c Initialise "again" to true
		bool again = false;
		TimeDate hr = clock.refreshNow();

		do { // Keep updating and printing the time, stop when a character is entered.
			clock.refreshNow();
			if (hr.hrs() != clock.time().hrs()) {
				cout << clock.now() << crlf;
				hr = clock.now();
			}

// #5b Wait for the result from getKey() for 1ms and if a result is available check its value.  

		} while (again);
		mockClock.stop();
	}
}
