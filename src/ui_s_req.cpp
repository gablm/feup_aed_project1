#include "headers/ui.h"

/**
 * Prints the menu asking for the code of the student being altered.
 * @note Complexity: O(1)
*/
void UI::PrintChange()
{
	while (1)
	{
		CLEAR;
		std::cout
			<< "FEUP - Schedule service\n"
			<< "\n"
			<< "You are now starting a alteration request.\n"
			<< "\n"
			<< "[B] Go back and cancel\n"
			<< "[Q] Quit\n"
			<< "\n"
			<< ">> Student Code:\n"
			<< "$> ";
		std::string str;
		getline(std::cin, str);
		if (str == "b" || str == "B")
			break;
		if (str == "q" || str == "Q")
			ClearAndExit();
		RequestDetails(str);
	}
}

/**
 * Prints the student's schedule and awaits for the user input
 * @param option Student code
 * @note Complexity: O(n^2)
*/
void UI::RequestDetails(std::string option)
{
	std::istringstream is(option);
	std::string up;
	is >> up;
	if (up.length() != 9)
	{
		HelpRequest("Please insert a valid code.", "[code]");
		return;
	}

	void *content = manager->getStudents().search(std::stod(up));
	if (!content)
	{
		HelpRequest("The Student was not found.", "[code]");
		return;
	}

	Student *student = (Student *)content;

	while (1)
	{
		CLEAR;
		std::cout
			<< "Student Inspector - "
			<< student->getCode()
			<< "/" << student->getName()
			<< " Schedule (Edit mode)\n";

		std::list<std::pair<UC *, Session *>> weekdays[7];
		for (auto pair : student->getSchedule())
		{
			std::istringstream wday(pair.second->getDay());
			std::tm time;
			wday >> std::get_time(&time, "%a");
			weekdays[time.tm_wday].push_back(pair);
		}

		bool print = true;
		for (auto i : weekdays)
		{
			i.sort([](std::pair<UC *, Session *> a, std::pair<UC *, Session *> b)
				   { return a.second->getTime() < b.second->getTime(); });
			for (auto session : i)
			{
				Session *a = session.second;
				if (print)
				{
					std::cout << "\n " << a->getDay() << "\n\n";
					print = false;
				}
				int time = a->getTime() * 60;
				int duration = a->getDuration() * 60;
				std::cout << std::setfill(' ') << std::right
						  << "   UC: " << session.first->getName()
						  << " | Class: " << a->getName()
						  << " | Type: " << std::setw(2) << a->getType()
						  << " | Start: " << std::setfill('0') << std::setw(2) << time / 60 << ":" << std::setw(2) << time % 60
						  << " | Duration: " << std::setw(2) << duration / 60 << ":" << std::setw(2) << duration % 60
						  << std::setfill(' ') << "\n";
			}
			print = true;
		}

		std::cout << std::left
				  << "\n To see the available commands, use 'help'!"

				  << "\n [B] Go back"
				  << "\n [Q] Quit"
				  << "\n\n"
				  << " $> ";

		std::string option;
		getline(std::cin, option);

		if (option.substr(0, 4) == "add ")
		{
			NewClass(option, student);
			continue;
		}
		if (option.substr(0, 7) == "remove ")
		{
			RemoveUC(option, student);
			continue;
		}
		if (option.substr(0, 7) == "swapUC ")
		{
			SwapUC(option, student);
			continue;
		}
		if (option == "undo")
		{
			PrintChangeHistory();
			continue;
		}
		if (option == "b" || option == "B")
			break;
		if (option == "q" || option == "Q")
			ClearAndExit();
		else if (option == "help" || option == "h" || option == "H")
			HelpRequest("", "");
		else
			HelpRequest("Command not found or incomplete", "help - Shows all commands");
	}
}

/**
 * Prints the help menu if both arguments are equal to "".
 * Otherwise, shows an error message.
 * It waits for user input to proceed.
 * @note Complexity: O(1)
*/
void UI::HelpRequest(std::string error, std::string usage)
{
	std::string option;
	CLEAR;
	if (error != "" && usage != "")
	{
		std::cout << "Invalid operation!\n"
				  << "\n Problem: " << error
				  << "\n Usage: " << usage
				  << "\n\nPress ENTER to continue...";
	}
	else
	{
		std::cout << "Commands available for the Requests page:"
				  << "\n add [UCcode] [ClassCode/\"any\"] - Add a new UC to the schedule in a specified class or swap the current class if the UC is already in the schedule"
				  << "\n remove [UCcode] - Remove an UC from the schedule"
				  << "\n swapUC [old UCCode] [new UCCode] [new ClassCode/\"any\"] - Swap an UC for another in the specified class"
				  << "\n undo - Go to the Change History page"
				  << "\n b/B - Go back"
				  << "\n\nNote: The commands and the respective arguments are case-sensitive."
				  << "\n\nPress ENTER to continue...";
	}
	while (std::cin.get() != '\n')
	{
	}
}

