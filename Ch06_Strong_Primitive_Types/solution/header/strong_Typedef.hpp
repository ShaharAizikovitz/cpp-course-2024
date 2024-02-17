//====================================================================
// File:        strong_Typedef.hpp
// Description: Declaration of strongTypeDef class
//====================================================================

#pragma once

// Place your templated strongTypeDef class definition here

template <typename T, typename Meaning>
class strongTypeDef {
public:
	strongTypeDef() = default;               // No initialization
	strongTypeDef(T value) : value{ value } {} // Construction from a
											   // fundamental value.
	operator T () const { return value; } 	// Implicit conversion
											// back to fundamental type.  
private:
	T value; 				   // The actual fundamental value.
};

// Place your dummy structs for Length and Area types here
struct Length_T {}; // create dummy types for the template 
struct Area_T {};

// Place your typedefs defining Length and Area alias types here
typedef strongTypeDef<int, Length_T > Length;
typedef strongTypeDef<int, Area_T > Area;

