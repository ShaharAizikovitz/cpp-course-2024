//====================================================================
// File:        TimeOnly.h
// Description: Declaration of TimeOnly class and its literal opeartors
//====================================================================

#pragma once
// most specialised first
#include "Sum_Operators.h"
#include "Range_Check.h"
#include <chrono>
#include <sstream>
#include <iomanip>
#include <utility>	// required by class users to supply operators
#include <string>	// required by class users to supply operators

namespace TimesDates {
	using namespace std::rel_ops;
	using namespace sum_ops;
	using namespace MyUtility;


// #1 Template this class on the integer type to be used for the data member
	class TimeOnly {
	public:
		// Constructors
		TimeOnly() = default;
// #5 Modify the constructor to call the range-checking function
		constexpr TimeOnly(int hrs, int mins) : _mins{ hrs * 60 + mins } {}


// #4 Modify the constructor to delegate to the two argument constructor
// Sadly, this is not supported for constexp constructors in VS 2015
		constexpr explicit TimeOnly(int mins) : _mins(mins) {};	


// #5 Modify the constructor to call the range-checking function

		
		// Queries
		std::string print() const;
		int mins() const { return _mins % 60; }
		int hrs() const { return _mins / 60; };

		explicit operator int() const { return _mins; }
		bool operator==(const TimeOnly & rhs) const { return _mins == rhs._mins; }
		bool operator<(const TimeOnly & rhs) const { return _mins < rhs._mins; }
		operator bool() const { return _mins != 0; }
		// obtain other boolean operators via <utility>

		// Modifiers
		TimeOnly & operator+=(const TimeOnly & rhs) { _mins += rhs._mins; return *this; }
		TimeOnly & operator-=(const TimeOnly & rhs) { _mins -= rhs._mins; return *this; }
		// Obtain other sum operators from templates
	private:
		int _mins = 0;
	};

// #2 Modify the declaration of this function to be a member of the newly templated class
	std::string TimeOnly::print() const {
		std::stringstream s;
		s << std::setfill('0') << std::setw(2);
		s << _mins / 60 << ":" << std::setw(2) << _mins % 60;
		return s.str();
	}

// #3 Insert type aliases here for TimeMins based on int_least16_t and TimeSecs based on int_least32_t 


	inline TimeMins currTime() {
		auto sysTime = std::chrono::system_clock::now();
		time_t time_now = std::chrono::system_clock::to_time_t(sysTime);
		tm *fldTime = std::localtime(&time_now);
		return TimeMins{ fldTime->tm_hour * 60 + fldTime->tm_min };
	}

	namespace Literals {
// #7 Insert Custom Literal operators for _mins and _hrs here


	}
	using namespace Literals;
}
