#pragma once
#include <type_traits>
#include <iostream>
#include <cstddef>

namespace BitFields {

	template< typename IntType, int start, int bits >
	void SetBitMask(IntType & base, int val) {
		constexpr IntType mask = (1u << bits) - 1u;
		base = (base & ~(mask << start)) | ((val & mask) << start);
	}

	template< typename IntType, int start, int bits >
	int GetBitMask(IntType base) {
		constexpr IntType mask = (1u << bits) - 1u;
		return (base >> start) & mask;
	}

// #3 Create a templated UBitField class utilising the algorithms above in member functions
//The function template arguments will become the class template arguments.
//	�	Which member function maps to the set operation ?
//	�	Which member function maps to the get operation ?
//	�	What data members does the class require ?
//	�	Where should the constexpr mask be placed ?
//  �	Write a constexpr constructor


	template <typename IntType, int start, int bits = 1>
	class UBitField {
// #4 Write a series of static asserts to check
		//  �	start is greater or equal to zero.
		//	�	bits is greater than zero.
		//	�	The base - type is large enough for start + bits.
		//	�	The base - type is an unsigned integer type.

		static_assert(start >= 0, "start must be >= 0");
		static_assert(bits > 0, "bits must be > 0");
		static_assert((1 << (start + bits)) -1 <= std::numeric_limits<IntType>::max(), "Integer type too small");
		static_assert(std::is_integral< IntType >::value && std::is_unsigned< IntType >::value, "IntType must be an unsigned integer type");

	public:
		constexpr UBitField() = default;
		constexpr UBitField(IntType val) : base( (base & ~(mask << start)) | ((val & mask) << start) ) {}
		constexpr UBitField(IntType val, bool zeroed) : base(IntType{0} | ((val & mask) << start)) {}
		
		// Queries
		constexpr operator IntType() const {
			return (base >> start) & mask;
		}
		constexpr IntType asBase() const {
			return base;
		}

		// Modifiers
		UBitField & operator=(IntType val) {
			base = (base & ~(mask << start)) | ((val & mask) << start);
			return *this;
		}

	protected:
		constexpr static IntType mask = (1u << bits) - 1u;
		IntType base;  // must not initialise because only one member of a union is allowed to be initialised
	};

}
