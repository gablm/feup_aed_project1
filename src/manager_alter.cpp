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