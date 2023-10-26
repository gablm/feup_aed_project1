#include "student.h"
#include <algorithm>

Student::Student(std::string name, int up) : name(name), up(up) {}

std::string Student::getName() const {
	return name;
}

int Student::getUP() const {
	return up;
}

std::vector<std::pair<UC,Session>> Student::getSchedule() const {
	return schedule;
}

bool addToSchedule(std::pair<UC,Session> ucSessionPair) {
	(void)ucSessionPair;
	return true;
}

/**
 * Removes a <UC, Class> combination from the students schedule
 * As 
*/
bool Student::removeFromSchedule(std::pair<UC,Session> ucSessionToRemove) {
	(void)ucSessionToRemove;
	return false;
}
