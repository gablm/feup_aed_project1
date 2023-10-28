#include "ui.h"

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
		<< "[T] Fast Test Access\n"
		<< "[Q] Exit\n"
		<< "\n"
        << "$> ";
        std::string str;
        std::cin >> str;
        if (str == "Q" || str == "q")
            ClearAndExit();
		if (str == "t" || str == "T") {
			TestFunc();
			continue;
		}	
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

template <typename T>	
size_t len(T iterList)
{
	size_t res = 0;
	for (auto i = iterList.begin(); i != iterList.end(); i++)
		res++;
	return (res);
}

static void read_if_student(BSTnode *node, std::list<void *> &toDisplay, bool (*f)(void *))
{
	if (!node)
		return;
	
	read_if_student(node->left, toDisplay, f);
	if (f(node->content))
		toDisplay.push_back(node->content);
	read_if_student(node->right, toDisplay, f);
}

void UI::TestFunc() {
	
	// Filter only names starting by N
	auto tree_filter = [](void *ptr){ return ((Student *)ptr)->getName()[0] == 'M';};
	// Sort in reverse name alphabetical order
	auto sort_filter = [](const void * a, const void *b) { return ((Student *)a)->getName() > ((Student *)b)->getName(); };
	PrintStudent(tree_filter, sort_filter);
	// Default ordering >> PrintStudent(NULL, NULL)
}

/* Takes two filters, one for search and one for sorting
*/	
void UI::PrintStudent(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *)) {
	system(CLEAR);
	toDisplay.clear();

	std::cout.width(30);
	std::cout << std::left
	<< std::setw(10) << "Code"
	<< std::setw(30) << "Name"
	<< "Number of UCs" << "\n\n";

	// Filter things
	
	if (!tree_filter)
		tree_filter = [](void *ptr){ return ptr != NULL; };
	read_if_student(manager->getStudents().getNode(), toDisplay, tree_filter);

	// Sort things
	if (sort_filter)
		toDisplay.sort(sort_filter);

	for (auto i : toDisplay) {
		Student *a = (Student *)i;
		std::cout << std::left
		<< std::setw(10) << a->getCode()
		<< std::setw(30) << a->getName()
		<< len(a->getSchedule())
		<< "\n";
	}

	std::cout << "\nOption: ";
	std::string option;
	std::cin >> option;
}