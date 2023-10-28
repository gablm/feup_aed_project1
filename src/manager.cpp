#include "manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Manager::Manager(): students(BST()), ucMap() {}

void Manager::load_map() {

    string line, sessionName, UCName, sessionDay, sessionType, sessionTimestr, sessionDurationstr;
    double sessionTime, sessionDuration;
	UC *temp_uc = NULL;

    ifstream file;
    file.open("data/classes.csv");

	if (file.fail()) {
		std::cout << "Invalid File";
		exit(0);
	}

    getline(file,line); //removes the first line, which has no usable values

    while(true) {
		
		if (file.eof())
			break;
		
		getline(file,line);

		if (line.size() < 1)
			continue;

        istringstream ss(line);

        // inserts the contents of the line into the apropriate variables, for the non-string variables an extra line was needed
		std::getline(ss, sessionName, ',');
        std::getline(ss, UCName, ',');
        std::getline(ss, sessionDay, ',');
        std::getline(ss, sessionTimestr, ',');
        sessionTime = stof(sessionTimestr);
        std::getline(ss, sessionDurationstr, ',');
        sessionDuration = stof(sessionDurationstr);
        std::getline(ss, sessionType, '\r');

		if (!temp_uc || temp_uc->getName() != UCName) {
			temp_uc = new UC(UCName, sessionName[0] - '0');
			ucMap[UCName] = temp_uc;
		}

        Session *temp_session = new Session(sessionName, sessionDay, sessionTime, sessionDuration, sessionType);
        temp_uc->addSession(temp_session);
    }
    file.close();
}

void Manager::test_map()
{
	for (auto i = ucMap.begin(); i != ucMap.end(); i++)
	{
		UC *temp = i->second;
		std::cout << temp->getName() << endl;
		for (Session *i : temp->getSessionList())
		{
			std::cout << " ID: " << i->getName() 
			<< " Type: " << i->getType()
			<< " At: " << i->getTime()
			<< " During: " << i->getDuration()
			<< " Day: " << i->getDay() 
			<< "\n";
		}
		std::cout << endl;
	}
}

void Manager::load_students() {

    string line, codeStr, studentName, UCName, sessionName;
    int code;
	Student *temp_student = NULL;

    ifstream file;
    file.open("data/students_classes.csv");

	if (file.fail()) {
		std::cout << "Invalid File";
		exit(0);
	}

    getline(file,line); //removes the first line, which has no usable values

    while(true) {
		
		if (file.eof())
			break;
		
		getline(file,line);

		if (line.size() < 1)
			continue;

        istringstream ss(line);

        // inserts the contents of the line into the apropriate variables, for the non-string variables an extra line was needed
		std::getline(ss, codeStr, ',');
		code = stoi(codeStr);
		std::getline(ss, studentName, ',');
		std::getline(ss, UCName, ',');
		std::getline(ss, sessionName, '\r');
        
		if (!temp_student || temp_student->getCode() != code) {
			temp_student = new Student(studentName, code);
			students.insert(code, temp_student);
		}

		UC *uc = ucMap[UCName];
		std::list<Session*> sessions = uc->find(sessionName);
		for (Session *s : sessions)
			temp_student->addToSchedule(make_pair(uc, s));
		
    }
    file.close();
}

void print(BSTnode *node)
{
	if (!node)
		return;
	
	print(node->left);
	
	Student *a = (Student *)node->content;
	std::cout 
	<< a->getCode()
	<< " - " << a->getName()
	<< endl;

	for (auto pair : a->getSchedule())
	{
		Session *a = pair.second;
		std::cout
		<< " " << pair.first->getName()
		<< " " << a->getName()
		<< " " << a->getDay()
		<< " " << a->getType()
		<< " @ " << a->getTime()
		<< " > " << a->getDuration()
		<< endl;
	}

	print(node->right);
}

void Manager::test_students() {
	print(students.getNode());
}

void Manager::dealocate_memory()
{
	// As UCs as dinamically allocated, they need to be deleted
	students.clear();
	for (auto i = ucMap.begin(); i != ucMap.end(); i++)
	{
		UC *p = i->second;
		p->clearSessions();
		delete i->second;
	}
}