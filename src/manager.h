#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <map>

#include "bst.h"
#include "student.h"
#include "uc.h"
#include "session.h"

class Manager {
	private:
		BST students;
		static const int sessionCap = 25;
		std::map<std::string, UC> ucMap;
	public:
		Manager();
		void load_data();
};

#endif