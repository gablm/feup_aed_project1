#ifndef UC_H
#define UC_H

#include <string>
#include <list>
#include <ostream>
#include "session.h"

class UC {
	private:
		std::string name;
		std::list<Session> sessionList;
	public:
		UC(std::string name);
		std::string getName() const;
		void addSession(Session session);
		std::list<Session> getSessionList() const;
};

#endif