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
		virtual void start() { _status = true; std::cout << '\n' << print() << "\n\n"; }
		virtual void stop() { _status = false; std::cout << '\n' << print() << "\n\n"; }
		bool status() { return _status; }
		std::string print() { return name() + " " + ISwitchable::name() + (status() ? " ON" : " OFF"); }
		virtual ~ISwitchable() { std::cout << name() << " " << ISwitchable::name() << " Deleted\n\n"; }
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

	class IEvent : public TimeDate {
	public:
		std::string print() { return name() + " at " + timeStr(); }
		virtual void operator()() = 0;
		virtual ~IEvent() = default;
		bool operator >(const IEvent & rhs) const { return TimeDate(*this) > TimeDate(rhs); }
		bool operator <(const IEvent & rhs) const { return TimeDate(*this) < TimeDate(rhs); }
	protected:
		IEvent(TimeDate time) : TimeDate( time) {};
	private:
		std::string timeStr() { return TimeDate::print(); }
		virtual std::string name() = 0;
	};

	template<typename target>
	class Event : public IEvent {
	public:
		Event(std::shared_ptr<target> switchable, TimeDate time, void (target::*Fn)())
			: IEvent{ time },
			_switchable{ move(switchable) },
			Fn{ Fn } {}

		target * switchable() { return _switchable.get(); }
		void operator()() override { (switchable()->*Fn)(); }
	protected:
	private:
		std::string name() override { return switchable()->print(); }
		std::shared_ptr<target> _switchable;
		void (target::*Fn)();
	};
}
