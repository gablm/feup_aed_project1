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
		std::map<std::string, UC> ucMap;
	public:
		void load_data();
};

#endif