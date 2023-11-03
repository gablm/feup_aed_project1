#include "headers/manager.h"
#include "headers/ui.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Manager::Manager() : students(BST()), ucMap() {}

/**
 * Complexity: O(n) |
 * Disposes of everything that was allocated on the data filling methods.
 */
Manager::~Manager()
{
	students.clear([](void *ptr)
				   { delete (Student *)ptr; });
	for (auto i = ucMap.begin(); i != ucMap.end(); i++)
	{
		UC *p = i->second;
		p->clearSessions();
		delete i->second;
	}
	while (!requestStack.empty()) {
		auto i = requestStack.top();
		delete i;
		requestStack.pop();
	}
}

/**
 * Complexity: O(1) |
 * Returns the Binary Search Tree where the students are stored.
*/
BST &Manager::getStudents()
{
	return students;
}

/**
 * Complexity: O(1) |
 * Returns the map of UCs.
*/
std::map<std::string, UC *> &Manager::getUcMap()
{
	return ucMap;
}

/**
 * Complexity: O(1) |
 * Returns the set of Session in string format.
 * It makes it easier to find all classes without going thru all ucs.
*/
std::set<std::string> &Manager::getSessionSet()
{
	return sessionSet;
}

/**
 * Complexity: O(n) |
 * Goes thru every line of the Classes dataset and fills various structures: 
 * The map of UCs, the set of classes and the list of session inside each UC.
*/
void Manager::load_map()
{

	string line, sessionName, UCName, sessionDay, sessionType, sessionTimestr, sessionDurationstr;
	double sessionTime, sessionDuration;
	UC *temp_uc = NULL;

	ifstream file;
	file.open("./data/classes.csv");

	if (file.fail())
	{
		std::cout << "Invalid File - Please insert a valid classes.csv in the data folder.";
		exit(0);
	}

	getline(file, line);

	while (true)
	{

		if (file.eof())
			break;

		getline(file, line);

		if (line.size() < 5)
			continue;

		istringstream ss(line);

		std::getline(ss, sessionName, ',');
		std::getline(ss, UCName, ',');
		std::getline(ss, sessionDay, ',');
		std::getline(ss, sessionTimestr, ',');
		sessionTime = stof(sessionTimestr);
		std::getline(ss, sessionDurationstr, ',');
		sessionDuration = stof(sessionDurationstr);
		std::getline(ss, sessionType, '\r');

		if (!temp_uc || temp_uc->getName() != UCName)
		{
			temp_uc = new UC(UCName, sessionName[0] - '0');
			ucMap[UCName] = temp_uc;
		}

		sessionSet.insert(sessionName);

		Session *temp_session = new Session(sessionName, sessionDay, sessionTime, sessionDuration, sessionType);
		temp_uc->addSession(temp_session);
	}
	file.close();
}

/**
 * Complexity: O(n) | 
 * Prints the data parsed into the UC map.
 * Not used anywhere in the program apart from testing.
*/
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

/**
 * Complexity: O(n^2) | 
 * Loads the students to the Binary Search Tree.
 * As there is the need to search for the specific UC and Sessions, the time complexity is higher.
*/
void Manager::load_students()
{

	string line, codeStr, studentName, UCName, sessionName;
	int code;
	Student *temp_student = NULL;

	ifstream file;
	file.open("./data/students_classes.csv");

	if (file.fail())
	{
		std::cout << "Invalid File - Please insert a valid students_classes.csv in the data folder.";
		exit(0);
	}

	getline(file, line);

	while (true)
	{

		if (file.eof())
			break;

		getline(file, line);

		if (line.size() < 5)
			continue;

		istringstream ss(line);

		std::getline(ss, codeStr, ',');
		code = stoi(codeStr);
		std::getline(ss, studentName, ',');
		std::getline(ss, UCName, ',');
		std::getline(ss, sessionName, '\r');

		if (!temp_student || temp_student->getCode() != code)
		{
			temp_student = new Student(studentName, code);
			students.insert(code, temp_student);
		}

		UC *uc = ucMap[UCName];
		std::list<Session *> sessions = uc->find(sessionName);
		for (Session *s : sessions)
		{
			temp_student->addToSchedule(make_pair(uc, s));
			s->addStudent(temp_student);
		}
		uc->editStudentCount(1);
		temp_student->editUCcount(1);
	}
	file.close();
}

/**
 * Complexity: O(n^2) | 
 * Loads the alterations from the changes.csv file and applies it to specific students.
 * Similarly to load_students(), the need to search structure make the time complexity higher.
*/
void Manager::load_alterations()
{
	string line, timestr, action, studentCode, parameter1, parameter2, parameter3;
	time_t time;
	int code;
	Student *temp_student = NULL;

	ifstream file;
	file.open("./data/changes.csv");

	getline(file, line);

	if (line == "")
	{
		file.close();
		ofstream file2;
		file2.open("./data/changes.csv", std::ios::app);
		file2 << "Action,StudentCode,UCName,SessionName" << endl;
		file2.close();
		return;
	}

	while (true)
	{

		if (file.eof())
			break;

		getline(file, line);

		if (line.size() < 5)
			continue;

		istringstream ss(line);

		std::getline(ss, timestr, ',');
		time = stol(timestr);
		std::getline(ss, action, ',');
		std::getline(ss, studentCode, ',');
		code = stoi(studentCode);
		std::getline(ss, parameter1, ',');
		std::getline(ss, parameter2, ',');
		std::getline(ss, parameter3, '\r');

		if (!temp_student || temp_student->getCode() != code)
		{
			temp_student = (Student *)students.search(code);
		}

		if (action == "remove")
			RemoveUC(time, parameter1, temp_student);
		if (action == "add")
			NewClass(time, parameter1, parameter2, temp_student);
		if (action == "swapUC")
			SwapUC(time, parameter1, parameter2, parameter3, temp_student);
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

/**
 * Complexity: O(n) |
 * Prints the data parsed into the Binary Search Tree.
 * Not used anywhere in the program apart from testing.
*/
void Manager::test_students()
{
	print(students.getNode());
}

/**
 * Complexity: O(1)
 * @return The hard-set student limit for a session 
*/
int Manager::getsessionCap() {
	return sessionCap;
}
