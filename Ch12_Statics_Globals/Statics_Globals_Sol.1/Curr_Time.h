//====================================================================
// File:        Curr_Time.h
// Description: Declaration of Curr_Time class
//====================================================================
#pragma once
// most specialised first
#include "Date_Only.h"
#include "Time_Only.h"
#include "Time_Date.h"
#include <stdexcept>

namespace TimesDates {
	class CurrTime;
	using CurrTime_t = CurrTime;

// #3 Modify adjustForDST() to take a TimeDate object representing now as an argument	
	int adjustForDST();

// #4 Create a prototype for a free function called CurrTime that returns a CurrTimeSingleton reference



// #1 Modify the class to delegate to a TimeDate object
// Should we use private inheritance or composition?

/// <summary>
/// Maintains clock-time. now(), date() and time() return the most recently acquired time.
///	To refresh the time from the source, call refreshNow()
///	which returns the most up-to-date time available.
/// DST is applied automatically when appropriate.
/// </summary>

// #4 Rename the current time class as CurrTimeSingleton
	class CurrTime {
	public:
// #3 Cause the constructor to throw a std::length_error if a second instance is attempted.
// #4 Make the constructor private.
		CurrTime() {}
		
// #4 Define the copy and assignment functions as =delete.
// #4 Make the new CurrTime() function a friend 

		// Queries
		std::string print() const { return now().print(); }
		TimeDate now() const { return _now; }
		DateOnly date() const { return now().date(); }
		TimeMins time() const { return now().time(); }
		operator TimeDate() const { return now(); }

		// Modifiers
		void setClock(const TimeMins & time);
		void setClock(const DateOnly & date);
		void setClock(const TimeMins & time, const DateOnly & date);

		TimeDate refreshNow();

		void checkDST();

	private:
// #2 Make TimeDate a static member.
		TimeDate _now;

// #3 add a static bool instantiated member.

	};
}

