#pragma once

namespace sum_ops {

	template<class C>
	C & operator++ (C & arg) {
		return arg += C(1);
	}

	template<class C>
	const C operator++ (C & arg, int) {
		const C original = arg;
		++arg;
		return original;
	}

	template<class C>
	C operator- (const C & arg) {
		return C(0) -= arg;
	}

	template<class C>
	C & operator-- (C & arg) {
		return arg -= C(1);
	}

	template<class C>
	const C operator-- (C & arg, int) {
		const C original = arg;
		--arg;
		return original;
	}

	// Global binary operators
	template<class C>
	C operator+(const C & lhs, const C & rhs) { C result = lhs; return result += rhs; }

	template<class C>
	C operator-(const C & lhs, const C & rhs) { C result = lhs; return result -= rhs; }

}
