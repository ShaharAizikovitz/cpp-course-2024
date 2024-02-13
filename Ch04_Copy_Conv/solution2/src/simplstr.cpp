//====================================================================
// File:        simplstr.cpp
// Description: Implementation of simple_string class
//====================================================================

#include "simplstr.hpp"
#include <cstring>



// ===================================================================
// Q1, Copying and Conversions practical
// Copy constructor, assignment operator, conversion operator
// ===================================================================


// Copy constructor
simple_string::simple_string(const simple_string &other)
  : text(new char[other.size() + 1])
{
    strcpy(text, other.text);
}

// Assignment operator
simple_string &simple_string::operator=(const simple_string &rhs)
{
    if (this != &rhs)
    {
        delete[] text;
        text = new char[rhs.size() + 1];
        strcpy(text, rhs.text);
    }
    return *this;
}

// Conversion operator
simple_string::operator const char *() const
{
	return text;
}


// ===================================================================
// Q2, Copying and Conversions practical
// Global operators == and !=
// ===================================================================

bool operator==(const simple_string &lhs, const simple_string &rhs)
{
	return strcmp(lhs, rhs) == 0;
}

bool operator== (const simple_string &lhs, const char *rhs)
{
	return strcmp(lhs, rhs) == 0;
}

bool operator== (const char *lhs, const simple_string &rhs)
{
	return strcmp(lhs, rhs) == 0;
}

bool operator!= (const simple_string &lhs, const simple_string &rhs)
{
	return !(lhs == rhs);
}

bool operator!= (const simple_string &lhs, const char *rhs)
{
	return !(lhs == rhs);
}

bool operator!= (const char *lhs, const simple_string &rhs)
{
	return !(lhs == rhs);
}


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
    delete [] text;
}

// Query size of string
size_t simple_string::size() const
{
	return strlen(text);
}