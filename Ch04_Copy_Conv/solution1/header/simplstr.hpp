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
	simple_string(const char *t =  "");
	virtual ~simple_string();

	simple_string(const simple_string &other);// copy CTOR
	simple_string &operator=(const simple_string &other);//assignment operator

	operator const char *() const;// conversion operator
	size_t size() const;

protected:
	char *text;
};

#endif
