#include "headers/manager.h"

/**
 * Constructor for the request class
 * @param time Timestamp in ms since epoch
 * @param type Type of requests [add, remove or switch]
 * @param studentCode Code to the student
 * @param UC1 Code of the first UC involved in the request
 * @param session1 Code of the first session involved in the request
 * @param UC2 Code of the second UC involved in the request, if needed.
 * @param session2 Code of the first session involved in the request, if needed.
*/
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
 * @note Complexity: O(1)
 * @return The request stack 
*/
std::stack<Request*>& Manager::getRequestStack() {
	return requestStack;
}

/**
 * Removes all session for the respective UC.
 * The isn't any verification as removing is not bound by requeriments.
 * @note Complexity: O(n)
 * @param time Timestamp in ms since epoch
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
 * Adds a UC and class or changes the class if a student is already in the UC.
 * Given that this function reads from the changes.csv, we assume it is well formatted and there is no verifications.
 * @note Complexity: O(n^2)
 * @param time Timestamp in ms since epoch
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

/**
 * TODO ????????????????
 * @note Complexity: O(????????????????????????)
 * @param time Timestamp in ms since epoch
 * @param oldUCcode The code of the UC being removed
 * @param newUCcode The code of the UC being added
 * @param classcode The code of the Session being added, can also be any for the lowest occupation class
 * @param student The pointer to the student being edited
*/
void Manager::SwapUC(time_t time, std::string oldUCcode, std::string newUCcode, std::string classcode, Student *student)
{

	UC *oldUC = ucMap[oldUCcode];
	UC *newUC = ucMap[newUCcode];

	if (classcode == "any") {
		int minCount = 100;
		Session *tempsession = NULL;
		for (auto i : newUC->getSessionList()){
			if (i->getsize() < minCount){
				minCount = i->getsize();
				tempsession = i;
			}
		}
		if (tempsession)
			classcode = tempsession->getName();
	}

	ucMap[oldUCcode]->editStudentCount(-1);
	ucMap[newUCcode]->editStudentCount(1);

	std::string oldSessionName;

	for (auto i: student->getSchedule()) {
		if (i.first->getName() == oldUC->getName()) {
			student->removeFromSchedule(i);
			i.second->removeStudent(student);
			oldSessionName = i.second->getName();
		}
	}

	for (auto i : newUC->find(classcode)) {
		student->addToSchedule(std::make_pair(newUC, i));
		i->addStudent(student);
	}

	Request *req = new Request(time, "swapUC", std::to_string(student->getCode()), oldUC->getName(), oldSessionName, newUC->getName(), classcode);
	requestStack.push(req);
}