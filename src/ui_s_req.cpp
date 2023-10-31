#include "headers/ui.h"

void UI::PrintChange()
{
	while (1)
	{
		system(CLEAR);
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
		system(CLEAR);
		std::cout
			<< "Student Inspector - "
			<< student->getCode()
			<< "/" << student->getName()
			<< " Schedule\n";

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

void UI::HelpRequest(std::string error, std::string usage)
{
	std::string option;
	system(CLEAR);
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
				  << "\n add [UCcode] [ClassCode] - add new UC to the schedule in the specified class or swaps the current class if the UC is already present"
				  << "\n remove [UCcode] - Remove an UC from the schedule"
				  << "\n swapUC [old UCCode] [new UCCode] [new ClassCode] - swaps an UC for another in the specified class"
				  << "\n b/B - Go back"
				  << "\n\nNote: The commands and the respective arguments are case-sensitive."
				  << "\n\nPress ENTER to continue...";
	}
	while (std::cin.get() != '\n')
	{
	}
}

// void ChangeClass(){}

void UI::RemoveUC(std::string option, Student *student) // now is working!
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
	for (const auto &pair : student->getSchedule())
	{
		if (pair.first->getName() == up)
		{
			if (!removed) {
				student->editUCcount(-1);
				pair.first->editStudentCount(-1);
				out << "remove," + std::to_string(student->getCode()) + "," + up + ",all" << std::endl;
				removed = true;
			}
			student->removeFromSchedule(pair);
			pair.second->removeStudent(student);
		}
	}
	out.close();
}

void UI::NewClass(std::string option, Student *student)
{
	student = student;
	std::istringstream is(option);
	std::string uccode, classcode;
	is >> uccode >> uccode >> classcode;

	auto ucMap = manager->getUcMap();
	if (uccode.length() < 1 || ucMap.find(uccode) == ucMap.end())
	{
		HelpRequest("Invalid UC code", "add [UCcode] [ClassCode]");
		return;
	}
	auto uc = *manager->getUcMap()[uccode];


	if (classcode == "any"){
		int minCount = 100;
		Session *tempsession;
		for(auto i : uc.getSessionList()){
			if(i->getsize()<minCount){
				minCount=i->getsize();
				tempsession=i;
			}
		}
		classcode = tempsession->getName();
	}


	if (classcode.length() < 1 || uc.find(classcode).size()<1)
	{
		HelpRequest("Invalid Classcode", "add [UCcode] [ClassCode]");
		return;
	}

	auto schedule = student->getSchedule();
	Session *oldClass = nullptr;
	for (auto i: schedule){
		if (i.first->getName() == uc.getName()){
			oldClass=i.second;
		}
	}

	if (oldClass == nullptr && student->getUCcount()==7){
		HelpRequest("Max UC count reached, cannot add a new class before removing another one", "add [UCcode] [ClassCode]");
		return;
	}

	auto newClasses = uc.find(classcode);
	for (auto i : newClasses){
		if(i->getsize()>=manager->getsessionCap()){
			HelpRequest("Class already at maximum capacity", "add [UCcode] [ClassCode]");
			return;
		}
		if(i->getType()!="T" && student->verifyScheduleConflict(i)){
			HelpRequest("Schedule conflict", "add [UCcode] [ClassCode]");
			return;
		}
		
		if(i->getType()!="T" && uc.verifyOccupancyConflict(i,oldClass)){
			HelpRequest("Occupancy conflict: would result in an uneven distribution of students (>5 of a diference between classes)", "add [UCcode] [ClassCode]");
			return;
		}
	}
	std::ofstream out;
	out.open("./data/changes.csv", std::ios::app);

	if(oldClass==nullptr){
		student->editUCcount(+1);
		manager->getUcMap()[uccode]->editStudentCount(+1);
	}
	else{
		oldClass->removeStudent(student);
	}
	out << "add," + std::to_string(student->getCode()) + "," + uc.getName() + "," + classcode + ",all" << std::endl;

	std::pair<UC *, Session *> ucSessionPair;
	ucSessionPair.first=manager->getUcMap()[uccode];
	for (auto i : newClasses){
		ucSessionPair.second=i;
		student->addToSchedule(ucSessionPair);
		i->addStudent(student);
	}
	out.close();
}

void UI::SwapUC(std::string option, Student *student)
{
	student = student;
	option = option; // TODO
}
