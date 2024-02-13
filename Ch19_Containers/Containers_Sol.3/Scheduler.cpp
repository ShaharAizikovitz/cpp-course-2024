#include "Scheduler.h"
#include <memory>
#include <algorithm>

using namespace std;

namespace TimesDates {

// #3b  Initialise _schedule with sortPtrs_greater
// #4b	Make the constructor call start().
	Scheduler::Scheduler(CurrTime & clock) : _clock{ &clock }, _schedule(sortPtrs_greater){ }

// #1b Provide addEvent()
	void Scheduler::addEvent(unique_ptr<IEvent> eventPtr) {
		//_schedule.push_back(move(eventPtr));

// 2b Sort the vector on addEvent()
		//sort(_schedule.begin(), _schedule.end(), sortEvents{});

// 3a Modify for priority_queue
		_schedule.push(move(eventPtr));
	}

	void Scheduler::check() {
		_clock->refreshNow();
		cout << "Time is : " << _clock->now() << '\n';

// 3a Modify for priority_queue
		if (!isEmpty()) {
			auto & eventPtr = _schedule.top();
			if (_clock->now() >= TimeDate(*eventPtr)) {
				(*eventPtr)();
				_schedule.pop();
			}
			else {
				cout << "Event not due : " << (*eventPtr).print() << '\n';
			}
		}
	
// 2c pop events that have been executed and stop iterating when it has found an event that is not due
		//for (auto i = _schedule.rbegin(); i < _schedule.rend(); ++i) {
		//	auto & eventPtr = *i;
		//	if (eventPtr) {
		//		if (_clock->now() >= TimeDate(*eventPtr)) {
		//			(*eventPtr)();
		//			eventPtr = nullptr;
		//		}
		//		else {
		//			cout << "Event not due : " << (*eventPtr).print() << '\n';
		//			break;
		//		}
		//	}
		//}
		//while (!_schedule.empty() && _schedule.back() == nullptr)
		//	_schedule.pop_back();
	}

	bool Scheduler::isEmpty() {
// 3a Modify for priority_queue
		return _schedule.empty();
		//for (auto & event : _schedule) {
		//	if (event) return false;
		//}
		//return true;
	}

}