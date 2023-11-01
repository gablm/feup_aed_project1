#include "headers/manager.h"

/**
 * Complexity: O(n) |
 * Removes all session for the respective UC.
 * The isn't any verification as removing is not bound by requeriments
 * @param UCname The code for the UC to be removed
 * @param student The pointer to the student being edited
*/
void Manager::RemoveUC(std::string UCname, Student *student) {

	if (UCname.length() < 1 || ucMap.find(UCname) == ucMap.end())
		return;

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
		}
	}
}

/**
 * Complexity: O(n^2) |
 * Adds a UC and class or changes the class if a student is already in the UC.
 * Given that this function reads from the changes.csv, we assume it is well formatted and there is no verifications
 * @param uccode The code for the UC to be added/changed
 * @param classcode The code for the class to be added. Can be "any" and the class with the lowest occupation will be attributed.
*/
void Manager::NewClass(std::string uccode, std::string classcode, Student *student) {

	UC *uc = ucMap[uccode];

	if (classcode == "any") {
		int minCount = 100;
		Session *tempsession;
		for (auto i : uc->getSessionList()){
			if (i->getsize() < minCount){
				minCount = i->getsize();
				tempsession = i;
			}
		}
		classcode = tempsession->getName();
	}

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
}