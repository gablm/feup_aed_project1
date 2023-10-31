#include "headers/session.h"
#include <ostream>

/** Constructor for the session class
 * @param name Session name (year, course_id, number)
 * @param day Day of the week in string format
 * @param time Time of the day in base 10
 * @param duration Duration in base 10
 * @param type Type of session [T, TP, LP]
*/
Session::Session(std::string name, std::string day, double time, double duration, std::string type)
	: name(name), day(day), time(time), duration(duration), type(type) {}

/**
 * Complexity: O(1)
 * @return Session name
*/
std::string Session::getName() const {
	return name;
}

/**
 * Complexity: O(1)
 * @return Day of the week for the session
*/
std::string Session::getDay() const {
	return day;
}

/**
 * Complexity: O(1)
 * @return Session time (base 10 | 1.5 = 1h30)
*/
double Session::getTime() const {
	return time;
}

/**
 * Complexity: O(1)
 * @return Session duration (base 10 | 10.5 = 10:30)
*/
double Session::getDuration() const {
	return duration;
}

/**
 * Complexity: O(1)
 * @return Number of students in the session
*/
size_t Session::getSessionCount() const {
	return studentList.size();
}

/**
 * Complexity: O(1)
 * @return Session Type
*/
std::string Session::getType() const {
	return type;
}

/**
 * Complexity: O(1) | 
 * Adds a student to a session
 * @param student Pointer to a student
*/
void Session::addStudent(Student *student)
{
	studentList.push_back(student);
}

/**
 * Complexity: estimated worse case O(n) |
 * Removes a student from the session
 * @param student Pointer to a student
*/
void Session::removeStudent(Student *student) {
	studentList.remove(student);
}

int Session::getsize() const{
	return studentList.size();
}