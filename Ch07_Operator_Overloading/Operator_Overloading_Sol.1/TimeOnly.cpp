// most specialised first
#include "TimeOnly.h"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <ctime>

using namespace std;

namespace TimesDates {

	// Queries
	int TimeOnly::mins() const { return _mins % 60; }
	int TimeOnly::hrs() const { return _mins / 60; }
	TimeOnly::operator int() const { return _mins; }
	bool TimeOnly::operator==(const TimeOnly & rhs) const { return _mins == rhs._mins; }
	bool TimeOnly::operator<(const TimeOnly & rhs) const { return _mins < rhs._mins; }
	bool TimeOnly::operator>(const TimeOnly & rhs) const { return _mins > rhs._mins; }
	// obtain other boolean operators via <utility>

	// Modifiers
	TimeOnly & TimeOnly::operator+=(const TimeOnly & rhs) { _mins += rhs._mins; return *this; }
	TimeOnly & TimeOnly::operator-=(const TimeOnly & rhs) { _mins -= rhs._mins; return *this; }


	string TimeOnly::print() const {
		stringstream s;
		s << setfill('0') << setw(2);
		s << _mins / 60 << ":" << setw(2) << _mins % 60;
		return s.str();
	}

	TimeOnly currTime() {
		auto sysTime = std::chrono::system_clock::now();
		time_t time_now = std::chrono::system_clock::to_time_t(sysTime);
		tm *fldTime = std::localtime(&time_now);
		return TimeOnly{ fldTime->tm_hour * 60 + fldTime->tm_min };
	}
}