#ifndef STUDENT_H
#define STUDENT_H

#include <string>
#include <ostream>
#include <vector>
#include <utility>

class UC;
class Session;

class Student {
	private:
		std::string name;
		int up;
		std::vector<std::pair<UC, Session>> schedule;
	public:
		//...
};

#endif