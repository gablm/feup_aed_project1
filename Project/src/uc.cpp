#include "headers/uc.h"

/**
 * Constructor for the UC class
 * @param name UC code - Ex. L.EIC001
 * @param year Year that the UC belongs to
*/
UC::UC(std::string name, int year) : name(name), year(year) {}

/**
 * @return UC code
 * @note Complexity: O(1)
*/
std::string UC::getName() const {
	return name;
}

/**
 * @return UC year
 * @note Complexity: O(1)
*/
int UC::getYear() const {
	return year;
}

/**
 * @param diff Number to add to the student count
 * @note Complexity: O(1)
 */
void UC::editStudentCount(int diff) {
	students += diff;
}

/**
 * @return UC student count
 * @note Complexity: O(1)
*/
int UC::getStudentCount() const {
	return students;
}

/**
 * @param session The class/session to add to the UC
 * @note Complexity: O(1)
*/
void UC::addSession(Session *session) {
	sessionList.push_back(session);
}

/**
 * @return The list of Sessions for the UC
 * @note Complexity: O(1)
*/
std::list<Session*> UC::getSessionList() const {
	return sessionList;
}

/**
 * Clears all the sessions for a UC
 * @note Complexity: O(n)
*/
void UC::clearSessions() {
	for (auto i = sessionList.begin(); i != sessionList.end(); i++)
		delete *i;
	sessionList.clear();
}

/**
 * Finds all the session with the same name/code
 * @return List of sessions
 * @note Complexity: O(n)
*/
std::list<Session*> UC::find(std::string sessionName) {
	std::list<Session*> res;
	for (auto i = sessionList.begin(); i != sessionList.end(); i++)
	{
		if ((*i)->getName() == sessionName)
			res.push_back(*i);
	}
	return res;
}

/**
 * Checks if adding a student to the session generates a occupation conflict
 * @return True if there are conflicts, false otherwise
 * @note Complexity: O(n)
*/
bool UC::verifyOccupancyConflict(Session* newSession, Session* oldSession){
	
	if (!newSession && !oldSession)
		return false;
	
	int maxOccupancy = newSession->getsize();
	int minOccupancy = maxOccupancy;
	int tempOccupancy;

	for (auto i = sessionList.begin(); i != sessionList.end(); i++) {
		tempOccupancy = (*i)->getsize();

		if (tempOccupancy >= maxOccupancy) 
			maxOccupancy = tempOccupancy;
		if (tempOccupancy <= minOccupancy) 
			minOccupancy = tempOccupancy;
	}

	if (minOccupancy == newSession->getsize())
		return false;

	if (!oldSession && ((maxOccupancy - minOccupancy < 5 && newSession->getsize() != maxOccupancy) || maxOccupancy - minOccupancy < 4))
		return false;

	if (minOccupancy == newSession->getsize())
		return false;

	if (maxOccupancy - minOccupancy > 4)
		return true;
	
	if (!oldSession){
		return true;
	}

	if (maxOccupancy - minOccupancy == 4 
			&& (newSession->getsize() == maxOccupancy || oldSession->getsize() == minOccupancy) 
			&& (newSession->getsize() != oldSession->getsize()))
		return true;

	return false;
}
