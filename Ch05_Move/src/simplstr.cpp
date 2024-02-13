//====================================================================
// File:        simplstr.cpp
// Description: Implementation of simple_string class
//====================================================================

#include "simplstr.hpp"
#include <cstring>
#include <iostream>
using namespace std;

// ===================================================================
// Q1, Move practical
// Move constructor & assignment operator
// ===================================================================




// ===================================================================
// Prewritten functions
// ===================================================================

simple_string simple_string::clone() const {
	cout << "RVO\n";
	return *this;
}

simple_string simple_string::rv_clone() const {
	cout << "rv_clone\n";
	auto temp = *this;
	return temp;
}

// Basic constructor
simple_string::simple_string(const char *t)
	: text(new char[strlen(t) + 1])
{
	strcpy(text, t);
	cout << "Char * C : " << text << '\n';
}

// Copy constructor
simple_string::simple_string(const simple_string &other)
	: text(new char[other.size() + 1])
{
	strcpy(text, other.text);
	cout << "Deep C : " << text << '\n';
}

// Assignment operator
simple_string &simple_string::operator=(const simple_string &rhs)
{
	char * temp = text;
	text = new char[rhs.size() + 1];
	strcpy(text, rhs.text);
	delete[] temp;
	cout << "Deep = : " << text << '\n';
	return *this;
}

// Conversion operator
simple_string::operator const char *() const
{
	return text;
}

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