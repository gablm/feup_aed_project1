#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <vector>
#include <utility>
#include "uc.h"
#include "session.h"

class Student {
	private:
		std::string name;
		int up;
		std::vector<std::pair<UC, Session>> schedule;
	public:
		Student(std::string name, int up);
		std::string getName() const;
		int getUP() const;
		std::vector<std::pair<UC,Session>> getSchedule() const;
		bool addToSchedule(std::pair<UC,Session> ucSessionPair);
		bool removeFromSchedule(std::pair<UC,Session> ucSessiontoRemove);
};

#endif