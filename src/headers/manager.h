#ifndef MANAGER_H
#define MANAGER_H

#include <string>
#include <map>
#include <set>
#include <ctime>
#include <stack>

#include "bst.h"
#include "student.h"
#include "uc.h"
#include "session.h"

class Request {
	public:
		Request(time_t time, std::string type, std::string studentCode, std::string UC1, std::string session1, std::string UC2, std::string session2);
		time_t timestamp;
		std::string type;
		std::string studentCode;
		std::string UC1;
		std::string session1;
		std::string UC2;
		std::string session2;	
};

class Manager {
	private:
		BST students;
		static const int sessionCap = 25;
		std::map<std::string, UC*> ucMap;
		std::set<std::string> sessionSet;
		std::stack<Request*> requestStack;
	public:
		Manager();
		~Manager();
		void load_map();
		void test_map();
		void load_students();
		void test_students();
		void load_alterations();
		BST& getStudents();
		std::map<std::string, UC*>& getUcMap();
		std::set<std::string>& getSessionSet();
		std::stack<Request*>& getRequestStack();
		int getsessionCap();


		void RemoveUC(time_t time, std::string UCname, Student *student);
		void NewClass(time_t time, std::string uccode, std::string classcode, Student *student);
		void RemoveUC(std::string UCname, Student *student);
		void NewClass(std::string uccode, std::string classcode, Student *student);
		void SwapUC(std::string oldUCcode, std::string newUCcode, std::string classcode, Student *student);

};

#endif