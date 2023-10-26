#include "session.h"
#include <ostream>

Time::Time() : hour(0), minute(0) {}

Time::Time(int h, int m) : hour(h), minute(m) {}

int Time::getHour() const {
	return hour;
}

int Time::getMinute() const {
	return minute;
}

std::ostream& operator<<(std::ostream& os, Time time)
{
	os << time.getHour() << ":" << time.getMinute();
	return os;
}

Session::Session(SessionName name, Time time, std::string type)
	: name(name), time(time), type(type) {}

void Session::addStudent(Student *student)
{
	studentList.push_back(student);
}

SessionName Session::getName() const {
	return name;
}

Time Session::getTime() const {
	return time;
}

std::string Session::getType() const {
	return type;
}

std::ostream& operator<<(std::ostream& os, SessionName name)
{
	if (name.year > 0)
		os << name.year;
	os << name.course_id << name.number;
	return os;
}
