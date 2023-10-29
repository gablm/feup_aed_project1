#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <map>
#include <set>

#include "bst.h"
#include "student.h"
#include "uc.h"
#include "session.h"

class Manager {
	private:
		BST students;
		static const int sessionCap = 25;
		std::map<std::string, UC*> ucMap;
		std::set<std::string> sessionSet;
	public:
		Manager();
		~Manager();
		void load_map();
		void test_map();
		void load_students();
		void test_students();
		BST& getStudents();
		std::map<std::string, UC*>& getUcMap();
};

#endif