#pragma once
#include "Widget.h"
#include "DoDar.h"
#include <string>
#include <array>

class Foo  
	: public DoDar // #1
{		
public:
	Widget fnA(); // #2
	void FnB(Widget);			// #3
	DoDar FnC(Widget &);			// #4
private:
	std::array<Widget,5> arrayWidget; // #5
	Widget widget;					// #6
	Widget * widgetPtr;				// #7
	std::string * strPtr;			// #8
};
