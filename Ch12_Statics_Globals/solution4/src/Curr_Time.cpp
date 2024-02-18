#include "Curr_Time.h"
#include <iostream>


namespace TimesDates {
	// static definitions
//	TimeDate CurrTime::_now{};
//	bool CurrTimeSingleton::_instantiated = false;

// #4 Provide a definition for the new CurrTime() function
	CurrTimeSingleton & CurrTime() {
		static CurrTimeSingleton singleton;
		TimeDate debug = singleton;
		return singleton;
	}


	/// <summary>
	/// Checks if the argument is the date/time at which DST is adjusted.
	/// If it is, it returns the hour offset required.
	/// </summary>
	/// <param name="now">Current TimeDate</param>
	/// <returns></returns>
// #3 Modify adjustForDST() to take a TimeDate object representing now as an argument	
//	int adjustForDST() {
	int adjustForDST(const TimeDate & now) {
//		auto now = CurrTime().now();
		int returnVal = 0;
		if (now.month() == 3 || now.month() == 10) { // Mar/Oct
			if (now.day() > 24) { // last week
				if (weekDayNo(now) == 6) {
					if (now.month() == 3 && now.hrs() == 1) {
						returnVal = 1;
					}
					else if (now.month() == 10 && now.hrs() == 2) {
						returnVal = -1;
					}
				}
			}
		}
		return returnVal;
	}

	void CurrTimeSingleton::setClock(const TimeMins & time) {
		_now.time() = time;
	}

	void CurrTimeSingleton::setClock(const DateOnly & date) {
		_now.date() = date;
	}

	void CurrTimeSingleton::setClock(const TimeMins & time, const DateOnly & date) {
		setClock(time);
		setClock(date);
	}

	/// <summary>
	/// Updates CurrTime from the clock and returns the current time.
	/// </summary>
	/// <returns></returns>
	TimeDate CurrTimeSingleton::refreshNow() {
		_now = currTimeDate();
		checkDST();
		return _now;
	}

	/// <summary>
	/// Adjusts the CurrTime for DST if required
	/// </summary>
	void CurrTimeSingleton::checkDST() {
		static bool dstHasBeenSet = false;
// #3 Pass the TimeDate held by CurrTime to adjustForDST as an argument	
//		auto addHour = adjustForDST();
		auto addHour = adjustForDST(now());
		if (addHour && !dstHasBeenSet) {
			dstHasBeenSet = true;
			this->_now.time() += {addHour, 0};
		} 
		if (this->date().day() < 24 && dstHasBeenSet) {
			dstHasBeenSet = false; // clear
		}
	}

}
