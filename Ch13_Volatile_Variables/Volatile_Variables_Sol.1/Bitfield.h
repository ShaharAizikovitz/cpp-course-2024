//====================================================================
// File:        BitField.h
// Description: Declaration of UBitField class
//====================================================================
#pragma once
#include <type_traits>
#include <iostream>
#include <cstddef>
#include <limits>
#include <cstdint>

namespace BitFields {

	template <size_t Width>
	struct SmallestType {
		typedef
			typename std::conditional<Width == 0, void,
			typename std::conditional<Width <= 8, uint8_t,
			typename std::conditional<Width <= 16, uint16_t,
			typename std::conditional<Width <= 32, uint32_t,
			typename std::conditional<Width <= 64, uint64_t,
			void>::type>::type>::type>::type>::type type;
	};

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

	template <typename IntType, int start, int bits = 1>
	class UBitField {
		static_assert(start >= 0, "start must be >= 0");
		static_assert(bits > 0, "bits must be > 0");
		static_assert((1LL << (start + bits)) - 1 <= std::numeric_limits<IntType>::max(), "Integer type too small");
		static_assert(std::is_integral< IntType >::value && std::is_unsigned< IntType >::value, "IntType must be an unsigned integer type");

	public:
		constexpr UBitField() = default;
		constexpr UBitField(IntType val) : base((base & ~(mask << start)) | ((val & mask) << start)) {}
		constexpr UBitField(IntType val, bool zeroed) : base(IntType{0} | ((val & mask) << start)) {}

		// Queries
		typedef typename SmallestType<bits>::type RT;
		constexpr operator RT() const {
			return (base >> start) & mask;
		}
		constexpr IntType asBase() const {
			return base;
		}

// #1c Copy the outward conversion operator adding volatile to its qualifiers 
		operator RT() const volatile {
			return (base >> start) & mask;
		}

		// Modifiers
		UBitField & operator=(IntType val) {
			base = (base & ~(mask << start)) | ((val & mask) << start);
			return *this;
		}

	protected:
		enum :IntType { mask = (1u << bits) - 1u };
		IntType base; // must not initialise because only one member of a union is allowed to be initialised
	};

	/// <summary>
	/// Converts from binary to a two-digit BCD representation  
	/// </summary>
	/// <param name="value">An 8-bit binary number 0-99.</param>
	/// <returns></returns>
	inline uint8_t toBCD(uint8_t value) {
		return ((value / 10) << 4) + (value % 10);
	}

	/// <summary>
	/// Converts from a two-digit BCD representation to binary
	/// </summary>
	/// <param name="value">A two-digit BCD value</param>
	/// <returns></returns>
	inline uint8_t fromBCD(uint8_t value) {
		uint8_t decoded = value & 127;
		return (decoded & 15) + 10 * ((decoded & (15 << 4)) >> 4);
	}

}
