//====================================================================
// File:        array.hpp
// Description: Definition of array template class
//====================================================================

#ifndef ARRAY_INCLUDED
#define ARRAY_INCLUDED

#include <cstddef>
#include <algorithm>

// array class definition
namespace mine {
	template<typename type>
	class array
	{
	public:

		array();
		array(const array &);
		~array();

		array &operator=(const array &);

		type &operator[](size_t);
		const type &operator[](size_t) const;

		bool empty() const;
		size_t size() const;
		void resize(size_t new_size);

	private:
		type *body;   // actual array elements
		size_t length; // number of actual array elements

	};

	// definition of array member functions

	template<typename type>
	array<type>::array()
		: body(0), length(0)
	{
	}

	template<typename type>
	array<type>::array(const array &other)
		: body(0), length(other.length)
	{
		body = new type[length];

		for (size_t current = 0; current < length; ++current)
			body[current] = other.body[current];
	}

	template<typename type>
	array<type>::~array()
	{
		delete[] body;
	}

	template<typename type>
	array<type> &array<type>::operator=(const array &rhs)
	{
		if (this != &rhs)
		{
			type *new_body = new type[rhs.length];

			for (size_t current = 0; current < rhs.length; ++current)
				new_body[current] = rhs.body[current];

			delete[] body;
			body = new_body;
			length = rhs.length;
		}

		return *this;
	}

	template<typename type>
	type &array<type>::operator[](size_t index)
	{
		return body[index];
	}

	template<typename type>
	const type &array<type>::operator[](size_t index) const
	{
		return body[index];
	}

	template<typename type>
	bool array<type>::empty() const
	{
		return length == 0;
	}

	template<typename type>
	size_t array<type>::size() const
	{
		return length;
	}

	template<typename type>
	void array<type>::resize(size_t new_size)
	{
		if (length != new_size)
		{
			type *new_body = new type[new_size];
			size_t copy = std::min(length, new_size);

			for (size_t current = 0; current < copy; ++current)
				new_body[current] = body[current];

			delete[] body;
			body = new_body;
			length = new_size;
		}
	}
}

#endif 
