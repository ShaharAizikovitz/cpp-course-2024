#include "Scheduler.h"
#include <memory>
#include <algorithm>

using namespace std;

namespace TimesDates {

// #3b  Initialise _schedule with sortPtrs_greater
// #4b	Make the constructor call start().
	Scheduler::Scheduler(CurrTime & clock) : _clock{ &clock } { }

// #1b Provide addEvent()
	void Scheduler::addEvent() {

// 2b Sort the vector on addEvent()

// 3a Modify for priority_queue

	}

	void Scheduler::check() {
		_clock->refreshNow();
		cout << "Time is : " << _clock->now() << '\n';

// 3a Modify for priority_queue
	
// 2c pop events that have been executed and stop iterating when it has found an event that is not due
		for (auto & eventPtr : _schedule) {
			if (eventPtr) {
				if (_clock->now() >= TimeDate(*eventPtr)) {
					(*eventPtr)();
					eventPtr = nullptr;
				} else {
					cout << "Event not due : " << (*eventPtr).print() << '\n';
				}
			}
		}
	}

	bool Scheduler::isEmpty() {
// 3a Modify for priority_queue
		for (auto & event : _schedule) {
			if (event) return false;
		}
		return true;
	}

}