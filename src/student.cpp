#include "student.h"
#include <algorithm>
#include <ostream>
#include <iostream>

/**
 * The only constructor for this class
 * @param name Student Name
 * @param up Student number (commonly known as UP)
*/
Student::Student(std::string name, int up) : name(name), up(up) {}

/**
 * Complexity: O(1)
 * @return Student name
*/
std::string Student::getName() const {
	return name;
}

/**
 * Complexity: O(1)
 * @return Identification number (UP)
*/
int Student::getUP() const {
	return up;
}

/**
 * Returns the student schedule, composed of pairs of one UC and a Session/Class 
 * Complexity: O(1)
 * @return Vector of pair<UC, Session>
*/
std::vector<std::pair<UC*,Session*>> Student::getSchedule() const {
	return schedule;
}

/**
 * Adds an element to the student schedule
 * Complexity: O(??)
 * @return If the addition was sucessful
*/
bool addToSchedule(std::pair<UC*,Session*> ucSessionPair) {
	(void)ucSessionPair;
	std::cout << "not done - add schedule";
	return true;
}

/**
 * Removes a <UC, Class> combination from the students schedule
 * Complexity: O(??)
 * @return If that pair exists and can be removed
*/
bool Student::removeFromSchedule(std::pair<UC*,Session*> ucSessionToRemove) {
	(void)ucSessionToRemove;
	std::cout << "not done - remove schedule";
	return false;
}
