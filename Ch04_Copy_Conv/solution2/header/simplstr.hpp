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

	simple_string(const simple_string &other);
	simple_string &operator=(const simple_string &other);

	operator const char *() const;
	size_t size() const;

private:
	char *text;
};

bool operator==(const simple_string &lhs, const simple_string &rhs);
bool operator==(const simple_string &lhs, const char *rhs);
bool operator==(const char *lhs,          const simple_string &rhs);

bool operator!=(const simple_string &lhs, const simple_string &rhs);
bool operator!=(const simple_string &lhs, const char *rhs);
bool operator!=(const char *lhs,          const simple_string &rhs);

#endif
