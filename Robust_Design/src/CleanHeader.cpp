#include "CleanHeader.h"
#include "Widget.h"
#include "DoDar.h"



Widget Foo::fnA() { return Widget{}; } 
void Foo::FnB(Widget) {};			
DoDar Foo::FnC(Widget &) { return DoDar{}; };