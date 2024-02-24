#include "stdafx.h" 
#include "Date_Only.h"

namespace TimesDates {

	int weekDayNo(DateOnly date) {
		int yy = date.year() + 2000;
		int day = date.day();
		if (date.month() < 3) {
			date.set_month(date.month() + 12);
			--yy;
		}

		return (--day + (2 * date.month()) 
			+ (6 * (date.month() + 1) / 10)
			+ yy + (yy / 4) - (yy / 100)
			+ (yy / 400) + 1) % 7;
	}
}