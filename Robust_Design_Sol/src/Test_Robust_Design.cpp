#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "CleanHeader.h"
#include "Widget.h"
#include <iostream>
using namespace std;


int main(int argc, char* argv[])
{
	Catch::Session session; // There must be exactly once instance
	Foo f;

	Widget w;
	cout << w.print();

	return session.run();
}

TEST_CASE("Print()", "[Widget]") {
	Widget w;
	REQUIRE(w.print() == "0 : 1 : 2 : 3 : 4 : 5 : 6 : 7 : 8 : 9 : ");
}
