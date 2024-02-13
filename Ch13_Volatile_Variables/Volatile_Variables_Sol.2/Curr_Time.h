//====================================================================
// File:        Curr_Time.h
// Description: Declaration of Curr_Time class
//====================================================================
#pragma once
// most specialised first
#include "Time_Date.h"
#include "Date_Only.h"
#include "Time_Only.h"
#include <stdexcept>

namespace TimesDates {

	int adjustForDST(const TimeDate & now);

	union ClockAsBCD;

/// <summary>
/// Maintains clock-time. now(), date() and time() return the most recently aquired time.
///	To refresh the time from the sourse, call refreshNow() 
///	which returns the most up-to-date time available.
/// DST is applied automatically when appropriate.
/// </summary>

	class CurrTime {
	public:
// #1b Initialise the ClockAsBCD member in the constructor
		CurrTime(const volatile ClockAsBCD & clock) : _clock(&clock) {
			if (_instantiated) throw std::length_error("Only one instance allowed");
			_instantiated = true;
			refreshNow();
		}

		// Queries
		std::string print() const { return now().print(); }
		TimeDate now() const { return _now; }
		DateOnly date() const { return now().date(); }
		TimeMins time() const { return now().time(); }
		operator TimeDate() const { return now(); }

		TimeDate refreshNow();
		void checkDST();

		~CurrTime() { _instantiated = false; }
	private:
		TimeDate _now;
// #1a Add an associated ClockAsBCD member 
		const volatile ClockAsBCD * _clock;
		static bool _instantiated;
	};

	union ClockAsBCD {
		UBitField<uint64_t, 0, 8> _min;
		UBitField<uint64_t, 8, 8> _hr;
		UBitField<uint64_t, 16, 8> _day;
		UBitField<uint64_t, 24, 8> _month;
		UBitField<uint64_t, 32, 8> _year;
	};

	void setMockClock(const volatile ClockAsBCD * clock, TimeDate time);

}