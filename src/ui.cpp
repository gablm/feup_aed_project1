#include "ui.h"

/**
 * Clear the standard io and exits
*/
void UI::ClearAndExit() {
	system(CLEAR);
	exit(0);
}

/**
 * Displays the main menu, and awaits for an input to decide what to do next 
*/
void UI::MainMenu() {

    while (1)
    {
        system(CLEAR);
        std::cout << "University of Porto - Faculty of Engineering\n"
        << "\n"
        << "Welcome to the Schedules service!\n"
        << "Select an option [0-3]:\n"
        << "\n"
        << ">> List and search\n"
        << "\n"
        << "[0] Students\n"
        << "[1] UCs\n"
        << "[2] Classes\n"
        << "\n"
        << ">> Edit data\n"
        << "\n"
        << "[3] Change Student schedule\n"
        << "\n"
        << "Option: ";
        std::string str;
        std::cin >> str;
        if (str == "q")
            ClearAndExit();
		if (str.size() > 1)
			continue;
		switch (str[0] - '0')
		{
			case 0:
				StudentMenu();
				break;
			case 1:
				UcMenu();
				break;
			case 2:
				ClassMenu();
				break;
		}
    }
}

void UI::UcMenu()
{
	while (1)
    {
        system(CLEAR);
        std::cout << "UC page\n"
        << "Option: ";
        std::string str;
        std::cin >> str;
		if (str == "b")
			break;
        if (str == "q")
            ClearAndExit();
    }
}

void UI::StudentMenu()
{
	while (1)
    {
        system(CLEAR);
        std::cout << "Student page\n"
        << "Option: ";
        std::string str;
        std::cin >> str;
		if (str == "b")
			break;
        if (str == "q")
            ClearAndExit();
    }
}

void UI::ClassMenu()
{
	while (1)
    {
        system(CLEAR);
        std::cout << "Class page\n"
        << "Option: ";
        std::string str;
        std::cin >> str;
		if (str == "b")
			break;
        if (str == "q")
            ClearAndExit();
    }
}
