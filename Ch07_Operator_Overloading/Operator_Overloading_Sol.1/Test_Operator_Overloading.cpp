//====================================================================
// File:        Test_Operator_Overloading.cpp
// Description: Test harness for TimeOnly class
//====================================================================
#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
// most specialised first
#include "TimeOnly.h"
#include <iostream>
using namespace std;
using namespace TimesDates;

int main()
{
	Catch::Session session; // There must be exactly once instance
	session.run();
	return 0;
}

TEST_CASE("Member_Rel_Ops", "[Operators]") {
	cout << "\nMember Relative Operators Test\n";

	auto now = currTime();
	auto was = now - TimeOnly{ 5 };
	auto then = now + TimeOnly{ 5 };
	auto soon = then;
	cout << "now : " << now.print() << " was: " << was.print() << " then: " << then.print() << '\n';
	REQUIRE(now < then);
	REQUIRE(then > was);
	REQUIRE(soon == then);
}

TEST_CASE("Utility_Rel_Ops", "[Operators]") {
	cout << "\nUtility Relative Operators Test\n";

	auto now = currTime();
	auto was = now - TimeOnly{ 5 };
	auto then = now + TimeOnly{ 5 };
	auto soon = then;
	cout << "now : " << now.print() << " was: " << was.print() << " then: " << then.print() << '\n';
	
	REQUIRE(now <= then);
	REQUIRE(then >= was);
	REQUIRE(soon != now);

	REQUIRE(now == currTime());
	REQUIRE(then >= TimeOnly{ was });
	REQUIRE(soon != now);

}

TEST_CASE("Sum_Ops", "[Operators]") {
	cout << "\nSum Operators Test\n";
	auto teaTime = TimeOnly{18,30};
	constexpr auto boilEgg = TimeOnly{ 4 };
	constexpr auto pourBeer = TimeOnly{ 2 };
	auto eggInPan = teaTime - boilEgg;
	auto ready = eggInPan + boilEgg + pourBeer;
	cout << " teaTime: " << teaTime.print() << " eggInPan : " << eggInPan.print() << " ready: " << ready.print() << '\n';
	
	REQUIRE(teaTime.hrs() == 18);
	REQUIRE(teaTime.mins() == 30);
	REQUIRE(eggInPan.mins() == 26);
	REQUIRE(ready.mins() == 32);
}