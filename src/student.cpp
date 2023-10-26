#include "student.h"
#include <algorithm>

/**
 * The only constructor for this class
 * @param name Student Name
 * @param up Student number (commonly known as UP)
*/
Student::Student(std::string name, int up) : name(name), up(up) {}

/**
 * O(1)
 * @return Student name
*/
std::string Student::getName() const {
	return name;
}

/**
 * O(1)
 * @return Identification number (UP)
*/
int Student::getUP() const {
	return up;
}

/**
 * Returns the student schedule, composed of pairs of one UC and a Session/Class 
 * O(1)
 * @return Vector of pair<UC, Session>
*/
std::vector<std::pair<UC,Session>> Student::getSchedule() const {
	return schedule;
}

/**
 * Adds an element to the student schedule
 * @return If the addition was sucessful
*/
bool addToSchedule(std::pair<UC,Session> ucSessionPair) {
	(void)ucSessionPair;
	return true;
}

/**
 * Removes a <UC, Class> combination from the students schedule
 * As 
 * @return If that pair exists and can be removed
*/
bool Student::removeFromSchedule(std::pair<UC,Session> ucSessionToRemove) {
	(void)ucSessionToRemove;
	return false;
}
