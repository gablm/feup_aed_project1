#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <map>
#include <iostream>
#include <fstream>
#include "bst.h"
#include "student.h"
#include "uc.h"
#include "session.h"

class Manager {
	private:
		BST students;
		std::map<std::string, UC> ucMap;
	public:
		Manager();
		void load_data();
};

#endif