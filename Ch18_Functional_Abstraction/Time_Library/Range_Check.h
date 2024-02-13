#pragma once
#include <exception>
#include <stdexcept>

namespace MyUtility {

	template <typename T1, typename T2, typename T3>
	constexpr T1 inRange(T1 val, T2 min, T3 max) {
		return (val > max) ? throw std::out_of_range("Arg too large") : ((val < min) ? throw std::out_of_range("Arg too small") : val);
	}
}
