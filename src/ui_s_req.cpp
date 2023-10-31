#include "headers/ui.h"
#include <iostream> //remove later, just for debugging

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
        std::cin >> str;
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
		HelpStudent("Please insert a valid code.", "select [code]");
		return;
	}
	void *content = manager->getStudents().search(std::stod(up));
	if (!content)
	{
		HelpStudent("The Student was not found.", "select [code]");
		return;
	}


	Student *student = (Student *)content;
	while (1)
	{
		std::cout
			<< "Student Inspector - "
			<< student->getCode()
			<< "/" << student->getName()
			<< " Schedule\n";

		std::list<std::pair<UC*, Session*>> weekdays[7];
		for (auto pair : student->getSchedule())
		{
			std::istringstream wday(pair.second->getDay());
			std::tm time;
			wday >> std::get_time(&time, "%a");
			weekdays[time.tm_wday].push_back(pair);
		}

		bool print = true;
		for (auto i : weekdays) {
			i.sort([](std::pair<UC*, Session*> a, std::pair<UC*, Session*> b) { return a.second->getTime() < b.second->getTime(); });
			for (auto session : i) {
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
					<< " | Start: "  << std::setfill('0') << std::setw(2) << time / 60 << ":" << std::setw(2) << time % 60
					<< " | Duration: " << std::setw(2) << duration / 60 << ":" << std::setw(2) << duration % 60
					<< std::setfill(' ') << "\n";
			}
			print = true;
		}

		std::cout  << std::left 
            << "\n To see the available commands, use 'help'!"
            << "\n [B] Go back"
            << "\n [Q] Quit"
            << "\n\n"
            << " $>";
                
        std::string option;
		getline(std::cin, option);

        if (option.substr(0, 4) == "add "){
            NewClass(option);
        }
        else if (option.substr(0,7) == "remove "){
            RemoveUC(option, student);
        }
        else if (option.substr(0,7) == "swapUC "){
            SwapUC(option);
        }
        else if (option == "b" || option == "B")
			break;
        else if (option == "q" || option == "Q")
            ClearAndExit();
        else if (option == "help" || option == "h" || option == "H"){
            RequestHelp();
            return;
        }
        system(CLEAR);
	}
}

void UI::RequestHelp()
{
    std::string option;
    system(CLEAR);
    std::cout << "Commands available for the Requests page:"
		<< "\n add [UCcode] [ClassCode] - add new UC to the schedule in the specified class or swaps the current class if the UC is already present"
		<< "\n remove [UCcode] - remove an UC from the schedule"
		<< "\n swapUC [old UCCode] [new UCCode] [new ClassCode] - swaps an UC for another in the specified class"
		<< "\n b/B - Go back"
		<< "\n\nNote: The commands and the respective arguments are case-sensitive."
		<< "\n\nPress ENTER to continue...";
    std::cin >> option;
    RequestDetails(option);
}

//void ChangeClass(){}

void UI::RemoveUC(std::string option, Student *student){ //not working right
    std::istringstream is(option);
	std::string up;
	is >> up;
    if (up.length()!=8){
        std::cout << "Invalid code, try again";
        getline(std::cin, option);
        RemoveUC(option, student);
        return;
    }
    for (const auto& pair : student->getSchedule()){
        if (pair.first->getName()==up){
            student->removeFromSchedule(pair);
        }
    }
}

void UI::NewClass(std::string option){
    option = option; //TODO
}


void UI::SwapUC(std::string option){
    option = option; //TODO
    
}

