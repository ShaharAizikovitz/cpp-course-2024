#pragma once
#include <vector>
#include <cstddef>

class SafeVector  : public std::vector<int> {
public:
	using std::vector<int>::vector;
	int & operator[](size_t index) { return this->at(index); }
	const int & operator[](size_t index) const { return this->at(index); }
};
