//====================================================================
// File:        Action.h
// Description: Declaration of IAction and derived classes
//====================================================================
#pragma once
#include "Time_Date.h"
#include <iostream>

namespace TimesDates {

// #1a Define the IAction interface class providing the go() function
	class IAction {
	public:
		virtual void go() = 0;
		virtual ~IAction() {}
	protected:
		IAction() {}
// #3a Declare a protected pure virtual name() function returning string " at "
		virtual std::string name() = 0;
	};
	inline std::string IAction::name() { return " at "; }

// #1b Define the IEvent abstract class combining IAction and TimeDate
	class IEvent : public IAction, public TimeDate {
	public:
// #3d Implement a non-virtual print() function delegating to concrete name(), base name() and timeStr()
		std::string print() { return name() + IAction::name() + timeStr(); }
	protected:
		IEvent(TimeDate time) : TimeDate(time) {}
	private:
// #3b Override the name() function as private pure
		std::string name() override = 0;
// #3c Implement a private non-virtual timeStr() function
		std::string timeStr() { return TimeDate::print(); }
	};
	
// #1c Define the StartMotor concrete event class initialising the TimeDate
	class StartMotor : public IEvent {
	public:
		StartMotor(TimeDate time) : IEvent{ time } {}
// #3e Move the contents of go() to name() returning a string.
		void go() override {}
	private:
		std::string name() override {return "StartMotor";}
	};

// #1c Define the StopMotor concrete event class initialising the TimeDate
	class StopMotor : public IEvent {
	public:
		StopMotor(TimeDate time) : IEvent{ time } {}
		void go() override {}
	private:
		std::string name() override { return "StopMotor"; }
	};

// #1c Define the StartRecording concrete event class initialising the TimeDate
	class StartRecording : public IEvent {
	public:
		StartRecording(TimeDate time) : IEvent{ time } {}
		void go() override {}
	private:
		std::string name() override { return "StartRecording"; }
	};

// #1c Define the StopRecording concrete event class initialising the TimeDate
	class StopRecording : public IEvent {
	public:
		StopRecording(TimeDate time) : IEvent{ time } {}
		void go() override {}
	private:
		std::string name() override { return "StopRecording"; }
	};
}
