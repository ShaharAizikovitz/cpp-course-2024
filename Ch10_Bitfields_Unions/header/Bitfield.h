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

	
// #4 Write a series of static asserts to check
//  �	start is greater or equal to zero.
//	�	bits is greater than zero.
//	�	The base - type is large enough for start + bits.
//	�	The base - type is an unsigned integer type.

// *********** Place your templated class definition here *****************



}
