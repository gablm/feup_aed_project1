#include "headers/uc.h"

/**
 * Constructor for the UC class
 * @param name UC code - Ex. L.EIC001
 * @param year Year that the UC belongs to
*/
UC::UC(std::string name, int year) : name(name), year(year) {}

/**
 * Complexity: O(1)
 * @return UC code
*/
std::string UC::getName() const {
	return name;
}

/**
 * Complexity: O(1)
 * @return UC year
*/
int UC::getYear() const {
	return year;
}

/**
 * Complexity: O(1)
 * @param diff Number to add to the student count
 */
void UC::editStudentCount(int diff) {
	students += diff;
}

/**
 * Complexity: O(1)
 * @return UC student count
*/
int UC::getStudentCount() const {
	return students;
}

/**
 * Complexity: O(1)
 * @param session The class/session to add to the UC
*/
void UC::addSession(Session *session) {
	sessionList.push_back(session);
}

/**
 * Complexity: O(1)
 * @return The list of Sessions for the UC
*/
std::list<Session*> UC::getSessionList() const {
	return sessionList;
}

/**
 * Complexity: O(n) | 
 * Clears all the sessions for a UC
*/
void UC::clearSessions() {
	for (auto i = sessionList.begin(); i != sessionList.end(); i++)
		delete *i;
	sessionList.clear();
}

/**
 * Complexity: O(n) | 
 * Finds all the session with the same name/code
 * @return List of sessions
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
 * Complexity: O(n) |
 * Checks if adding a student to the session generates a occupation conflict
 * @return True if there are conflits, false otherwise
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

	if (!oldSession && ((maxOccupancy - minOccupancy < 4 && newSession->getsize() != maxOccupancy) || maxOccupancy - minOccupancy < 4))
		return false;

	if (minOccupancy == newSession->getsize())
		return false;

	if (maxOccupancy - minOccupancy > 4)
		return true;

	if (maxOccupancy - minOccupancy == 4 
			&& (newSession->getsize() == maxOccupancy || oldSession->getsize() == minOccupancy) 
			&& (newSession->getsize() != oldSession->getsize()))
		return true;

	return false;
}