//====================================================================
// File:        array.hpp
// Description: Declaration of array template class
//====================================================================

#ifndef ARRAY_INCLUDED
#define ARRAY_INCLUDED

#include <cstddef>
#include <algorithm>
#include <exception>
#include <stdexcept>

// array class definition
namespace mine {
	template<class type>
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
		type &subscript(size_t) const;
		type *body;    // actual array elements
		size_t length; // number of actual array elements
	};

	// definition of array member functions

	template<class type>
	array<type>::array()
		: body(0), length(0)
	{
	}

	template<class type>
	array<type>::array(const array &other)
		: body(0), length(other.length)
	{
		body = new type[length];

		for (size_t current = 0; current < length; ++current)
			body[current] = other.body[current];
	}

	template<class type>
	array<type>::~array()
	{
		delete[] body;
	}

	template<class type>
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

	template<class type>
	type &array<type>::operator[](size_t index)
	{
		if (index >= size())
		{
			std::out_of_range out("Subscript out of range");
			throw out;
		}
		return subscript(index);
	}

	template<class type>
	const type &array<type>::operator[](size_t index) const
	{
		if (index >= size())
		{
			std::out_of_range out("Subscript out of range");
			throw out;
		}

		return subscript(index);
	}

	template<class type>
	bool array<type>::empty() const
	{
		return length == 0;
	}

	template<class type>
	size_t array<type>::size() const
	{
		return length;
	}

	template<class type>
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

	template<class type>
	type &array<type>::subscript(size_t index) const
	{
		if (index >= length)
			throw std::out_of_range("index past end of array");

		return body[index];
	}
}
#endif // header already included
