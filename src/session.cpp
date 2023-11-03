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
 * @return Session name
 * @note Complexity: O(1)
*/
std::string Session::getName() const {
	return name;
}

/**
 * @return Day of the week for the session
 * @note Complexity: O(1)
*/
std::string Session::getDay() const {
	return day;
}

/**
 * @return Session time (base 10 | 1.5 = 1h30)
 * @note Complexity: O(1)
*/
double Session::getTime() const {
	return time;
}

/**
 * @return Session duration (base 10 | 10.5 = 10:30)
 * @note Complexity: O(1)
*/
double Session::getDuration() const {
	return duration;
}

/**
 * @return Number of students in the session
 * @note Complexity: O(1)
*/
size_t Session::getSessionCount() const {
	return studentList.size();
}

/**
 * @return Session Type
 * @note Complexity: O(1)
*/
std::string Session::getType() const {
	return type;
}

/**
 * Adds a student to a session
 * @param student Pointer to a student
 * @note Complexity: O(1)
*/
void Session::addStudent(Student *student)
{
	studentList.push_back(student);
}

/**
 * Removes a student from the session
 * @param student Pointer to a student
 * @note Complexity: estimated worst case O(n)
*/
void Session::removeStudent(Student *student) {
	studentList.remove(student);
}

/**
 * @return The ammount of students in the Session
 * @note Complexity: O(1)
*/
int Session::getsize() const{
	return studentList.size();
}