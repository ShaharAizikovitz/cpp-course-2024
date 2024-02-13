//====================================================================
// File:        simplstr.hpp
// Description: Declaration of simple_string class
//====================================================================

#ifndef SIMPLE_STRING_INCLUDED
#define SIMPLE_STRING_INCLUDED
#include <cstddef>

class simple_string
{
public:	
	// Predefined functions
	simple_string(const char *t =  "");
	virtual ~simple_string();
	size_t size() const;

	// Declare your functions here:
	//   Copy constructor ...

	//   Assignment operator ...
	

	//   Conversion operator ...

private:
	char *text;
};

// Global operators here


#endif