/**
 * Removes all session for the respective UC.
 * The isn't any verification as removing is not bound by requirements apart from validating the UC code.
 * @param option The command inputted by the user.
 * @param student The pointer to the student being edited
 * @note Complexity: O(n)
*/
void UI::RemoveUC(std::string option, Student *student)
{ 
	std::istringstream is(option);
	std::string up;
	is >> up >> up;
	auto ucMap = manager->getUcMap();
	if (up.length() < 1 || ucMap.find(up) == ucMap.end())
	{
		HelpRequest("Invalid UC code", "removeUC [UCcode]");
		return;
	}

	bool removed = false;
	std::ofstream out;
	out.open("./data/changes.csv", std::ios::app);
	std::string session = "";
	for (const auto &pair : student->getSchedule())
	{
		if (pair.first->getName() == up)
		{
			if (!removed) {
				student->editUCcount(-1);
				pair.first->editStudentCount(-1);
				std::string stCode = std::to_string(student->getCode());
				out << std::time(nullptr) << ",remove," + stCode + "," + up + ",all" << std::endl;
				log("Removed all classes for " + up + " of " + stCode);
				Request *req = new Request(std::time(nullptr), "remove", std::to_string(student->getCode()), up, session, "", "");
				manager->getRequestStack().push(req);
				removed = true;
			}
			student->removeFromSchedule(pair);
			pair.second->removeStudent(student);
			session = pair.second->getName();
		}
	}
	out.close();
}

/**
 * Complexity: O(n^2) | The "n"s used here are very small and so a higher complexity only results in a negligible running time increase.
 * Adds a UC and class or changes the class if a student is already in the UC.
 * There are various checks in place: Max allocation of 25, max allocation difference of 4 and schedule conflicts
 * The allocation difference is not verified if the session to enter is the one with the lowest occupation.
 * That way, the UC will return to a balanced state after a while if not already in such state.
 * @param option The command inputted by the user.
 * @param student The pointer to the student being edited
 * @note Complexity: O(n^2)
 * The "n"s used here are very small and so a higher complexity only results in a negligible running time increase.
 */
void UI::NewClass(std::string option, Student *student) {

	std::istringstream is(option);
	std::string uccode, classcode;
	is >> uccode >> uccode >> classcode;

	auto ucMap = manager->getUcMap();
	if (uccode.length() < 1 || ucMap.find(uccode) == ucMap.end())
	{
		HelpRequest("Invalid UC code", "add [UCcode] [ClassCode]");
		return;
	}

	UC *uc = manager->getUcMap()[uccode];

	if (classcode == "any") {
        int minCount = 100;
        Session *tempsession = nullptr;
        for (auto i : uc->getSessionList()){
            if (i->getsize() < minCount && !student->verifyScheduleConflict(uc->getName(), i)){
                minCount = i->getsize();
                tempsession = i;
            }
        }
        if (tempsession == nullptr){
            HelpRequest("No available classes for this UC", "add [UCcode] [ClassCode]");
            return;
        }
        classcode = tempsession->getName();
    }

	if (classcode.length() < 1 || uc->find(classcode).size() < 1)
	{
		HelpRequest("Invalid Classcode", "add [UCcode] [ClassCode]");
		return;
	}

	auto schedule = student->getSchedule();
	Session *oldClass = NULL;
	for (auto i: schedule) {
		if (i.first->getName() == uc->getName()){
			oldClass = i.second;
		}
	}

	if (!oldClass && student->getUCcount() == 7){
		HelpRequest("Max UC count reached, cannot add a new class before removing another one", "add [UCcode] [ClassCode]");
		return;
	}

	auto newClasses = uc->find(classcode);

	for (auto i : newClasses) {

		if(i->getsize() >= manager->getsessionCap()) {
			HelpRequest("Class already at maximum capacity", "add [UCcode] [ClassCode]");
			return;
		}
		if (i->getType() != "T" && student->verifyScheduleConflict(uc->getName(), i)) {
			HelpRequest("Schedule conflict", "add [UCcode] [ClassCode]");
			return;
		}
		
		if(i->getType() != "T" && uc->verifyOccupancyConflict(i, oldClass)){
			HelpRequest("Occupancy conflict: would result in an uneven distribution of students (difference > 4 between classes)", "add [UCcode] [ClassCode]");
			return;
		}
	}
	        
	std::ofstream out;
	out.open("./data/changes.csv", std::ios::app);

	if (!oldClass) {
		student->editUCcount(1);
		ucMap[uccode]->editStudentCount(1);
	}
	else {
		oldClass->removeStudent(student);
	}

	std::string codeStr = std::to_string(student->getCode());
	out << std::time(nullptr) << ",add," + codeStr + "," + uc->getName() + "," + classcode << std::endl;
	
	log("Added pair <" + uc->getName() + ", " + classcode + "> to " + codeStr);

	Request *req = new Request(std::time(nullptr), "add", std::to_string(student->getCode()), uccode, classcode, "", oldClass != NULL ? oldClass->getName() : "");
	manager->getRequestStack().push(req);

	for (auto i: schedule) {
		if (i.first->getName() == uc->getName()) {
			student->removeFromSchedule(i);
			i.second->removeStudent(student);
		}
	}

	for (auto i : newClasses) {
		student->addToSchedule(std::make_pair(uc, i));
		i->addStudent(student);
	}
	out.close();
}

