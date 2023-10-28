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
 * Complexity: O(n???)
 * Clears all the sessions for a UC
*/
void UC::clearSessions() {
	for (auto i = sessionList.begin(); i != sessionList.end(); i++)
		delete *i;
	sessionList.clear();
}

std::list<Session*> UC::find(std::string sessionName) {
	std::list<Session*> res;
	for (auto i = sessionList.begin(); i != sessionList.end(); i++)
	{
		if ((*i)->getName() == sessionName)
			res.push_back(*i);
	}
	return res;
}
