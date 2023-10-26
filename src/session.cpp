#include "session.h"
#include <ostream>

/**
 * Default constructor
 * Hour and Minute are set to 0
*/
Time::Time() : hour(0), minute(0) {}

/**
 * Constructor with two integers
 * @param h Hour 
 * @param n Minute
*/
Time::Time(int h, int m) : hour(h), minute(m) {}

/**
 * Complexity: O(1)
 * @return Hours
*/
int Time::getHour() const {
	return hour;
}

/**
 * Complexity: O(1)
 * @return Minutes
*/
int Time::getMinute() const {
	return minute;
}

/**
 * Streamlines printing the Time class
*/
std::ostream& operator<<(std::ostream& os, Time time)
{
	os << time.getHour() << ":" << time.getMinute();
	return os;
}

/** Constructor for the session class
 * @param name Session name (year, course_id, number)
 * @param time Time the session will occur (h, m)
 * @param type Type of session [T, TP, LP]
*/
Session::Session(SessionName name, Time time, std::string type)
	: name(name), time(time), type(type) {}

/**
 * Complexity: O(1)
 * @return Session name
*/
SessionName Session::getName() const {
	return name;
}

/**
 * Complexity: O(1)
 * @return Session time
*/
Time Session::getTime() const {
	return time;
}

/**
 * Complexity: O(1)
 * @return Session Type
*/
std::string Session::getType() const {
	return type;
}

/**
 * Complexity: O(1)
 * @param student Pointer to a student
*/
void Session::addStudent(Student *student)
{
	studentList.push_back(student);
}

/**
 * Overload of the << operator for the SessionName class
 * Streamlines the process of printing the Name for the session
*/
std::ostream& operator<<(std::ostream& os, SessionName name)
{
	os << name.year << name.course_id << name.number;
	return os;
}
