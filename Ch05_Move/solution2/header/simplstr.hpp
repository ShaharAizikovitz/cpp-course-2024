//====================================================================
// File:        simplstr.hpp
// Description: Declaration of simple_string class
//====================================================================

#ifndef SIMPLE_STRING_INCLUDED
#define SIMPLE_STRING_INCLUDED
#include <cstddef>
#include <utility>

class simple_string
{
public:	
	simple_string(const char *t = "");

	virtual ~simple_string();

	// Deep Copy Functions
	simple_string(const simple_string & other);
	simple_string &operator=(const simple_string & other);

	// Move Functions
	simple_string(simple_string && other) noexcept;
	simple_string &operator=(simple_string && other) noexcept;

	simple_string clone() const;
	simple_string rv_clone() const;

	operator const char *() const;
	size_t size() const;

private:
	char *text;
};

// Add make_simple_string here
template<typename T>
simple_string make_simple_string(T && arg) {
	return (std::forward<T>(arg));
}

bool operator==(const simple_string &lhs, const simple_string &rhs);
bool operator==(const simple_string &lhs, const char *rhs);
bool operator==(const char *lhs,          const simple_string &rhs);

bool operator!=(const simple_string &lhs, const simple_string &rhs);
bool operator!=(const simple_string &lhs, const char *rhs);
bool operator!=(const char *lhs,          const simple_string &rhs);

#endif
