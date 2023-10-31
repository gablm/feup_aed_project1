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
			NewClass(option);
			continue;
		}
		if (option.substr(0, 7) == "remove ")
		{
			RemoveUC(option, student);
			continue;
		}
		if (option.substr(0, 7) == "swapUC ")
		{
			SwapUC(option);
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

void UI::NewClass(std::string option)
{
	option = option; // TODO
}

void UI::SwapUC(std::string option)
{
	option = option; // TODO
}
