#include "headers/manager.h"

Request::Request(time_t time, std::string type, std::string studentCode, std::string UC1, std::string session1, std::string UC2, std::string session2)
{
	this->timestamp = time;
	this->type = type;
	this->studentCode = studentCode;
	this->UC1 = UC1;
	this->session1 = session1;
	this->UC2 = UC2;
	this->session2 = session2;
}

/**
 * Complexity: O(1)
 * @return The request stack 
*/
std::stack<Request*>& Manager::getRequestStack() {
	return requestStack;
}

/**
 * Complexity: O(n) |
 * Removes all session for the respective UC.
 * The isn't any verification as removing is not bound by requeriments
 * @param UCname The code for the UC to be removed
 * @param student The pointer to the student being edited
*/
void Manager::RemoveUC(time_t time, std::string UCname, Student *student) {

	if (UCname.length() < 1 || ucMap.find(UCname) == ucMap.end())
		return;

	std::string session = "";
	bool removed = false;
	for (const auto &pair : student->getSchedule())
	{
		if (pair.first->getName() == UCname)
		{
			if (!removed) {
				student->editUCcount(-1);
				pair.first->editStudentCount(-1);
				removed = true;
			}
			student->removeFromSchedule(pair);
			pair.second->removeStudent(student);
			session = pair.second->getName();
		}
	}

	Request *req = new Request(time, "remove", std::to_string(student->getCode()), UCname, session, "", "");
	requestStack.push(req);
}

/**
 * Complexity: O(n^2) |
 * Adds a UC and class or changes the class if a student is already in the UC.
 * Given that this function reads from the changes.csv, we assume it is well formatted and there is no verifications
 * @param uccode The code for the UC to be added/changed
 * @param classcode The code for the class to be added. Can be "any" and the class with the lowest occupation will be attributed.
 * @param student The pointer to the student being edit
*/
void Manager::NewClass(time_t time, std::string uccode, std::string classcode, Student *student) {

	UC *uc = ucMap[uccode];

	auto schedule = student->getSchedule();
	Session *oldClass = NULL;
	for (auto i: schedule) {
		if (i.first->getName() == uc->getName()){
			oldClass = i.second;
		}
	}

	auto newClasses = uc->find(classcode);

	if (!oldClass) {
		student->editUCcount(1);
		ucMap[uccode]->editStudentCount(1);
	}
	else {
		oldClass->removeStudent(student);
	}

	for (auto i: schedule) {
		if (i.first->getName() == uc->getName()) {
			student->removeFromSchedule(i);
		}
	}

	for (auto i : newClasses) {
		student->addToSchedule(std::make_pair(uc, i));
		i->addStudent(student);
	}

	Request *req = new Request(time, "add", std::to_string(student->getCode()), uccode, classcode, "", oldClass != NULL ? oldClass->getName() : "");
	requestStack.push(req);
}