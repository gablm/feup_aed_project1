#include "headers/ui.h"

/**
 * Goes through the binary search tree and checks if the content validates the function passed.
 * If so, this content is added to a list
 * @param node BST node to search
 * @param toDisplay The list used to store all values meant to be shown in the output
 * @param f Function used to check if the element is supposed to be shown
 * @note Complexity: O(n)
*/
void UI::read_if_student(BSTnode *node, std::list<void *> &toDisplay, bool (*f)(void *))
{
	if (!node)
		return;

	read_if_student(node->left, toDisplay, f);
	if (f(node->content))
		toDisplay.push_back(node->content);
	read_if_student(node->right, toDisplay, f);
}

static std::string query;
/**
 * Parses user input and returns the appropriate function to search the list 
 * @param option String with the request
 * @return Lambda function
 * @note Complexity: O(1)
*/
bool (*UI::st_parse_search_filter(std::string option))(void *)
{
	std::string field;
	std::istringstream is(option);
	is >> field;
	if (is.eof())
		return NULL;
	is >> field;
	getline(is, query);
	if (query.length() > 1)
		query = query.substr(1);

	if (field == "code")
	{
		auto res = [](void *a)
		{ std::string code = std::to_string(((Student *)a)->getCode());
								return code.find(query) != code.npos; };
		return res;
	}
	if (field == "name")
	{
		auto res = [](void *a)
		{ std::string name = ((Student *)a)->getName();
								return name.find(query) != name.npos; };
		return res;
	}
	if (field == "minNumUC")
	{
		auto res = [](void *a)
		{ return ((Student *)a)->getUCcount() >= std::stod(query); };
		return res;
	}
	return NULL;
}

/**
 * Parses user input and returns the appropriate function to sort the list 
 * @param option String with the request
 * @return Lambda function
 * @note Complexity: O(1)
*/
bool (*UI::st_parse_sort_filter(std::string option))(const void *a, const void *b)
{
	std::string field;
	std::istringstream is(option);
	is >> field;
	if (is.eof())
		return NULL;
	is >> field;

	if (field == "name") {
		auto res = [](const void *a, const void *b)
		{ return ((Student *)a)->getName() < ((Student *)b)->getName(); };
		return res;
	}

	if (field == "rev_name") {
		auto res = [](const void *a, const void *b)
		{ return ((Student *)a)->getName() > ((Student *)b)->getName(); };
		return res;
	}

	if (field == "code") {
		auto res = [](const void *a, const void *b)
		{ return ((Student *)a)->getCode() < ((Student *)b)->getCode(); };
		return res;
	}

	if (field == "rev_code") {
		auto res = [](const void *a, const void *b)
		{ return ((Student *)a)->getCode() > ((Student *)b)->getCode(); };
		return res;
	}

	if (field == "numUC") {
		auto res = [](const void *a, const void *b)
		{ return ((Student *)a)->getUCcount() < ((Student *)b)->getUCcount(); };
		return res;
	}

	if (field == "rev_numUC") {
		auto res = [](const void *a, const void *b)
		{ return ((Student *)a)->getUCcount() > ((Student *)b)->getUCcount(); };
		return res;
	}
	
	return NULL;
}

/**
 * Prints the student list, according to the results from the two filters.
 * @param tree_filter Lambda function to filter the content
 * @param sort_filter Lambda function to sort the content
 * @note Complexity: O(n log n)
 */
void UI::PrintStudent(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *))
{
	toDisplay.clear();

	// Filter things
	if (!tree_filter)
		tree_filter = [](void *ptr)
		{ return ptr != NULL; };
	read_if_student(manager->getStudents().getNode(), toDisplay, tree_filter);

	// Sort things
	if (sort_filter)
		toDisplay.sort(sort_filter);

	while (1)
	{
		CLEAR;
		std::cout << "Schedules - Student List\n\n"
				  << std::left
				  << std::setw(10) << "Code"
				  << std::setw(11) << "Uc number"
				  << "Name"
				  << "\n\n";

		for (auto i : toDisplay)
		{
			Student *a = (Student *)i;
			std::cout << std::left
					  << std::setw(10) << a->getCode()
					  << "    " << std::setw(6) << std::left << a->getUCcount()
					  << a->getName()
					  << "\n";
		}
		if (toDisplay.empty())
			std::cout << "(No results)\n";

		std::cout << "\nTo see the available commands, use 'help'!"
				  << "\nTo go back to the main menu, use 'b'."
				  << "\n\n$> ";
		std::string option;
		getline(std::cin, option);
		if (option == "b" || option == "B")
			break;
		if (option == "q" || option == "Q") {
			toDisplay.clear();
			ClearAndExit();
		}
		if (option.substr(0, 7) == "search ") {
			auto new_filter = st_parse_search_filter(option);
			if (!new_filter) {
				HelpStudent("Invalid field", "search [code|name|minNumUC] [query]");
				continue;
			}
			PrintStudent(new_filter, sort_filter);
			break;
		}
		if (option.substr(0, 5) == "sort ") {
			auto new_filter = st_parse_sort_filter(option);
			if (!new_filter) {
				HelpStudent("Invalid field", "sort [name|rev_name|code|rev_code|numUC|rev_numUC]");
				continue;
			}
			PrintStudent(tree_filter, new_filter);
			break;
		}
		if (option == "reset") {
			PrintStudent(NULL, NULL);
			break;
		}
		if (option.substr(0, 7) == "select ")
			ShowStudent(option);
		else if (option.substr(0, 5) == "edit " && option.length() > 5)
			RequestDetails(option.substr(5));
		else if (option == "help")
			HelpStudent("", "");
		else
			HelpStudent("Command not found or incomplete", "help - Shows all commands");
	}
}

/**
 * Shows a student's schedule based on its code 
 * @param option The string with the full request
 * @note Complexity: O(n^2)
*/
void UI::ShowStudent(std::string option)
{
	std::istringstream is(option);
	std::string up;
	is >> up >> up;
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
		CLEAR;
		std::cout
			<< "Student Inspector - "
			<< student->getCode()
			<< "/" << student->getName()
			<< " Schedule (View mode)\n";

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

		std::string option;
		std::cout  << std::left << "\n [B] Go back\n\n$> ";
		getline(std::cin, option);
		if (option == "b" || option == "B")
			break;
		if (option == "q" || option == "Q")
            ClearAndExit();
	}
}

/**
 * Prints the help menu if both arguments are equal to "".
 * Otherwise, shows an error message.
 * It waits for user input to proceed.
 * @note Complexity: O(1)
*/
void UI::HelpStudent(std::string error, std::string usage)
{
	CLEAR;
	std::cout << "Schedules - Student List\n\n";
	if (error != "" && usage != "") {
		std::cout << "Invalid operation!\n"
				  << "\n Problem: " << error
				  << "\n Usage: " << usage
				  << "\n\nPress ENTER to continue...";
	} else {
		std::cout << "Commands available for the Student page:"
				  << "\n reset - Reset listing to the default sorting and search scheme"
				  << "\n search [code|name|minNumUC] [query] - Search the list"
				  << "\n sort [name|rev_name|code|rev_code|numUC|rev_numUC] - Sort the current list"
				  << "\n select [code] - Show the student's schedule"
				  << "\n edit [code] - Change a student's schedule"
				  << "\n b - Go back"
				  << "\n\nNote: The commands and the respective arguments are case-sensitive."
				  << "\n\nPress ENTER to continue...";
	}
	while (std::cin.get() != '\n') { }
}
