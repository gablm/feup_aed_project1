#include "headers/student.h"
#include <algorithm>
#include <ostream>
#include <iostream>

/**
 * The only constructor for this class
 * @param name Student Name
 * @param up Student number (commonly known as code)
*/
Student::Student(std::string name, int code) : name(name), code(code) {}

/**
 * Complexity: O(1)
 * @return Student name
*/
std::string Student::getName() const {
	return name;
}

/**
 * Complexity: O(1)
 * @return Identification number (code)
*/
int Student::getCode() const {
	return code;
}

/**
 * Complexity: O(1)
 * @return The number of UCs the student is in
*/
int Student::getUCcount() const {
	return ucCount;
}

/**
 * Complexity: O(1)
 * @param diff Number to add to the UC count
 */
void Student::editUCcount(int diff) {
	ucCount += diff;
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
 * Complexity: O(1)
 * @return If the addition was sucessful
*/
bool Student::addToSchedule(std::pair<UC*,Session*> ucSessionPair) {
	schedule.push_back(ucSessionPair);
	return true;
}

/**
 * Removes a <UC, Class> combination from the students schedule
 * Complexity: O(n)
 * @return If that pair exists and can be removed
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

bool Student::verifyScheduleConflict(Session* session){
	double minTime = session->getTime();
	double maxTime = minTime+session->getDuration();
	double tempMinTime;
	double tempMaxTime;
	
	Session* tempSession = session;

	for (auto i = schedule.begin(); i != schedule.end(); i++) {
		if (i->second->getType()=="T"){
			continue;
		}
		tempSession = i->second;
		tempMinTime = tempSession->getTime();
		tempMaxTime = tempMinTime+tempSession->getDuration();
		if(tempMaxTime>minTime && tempMinTime < maxTime && session->getDay() == i->second->getDay()){
			return true;
		}
	}
	return false;
}