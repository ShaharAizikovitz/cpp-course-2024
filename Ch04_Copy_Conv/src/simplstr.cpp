//====================================================================
// File:        simplstr.cpp
// Description: Implementation of simple_string class
//====================================================================

#include "simplstr.hpp"
#include <cstring>
#include <cstdlib>


// ===================================================================
// Q1, Copying and Conversions practical
// Implement your functions here
// ===================================================================

// Copy constructor ... 


// Assignment operator ...


//   Conversion operator ...




// ===================================================================
// Prewritten functions
// ===================================================================


// Basic constructor
simple_string::simple_string(const char *t)
  : text(new char[strlen(t) + 1])
{
    strcpy(text, t);
}

// Destructor
simple_string::~simple_string()
{
    delete[] text;
}

// Query size of string
size_t simple_string::size() const
{
	return strlen(text);
}
