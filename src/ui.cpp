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
		char *name = getenv("USER");
        std::cout 
		<< "FEUP - Schedules service\n"
        << "\n"
        << "Welcome " << name << "!\n"
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
		<< "[Q] Exit\n"
		<< "\n"
        << "$> ";
        std::string str;
        std::cin >> str;
        if (str == "Q" || str == "q")
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
			case 3:
				ChangeMenu();
				break;
		}
    }
}

/**
 * Shows the options available to manage UCs / Subjects
*/
void UI::UcMenu()
{
	while (1)
    {
        system(CLEAR);
        std::cout 
		<< "FEUP - Schedules service\n"
		<< "\n"
		<< "Select an option [0-1]:\n"
		<< "\n"
		<< ">> UC management\n"
		<< "\n"
		<< " [0] List\n"
		<< " [1] Search\n"
		<< "\n"
        << "[B] Go back\n"
		<< "\n"
		<< "$> ";
        std::string str;
        std::cin >> str;
		if (str == "b" || str == "B")
			break;
        if (str == "q")
            ClearAndExit();
		if (str.size() > 1)
			continue;
		switch (str[0] - '0')
		{
			case 0:
				break;
			case 1:
				break;
		}
    }
}

/**
 * Shows the options available to manage Students
*/
void UI::StudentMenu()
{
	while (1)
    {
        system(CLEAR);
        std::cout 
		<< "FEUP - Schedules service\n"
		<< "\n"
		<< "Select an option [0-1]:\n"
		<< "\n"
		<< ">> Student management\n"
		<< "\n"
		<< "[0] List\n"
		<< "[1] Search\n"
		<< "\n"
        << "[B] Go back\n"
		<< "\n"
		<< "$> ";
        std::string str;
        std::cin >> str;
		if (str == "b" || str == "B")
			break;
        if (str == "q")
            ClearAndExit();
		if (str.size() > 1)
			continue;
		switch (str[0] - '0')
		{
			case 0:
				break;
			case 1:
				break;
		}
    }
}

/**
 * Shows the options available to manage Classes
*/
void UI::ClassMenu()
{
	while (1)
    {
        system(CLEAR);
        std::cout 
		<< "FEUP - Schedule service\n"
		<< "\n"
		<< "Select an option [0-1]:\n"
		<< "\n"
		<< ">> Class management\n"
		<< "\n"
		<< " [0] List\n"
		<< " [1] Search\n"
		<< "\n"
        << "[B] Go back\n"
		<< "\n"
		<< "$> ";
        std::string str;
        std::cin >> str;
		if (str == "b" || str == "B")
			break;
        if (str == "q")
            ClearAndExit();
				if (str.size() > 1)
			continue;
		switch (str[0] - '0')
		{
			case 0:
				break;
			case 1:
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
