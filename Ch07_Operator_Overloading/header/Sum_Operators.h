#pragma once

namespace sum_ops {

	template<class C>
	C & operator++ (C & arg) {
		return arg += C(1);
	}


// Define global postfix operator++ here in terms of the prefix operator above


// Define global unary operator- here (negation) in terms of the member operator-=


// Define global prefix	operator-- here in terms of the member operator-=


// Define global postfix operator-- here in terms of the prefix you have just defined 


// Define Global binary operator+ here in terms of the member operator+=


// Define Global binary operator- here in terms of the member operator-=



}