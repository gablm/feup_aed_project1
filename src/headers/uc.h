#ifndef UC_H
#define UC_H

#include <string>
#include <list>
#include <ostream>
#include "session.h"

class UC {
	private:
		std::string name;
		int year;
		int students = 0;
		std::list<Session*> sessionList;
	public:
		UC(std::string name, int year);
		std::string getName() const;
		int getYear() const;
		void editStudentCount(int diff);
		int getStudentCount() const;
		void addSession(Session *session);
		void clearSessions();
		std::list<Session*> find(std::string sessionName);
		std::list<Session*> getSessionList() const;
};

#endif