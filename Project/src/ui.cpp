#include "headers/ui.h"

UI::UI(Manager *manager) : manager(manager) {}

UI::~UI() {
	delete manager;
}

/**
 * Clears the standard io, deallocates memory and exits
*/
void UI::ClearAndExit() {
	CLEAR;
	delete manager;
	std::exit(0);
}

/**
 * Displays the main menu, and awaits for an input to decide what to do next 
*/
void UI::MainMenu() {

    while (1)
    {
        CLEAR;
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
		<< " [4] Show recent changes\n"
        << "\n"
		<< "[Q] Exit\n"
		<< "\n"
        << "$> ";
        std::string str;
		getline(std::cin, str);
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
				PrintChange();
				break;
			case 4:
				PrintChangeHistory();
		}
    }
}
