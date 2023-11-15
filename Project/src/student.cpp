#include "headers/student.h"
#include <algorithm>
#include <ostream>

/**
 * The only constructor for this class
 * @param name Student Name
 * @param code Student number
*/
Student::Student(std::string name, int code) : name(name), code(code) {}

/**
 * @return Student name
 * @note Complexity: O(1)
*/
std::string Student::getName() const {
	return name;
}

/**
 * @return Identification number (code)
 * @note Complexity: O(1)
*/
int Student::getCode() const {
	return code;
}

/**
 * @return The number of UCs the student is in
 * @note Complexity: O(1)
*/
int Student::getUCcount() const {
	return ucCount;
}

/**
 * @param diff Number to add to the UC count
 * @note Complexity: O(1)
 */
void Student::editUCcount(int diff) {
	ucCount += diff;
}

/**
 * Returns the student schedule, composed of pairs of one UC and a Session/Class 
 * @return Vector of pair<UC, Session>
 * @note Complexity: O(1)
*/
std::vector<std::pair<UC*,Session*>> Student::getSchedule() const {
	return schedule;
}

/**
 * Adds an element to the student schedule
 * @return If the addition was successful
 * @note Complexity: O(1)
*/
bool Student::addToSchedule(std::pair<UC*,Session*> ucSessionPair) {
	schedule.push_back(ucSessionPair);
	return true;
}

/**
 * Removes a <UC, Class> combination from the students schedule
 * @return If that pair exists and can be removed
 * @note Complexity: O(n)
*/
bool Student::removeFromSchedule(std::pair<UC*,Session*> ucSessionToRemove) {
	for (auto i = schedule.begin(); i != schedule.end(); i++) {
		if (*i == ucSessionToRemove) {
			schedule.erase(i);
			return true;
		}
	}
	return false;
}

/**
 * Checks if a session to be added overlaps
 * @param ucname Name of the UC, used to ignore existing classes in the case of switching
 * @param session Pointer to the session to verify
 * @return True if there are conflicts, false otherwise
 * @note Complexity: O(n)
*/
bool Student::verifyScheduleConflict(std::string ucname, Session* session){
	
	if (!session)
		return false;
	
	double minTime = session->getTime();
	double maxTime = minTime + session->getDuration();
	double tempMinTime, tempMaxTime;
	
	for (auto i = schedule.begin(); i != schedule.end(); i++) {
		
		if (i->second->getType() == "T" || i->first->getName() == ucname)
			continue;

		Session tempSession = *(i->second);
		tempMinTime = tempSession.getTime();
		tempMaxTime = tempMinTime + tempSession.getDuration();
		
		if(tempMaxTime > minTime && tempMinTime < maxTime && session->getDay() == tempSession.getDay())
			return true;
	}

	return false;
}
