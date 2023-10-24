#ifndef UC_H
#define UC_H

#include <string>
#include <list>
#include <ostream>

class Session;

class UC {
	private:
		std::string name;
		std::list<Session> sessions;
	public:
		//...
};

#endif