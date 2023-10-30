#include "headers/ui.h"

UI::UI(Manager *manager) : manager(manager) {}

UI::~UI() {
	delete manager;
}

/**
 * Clears the standard io, dealocates memory and exits
*/
void UI::ClearAndExit() {
	system(CLEAR);
	delete manager;
	std::exit(0);
}

/**
 * Displays the main menu, and awaits for an input to decide what to do next 
*/
void UI::MainMenu() {

    while (1)
    {
        system(CLEAR);
        std::cout 
		<< "FEUP - Schedules service\n"
        << "\n"
        #ifdef _linux__
        << "Welcome " << getenv("USER") << "!\n"
        #else
        << "Welcome!\n"
        #endif
		<< "Select an option [0-3]:\n"
        << "\n"
        << ">> List and search\n"
        << "\n"
        << " [0] Students\n"
        << " [1] UCs\n"
        << " [2] Classes\n"
        << "\n"
        << ">> Edit data\n"
        << "\n"
        << " [3] Change Student schedule\n"
        << "\n"
		<< "[T] Fast Test Access\n"
		<< "[Q] Exit\n"
		<< "\n"
        << "$> ";
        std::string str;
        std::cin >> str;
        if (str == "Q" || str == "q")
            ClearAndExit();
		if (str == "t" || str == "T") {
			continue;
		}	
		if (str.size() > 1)
			continue;
		switch (str[0] - '0')
		{
			case 0:
				PrintStudent(NULL, NULL);
				break;
			case 1:
				PrintUC(NULL, NULL);
				break;
			case 2:
				PrintSession(NULL, NULL);
				break;
			case 3:
				ChangeMenu();
				break;
		}
    }
}

void UI::ChangeMenu()
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
		<< ">> Name:\n"
		<< "$> ";
        std::string str;
        std::cin >> str;
		if (str == "b" || str == "B")
			break;
        if (str == "q" || str == "Q")
            ClearAndExit();
		if (str.size() > 1)
			continue;
    }
}
