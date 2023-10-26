#include "uc.h"

/**
 * Constructor for the UC class
 * @param name UC code - Ex. L.EIC001
*/
UC::UC(std::string name) : name(name) {}

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
void UC::addSession(Session session) {
	sessionList.push_back(session);
}

/**
 * Complexity: O(1)
 * @return The list of Sessions for the UC
*/
std::list<Session> UC::getSessionList() const {
	return sessionList;
}