/**
 * Complexity: O(n^2) | The "n"s used here are very small and so a higher complexity only results in a negligible running time increase.
 * Removes an UC from the student's schedule and adds a new one in the specified class.
 * There are various checks in place: Max allocation of 25, max allocation difference of 4 and schedule conflicts
 * The allocation difference is not verified if the session to enter is the one with the lowest occupation.
 * That way, the new UC will return to a balanced state after a while if not already in such state.
 * @param option The command inputted by the user.
 * @param student The pointer to the student being edited
 */
void UI::SwapUC(std::string option, Student *student)
{
	std::istringstream is(option);
	std::string oldUCcode, newUCcode, classcode;
	is >> oldUCcode >> oldUCcode >> newUCcode >> classcode;

	auto ucMap = manager->getUcMap();
	if (newUCcode.length() < 1 || ucMap.find(newUCcode) == ucMap.end())
	{
		HelpRequest("Invalid UC code for old UC", "swapUC [old UCCode] [new UCCode] [new ClassCode]");
		return;
	}
	if (oldUCcode.length() < 1 || ucMap.find(oldUCcode) == ucMap.end())
	{
		HelpRequest("Invalid UC code for new UC", "swapUC [old UCCode] [new UCCode] [new ClassCode]");
		return;
	}

	UC *oldUC = manager->getUcMap()[oldUCcode];
	UC *newUC = manager->getUcMap()[newUCcode];

	if (classcode == "any") {
        int minCount = 100;
        Session *tempsession;
        for (auto i : newUC->getSessionList()){
            if (i->getsize() < minCount && !student->verifyScheduleConflict(newUC->getName(), i)){
                minCount = i->getsize();
                tempsession = i;
            }
		}
        if (tempsession == nullptr){
            HelpRequest("No available classes for this UC", "swapUC [old UCCode] [new UCCode] [new ClassCode]");
            return;
        }
        classcode = tempsession->getName();
    }

	auto schedule = student->getSchedule();
	bool foundOld = false;
	bool foundNew = false;
	for (auto i: schedule) {
		if (i.first->getName() == newUC->getName()){
			foundNew=true;
		}
		if (i.first->getName() == oldUC->getName()){
			foundOld=true;
		}
	}

	if (foundNew){
		HelpRequest("Already in selected new UC", "swapUC [old UCCode] [new UCCode] [new ClassCode]");
		return;
	}
	if (!foundOld){
		HelpRequest("Not part of selected old UC", "swapUC [old UCCode] [new UCCode] [new ClassCode]");
		return;
	}

	auto newClasses = newUC->find(classcode);
	for (auto i : newClasses) {

		if(i->getsize() >= manager->getsessionCap()) {
			HelpRequest("Class already at maximum capacity", "swapUC [old UCCode] [new UCCode] [new ClassCode]");
			return;
		}
		if (i->getType() != "T" && student->verifyScheduleConflict(newUC->getName(), i)) {
			HelpRequest("Schedule conflict", "swapUC [old UCCode] [new UCCode] [new ClassCode]");
			return;
		}
		
		if(i->getType() != "T" && newUC->verifyOccupancyConflict(i, nullptr)){
			HelpRequest("Occupancy conflict: would result in an uneven distribution of students (difference > 4 between classes)", "swapUC [old UCCode] [new UCCode] [new ClassCode]");
			return;
		}
	}

	std::ofstream out;
	out.open("./data/changes.csv", std::ios::app);

	ucMap[oldUCcode]->editStudentCount(-1);
	ucMap[newUCcode]->editStudentCount(1);

	std::string oldSessionName;

	for (auto i: schedule) {
		if (i.first->getName() == oldUC->getName()) {
			student->removeFromSchedule(i);
			i.second->removeStudent(student);
			oldSessionName = i.second->getName();
		}
	}

	for (auto i : newClasses) {
		student->addToSchedule(std::make_pair(newUC, i));
		i->addStudent(student);

	}

	std::string codeStr = std::to_string(student->getCode());
	out << std::time(nullptr) << ",swapUC," + codeStr + "," + oldUC->getName() + "," + newUC->getName() + "," + classcode +"\n"<< std::endl;

	log("Swapped UC from pair <" + oldUC->getName() + ", " + oldSessionName +"> to <" + newUC->getName() + ", " + classcode + "> for " + codeStr);

	out.close();

	Request *req = new Request(std::time(nullptr), "swapUC", std::to_string(student->getCode()), oldUC->getName(), oldSessionName, newUC->getName(), classcode);
	manager->getRequestStack().push(req);
}

/**
 * Logs the operations made by the user using the UI.
 * Changing the contents of this file won't affect the system.
 * @note Complexity: O(1)
*/
void UI::log(std::string action) 
{
	std::ofstream out;
	out.open("./changes.log", std::ios::app);
	time_t timenow = std::time(nullptr);
	out << "[" << std::put_time(std::localtime(&timenow), "%d/%m/%Y %T") << "] " << action << std::endl;
	out.close();
}
