//====================================================================
// File:        Date_Only.h
// Description: Declaration of DateOnly class
//====================================================================
#pragma once

// most specialised first
#include "Bitfield.h"
#include "Range_Check.h"
#include <utility>
#include <iostream>
#include <chrono>
#include <sstream>
#include <iomanip>

#include "Time_Only.h"

namespace TimesDates {
	using namespace BitFields;
	using namespace std::rel_ops;
	using namespace MyUtility;

	inline constexpr uint16_t getIni(int day, int month, int year) {
		return UBitField<uint16_t, 0, 5>{uint16_t(day), true}.asBase() |
			UBitField<uint16_t, 5, 4>{uint16_t(month), true}.asBase() |
			UBitField<uint16_t, 9, 7>{uint16_t(year), true}.asBase();
	}

	class DateOnly {
	public:
		// Constructors
		constexpr DateOnly() : dateInt{0}{};
		constexpr DateOnly(int day, int month, int year)
					: dateInt(getIni(inRange(day, 1, 31), inRange(month, 1, 12), inRange(year, 0, 127)))
		{}

		// Queries
		std::string print() const;
		int day() const { return int(_day); }
		int month() const { return int(_month); }
		int year() const { return int(_yr); }
		operator bool() const { return asInt() != 0; }
		int asInt() const { return dateInt; }

		bool operator==(const DateOnly & rhs) const {return asInt() == rhs.asInt();}
		bool operator<(const DateOnly & rhs) const {return asInt() < rhs.asInt();}
		bool operator>(const DateOnly & rhs) const {return asInt() > rhs.asInt();}
		// obtain other boolean operators via <utility>

		// Modifiers
		void set_month(int m) {_month = m;}
		void set_day(int day) {_day = day;}
		void set_year(int y) {_yr = y; }

	private:
		union {
				uint16_t dateInt;
				UBitField<uint16_t, 0, 5> _day;
				UBitField<uint16_t, 5, 4> _month;
				UBitField<uint16_t, 9, 7> _yr;
		};
	};

	inline std::string DateOnly::print() const {
		using namespace std;
		stringstream s;
		s << setfill('0') << setw(2);
		s << day() << "/" << setw(2) << month() << "/" << setw(2) << year();
		return s.str();
	}

	inline std::ostream & operator<<(std::ostream & out, const DateOnly & date) {
		return out << date.print();
	}

	inline DateOnly currDate() {
		auto sysTime = std::chrono::system_clock::now();
		time_t time_now = std::chrono::system_clock::to_time_t(sysTime);
		tm *fldTime = std::localtime(&time_now);
		return DateOnly{ fldTime->tm_mday, fldTime->tm_mon+1, fldTime->tm_year-100};
	}

	int weekDayNo(DateOnly date);

}
