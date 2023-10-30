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
		system(CLEAR);
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
            << "\n [1] Change Class"
            << "\n [2] Replace UC"
            << "\n [3] Add UC"
            << "\n [4] Remove UC"
            << "\n [B] Go back"
            << "\n [Q] Quit"
            << "\n\n"
            << " $> ";
                
        std::string option;
		getline(std::cin, option);
		if (option == "b" || option == "B")
			break;
        if (option == "q" || option == "Q")
            ClearAndExit();
        if (option == "0")
            ChangeClass();
        if (option == "1")
            ReplaceUC();
        if (option == "2")
            AddUC();
        if (option == "3")
            RemoveUC();
	}
}

void UI::ChangeClass(){
    
}

void UI::AddUC(){
    
}

void UI::RemoveUC(){
    
}

void UI::ReplaceUC(){
    
}
