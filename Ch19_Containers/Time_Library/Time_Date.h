//====================================================================
// File:        Time_Date.h
// Description: Declaration of TimeDate class
//====================================================================

#pragma once
// most specialised first
#include "Date_Only.h"
#include "Time_Only.h"
#include "Sum_Operators.h"
#include <utility>
#include <ostream>

namespace TimesDates {
	using namespace std::rel_ops;
	using namespace sum_ops;

	class TimeDate : public TimeMins, public DateOnly
	{
	public:
		// Constructors
		constexpr TimeDate() = default;
		constexpr TimeDate(TimeMins time, DateOnly date) : TimeMins(time), DateOnly(date) {}

		// Queries
		std::string print() const { return TimeMins::print() + " " + DateOnly::print(); }

		int_least32_t asInt() const { return (DateOnly::asInt() << 16) | TimeMins::asInt(); };
		operator bool() const { return TimeMins::operator bool() | DateOnly::operator bool(); }

		bool operator==(const TimeDate & rhs) const { return asInt() == rhs.asInt(); }
		bool operator<(const TimeDate & rhs) const { return asInt() < rhs.asInt(); }
		bool operator>(const TimeDate & rhs) const { return asInt() > rhs.asInt(); }
		// obtain other boolean operators via <utility>

		// Modifiers
		DateOnly & date() { return *this; }
		TimeMins & time() { return *this; }
	};

	inline TimeDate operator+(const TimeDate & lhs, const TimeMins & rhs) {
		TimeDate result = lhs;
		result += rhs;
		return result;
	}

	inline std::ostream & operator<<(std::ostream & out, const TimeDate & timeDate) {
		return out << timeDate.print();
	}

	inline TimeDate currTimeDate() {
		auto sysTime = std::chrono::system_clock::now();
		time_t time_now = std::chrono::system_clock::to_time_t(sysTime);
		tm *fldTime = std::localtime(&time_now);
		return { TimeMins{ fldTime->tm_hour * 60 + fldTime->tm_min }, { fldTime->tm_mday, fldTime->tm_mon + 1, fldTime->tm_year - 100 } };
	}
}