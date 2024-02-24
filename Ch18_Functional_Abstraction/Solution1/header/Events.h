//====================================================================
// File:        Events.h
// Description: Declaration of Event related classes
//====================================================================
#pragma once
#include "Time_Date.h"
#include <iostream>
#include <string>
#include <utility>
#include <memory>

namespace TimesDates {

	class ISwitchable {
	public:
		virtual void start() { _status = true; }
		virtual void stop() { _status = false; }
		bool status() { return _status; }
		std::string print() { return name() + " " + ISwitchable::name() + (status() ? " ON" : " OFF"); }
		virtual ~ISwitchable() {std::cout << name() << " " << ISwitchable::name() << " Deleted\n"; }
	protected:
		ISwitchable(const std::string & ID) : ID(ID) {}
		ISwitchable(std::string && ID) : ID(std::move(ID)) { std::cout << "Move" << '\n'; }
	private:
		virtual std::string name() = 0;
		bool _status = false;
		std::string ID;
	};
	inline std::string ISwitchable::name() { return ID; }

	class Motor : public ISwitchable {
	public:
		Motor(const std::string & ID) : ISwitchable(ID) {}
		Motor(std::string && ID) : ISwitchable(std::move(ID)) {}
	private:
		std::string name() override { return "Motor"; }
	};

	class Recorder : public ISwitchable {
	public:
		Recorder(const std::string & ID) : ISwitchable(ID) {}
		Recorder(std::string && ID) : ISwitchable(std::move(ID)) {}
	private:
		std::string name() override { return "Recorder"; }
	};

// #1a Convert the Action classes into functors and remove the go() function and IAction class.
	//class IAction {
	//public:
	//	virtual void go() = 0;
	//protected:
	//	IAction() {}
	//	virtual std::string name() = 0 { return " at "; }
	//};


//	class IEvent : public IAction, public TimeDate {
	class IEvent : public TimeDate {
	public:
		//std::string print() { return name() + IAction::name() + timeStr(); }
		std::string print() { return name() + " at " + timeStr(); }
		ISwitchable * switchable() { return _switchable.get(); }
		virtual void operator()() = 0;
		virtual ~IEvent(){}
	protected:
		IEvent(std::shared_ptr<ISwitchable> switchable, TimeDate time) : TimeDate(time), _switchable{ move(switchable) } {}
	private:
		//std::string name() override {return switchable()->print();}
		std::string name()  {return switchable()->print();}
		std::string timeStr() { return TimeDate::print(); }
		std::shared_ptr<ISwitchable> _switchable;
	};

// #4a Template the Event class on target type 
// #3a Merge Event with IEvent
// #2a Replace the four concrete event classes with a single Event class that takes a member function pointer as a constructor argument and uses this in its function operator.

	class StartMotor : public IEvent {
	public:
		StartMotor(std::shared_ptr<ISwitchable> switchable, TimeDate time) : IEvent{ move(switchable), time } {}
//		void go() override { switchable()->start(); }
		void operator()() override { switchable()->start(); }
	private:
	};

	class StopMotor : public IEvent {
	public:
		StopMotor(std::shared_ptr<ISwitchable> switchable, TimeDate time) : IEvent{ move(switchable),  time } {}
//		void go() override {switchable()->stop(); }
		void operator()() override {switchable()->stop(); }
	private:
	};

	class StartRecording : public IEvent {
	public:
		StartRecording(std::shared_ptr<ISwitchable> switchable, TimeDate time) : IEvent{ move(switchable), time } {}
//		void go() override { switchable()->start(); }
		void operator()() override { switchable()->start(); }
	private:
	};

	class StopRecording : public IEvent {
	public:
		StopRecording(std::shared_ptr<ISwitchable> switchable, TimeDate time) : IEvent{ move(switchable), time } {}
//		void go() override { switchable()->stop(); }
		void operator()() override { switchable()->stop(); }
	private:
	};

}
