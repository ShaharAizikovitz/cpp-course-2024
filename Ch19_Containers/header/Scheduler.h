//====================================================================
// File:        Scheduler.h
// Description: Declaration of Scheduler class
//====================================================================

#pragma once
// most specialised first
#include "Curr_Time.h"
#include "Time_Date.h"
#include "Events.h"
#include <queue>
#include <vector>
#include <memory>
#include <functional>
#include <thread>
#include <mutex>

namespace TimesDates {

// 2a Write a sortPtrs_greater Lambda


	class Scheduler {
	public:
		Scheduler(CurrTime & clock);

// #1b Provide addEvent()
		void addEvent();

		void check();
		bool isEmpty();

// #4a add start() and stop() functions launching a thread to call check();

	private:
		CurrTime * _clock;
// #1a Provide a vector member


// #3a Replace vector with priority_queue
	};

}
