//====================================================================
// File:        strong_Typedef.hpp
// Description: Declaration of strongTypeDef class
//====================================================================

#pragma once
// most specialised first
#include "Sum_Operators.h"
#include <utility>	// required by class users to supply operators
#include <string>	// required by class users to supply operators

namespace TimesDates {
	using namespace sum_ops;
	using namespace std::rel_ops;
	
	typedef int period_t;

	class TimeOnly {
	public:
		// Constructors
		TimeOnly() = default;
		constexpr TimeOnly(int hrs, int mins) : _mins{ hrs * 60 + mins } {};
		constexpr explicit TimeOnly(int mins) : _mins{ mins } {};

		// Queries
		std::string print() const;
		period_t mins() const;
		period_t hrs() const;

		explicit operator int() const;
		bool operator==(const TimeOnly &) const;
		bool operator<(const TimeOnly &) const;
		bool operator>(const TimeOnly &) const;
		// other boolean operators via <utility>

		// Modifiers
		TimeOnly & operator+=(const TimeOnly &);
		TimeOnly & operator-=(const TimeOnly &);
		// Other sum operators from templates

	private:
		int _mins = 0;
	};
	// Obtain global binary operators from templates

	TimeOnly currTime();
}