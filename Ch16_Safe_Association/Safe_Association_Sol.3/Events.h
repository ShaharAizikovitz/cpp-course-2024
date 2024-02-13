//====================================================================
// File:        Action.h
// Description: Declaration of IAction and derived classes
//====================================================================
#pragma once
#include "Time_Date.h"
#include <iostream>
#include <string>
#include <utility>
#include <memory>

namespace TimesDates {

// #1a Define a new ISwitchable abstract class that maintains a string ID and a boolean status for derived classes
// �	It should implement start() and stop() each modifying the status.
// �	It should implement status() returning the Boolean status.
// �	It should implement a non - virtual print() function using the template method pattern
//   	to return a string of the form : <class name> <ID> <status> e.g. "Motor Extractor Fan OFF"
// �	Provide  a destructor printing the ID of the object when it is destructed

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

// #1b Define a derived Motor class initialising the base-class string ID
	class Motor : public ISwitchable {
	public:
		Motor(const std::string & ID) : ISwitchable(ID) {}
		Motor(std::string && ID) : ISwitchable(std::move(ID)) {}
	private:
		std::string name() override { return "Motor"; }
	};

// #1b Define a derived Recorder class initialising the base-class string ID
	class Recorder : public ISwitchable {
	public:
		Recorder(const std::string & ID) : ISwitchable(ID) {}
		Recorder(std::string && ID) : ISwitchable(std::move(ID)) {}
	private:
		std::string name() override { return "Recorder"; }
	};


	class IAction {
	public:
		virtual void go() = 0;
		virtual ~IAction() {}
	protected:
		IAction() {}
		virtual std::string name() = 0;
	};
	inline std::string IAction::name() { return " at "; }

// #2a Amend the event classes to associate with ISwitchable objects
	class IEvent : public IAction, public TimeDate {
	public:
		std::string print() { return name() + IAction::name() + timeStr(); }
// #2b Provide a public switchable() function returning the pointer and make the pointer private. 
		ISwitchable * switchable() { return _switchable.get(); }
	protected:
// #3b Amend the constructor to take a shared_ptr. Use move() to initialise the data member.
//		IEvent(ISwitchable * switchable, TimeDate time) : _switchable{ switchable }, TimeDate { time } {}
		IEvent(std::shared_ptr<ISwitchable> switchable, TimeDate time) : TimeDate(time), _switchable{ move(switchable) } {}
	private:
//		std::string name() override = 0;
		std::string name() override {return switchable()->print();}
		std::string timeStr() { return TimeDate::print(); }
// #3a Amend the IEvent class to hold the ISwitchable in a shared_ptr
		//ISwitchable * _switchable;
		std::shared_ptr<ISwitchable> _switchable;
	};
	
// #2c Make the go() functions delegate to the associated object
	class StartMotor : public IEvent {
	public:
//		StartMotor(ISwitchable * switchable, TimeDate time) : IEvent{switchable, time } {}
		StartMotor(std::shared_ptr<ISwitchable> switchable, TimeDate time) : IEvent{ move(switchable), time } {}
		void go() override { switchable()->start(); }
	private:
//		std::string name() override {return "StartMotor";}
	};

	class StopMotor : public IEvent {
	public:
//		StopMotor(ISwitchable * switchable, TimeDate time) : IEvent{ switchable,  time } {}
		StopMotor(std::shared_ptr<ISwitchable> switchable, TimeDate time) : IEvent{ move(switchable),  time } {}
		void go() override {switchable()->stop(); }
	private:
//		std::string name() override { return "StopMotor"; }
	};

	class StartRecording : public IEvent {
	public:
		//StartRecording(ISwitchable * switchable, TimeDate time) : IEvent{ switchable, time } {}
		StartRecording(std::shared_ptr<ISwitchable> switchable, TimeDate time) : IEvent{ move(switchable), time } {}
		void go() override { switchable()->start(); }
	private:
//		std::string name() override { return "StartRecording"; }
	};

	class StopRecording : public IEvent {
	public:
//		StopRecording(ISwitchable * switchable, TimeDate time) : IEvent{ switchable, time } {}
		StopRecording(std::shared_ptr<ISwitchable> switchable, TimeDate time) : IEvent{ move(switchable), time } {}
		void go() override { switchable()->stop(); }
	private:
//		std::string name() override { return "StopRecording"; }
	};

}
