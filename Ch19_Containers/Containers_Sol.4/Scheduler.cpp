#include "Scheduler.h"
#include <memory>
#include <algorithm>

using namespace std;

namespace TimesDates {

// #3b  Initialise _schedule with sortPtrs_greater
// #4b	Make the constructor call start().
	Scheduler::Scheduler(CurrTime & clock) : _clock{ &clock }, _schedule(sortPtrs_greater) { start(); }

// #1b Provide addEvent()
	void Scheduler::addEvent(unique_ptr<IEvent> eventPtr) {
		//_schedule.push_back(move(eventPtr));

// 2b Sort the vector on addEvent()
		//sort(_schedule.begin(), _schedule.end(), sortEvents{});

// 3a Modify for priority_queue
		lock_guard<mutex> l(m);
		_schedule.push(move(eventPtr));
	}

	void Scheduler::check() {
		while (!_stop) {
			_clock->refreshNow();
			//cout << "Time is : " << _clock->now() << '\n';
			lock_guard<mutex> l(m);

// 3a Modify for priority_queue
			if (!isEmpty()) {
				auto & eventPtr = _schedule.top();
				if (_clock->now() >= TimeDate(*eventPtr)) {
					cout << _clock->now() << '\n';
					(*eventPtr)();
					_schedule.pop();
				}
				else {
					//cout << "Event not due : " << (*eventPtr).print() << '\n';
				}
			}
			std::this_thread::yield();
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

	void Scheduler::start() {
		if (_stop) {
			_stop = false;
			t = std::thread(&Scheduler::check, this);
		}
	}

	void Scheduler::stop() {
		if (!_stop) {
			_stop = true;
			t.join();
		}
	}

}