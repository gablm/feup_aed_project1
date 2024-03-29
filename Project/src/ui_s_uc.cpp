#include "headers/ui.h"

static std::string query;
/**
 * Parses user input and returns the appropriate function to search the list 
 * @param option String with the request
 * @return Lambda function
 * @note Complexity: O(1)
*/
bool (*UI::uc_parse_search_filter(std::string option))(void *)
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
		auto res = [](void *a) { std::string code = ((UC *)a)->getName();
								return code.find(query) != code.npos;};
		return res;
	}
	if (field == "year")
	{
		auto res = [](void *a) { return ((UC *)a)->getYear() == std::stod(query); };
		return res;
	}
	if (field == "minOccupation")
	{
		auto res = [](void *a)
		{ return ((UC *)a)->getStudentCount() >= std::stod(query); };
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
bool (*UI::uc_parse_sort_filter(std::string option))(const void *a, const void *b)
{
	std::string field;
	std::istringstream is(option);
	is >> field;
	if (is.eof())
		return NULL;
	is >> field;

	if (field == "year")
	{
		auto res = [](const void *a, const void *b)
		{ return ((UC *)a)->getYear() < ((UC *)b)->getYear(); };
		return res;
	}
	if (field == "rev_code")
	{
		auto res = [](const void *a, const void *b)
		{ return ((UC *)a)->getName() > ((UC *)b)->getName(); };
		return res;
	}
	if (field == "occupation")
	{
		auto res = [](const void *a, const void *b)
		{ return ((UC *)a)->getStudentCount() < ((UC *)b)->getStudentCount(); };
		return res;
	}
	if (field == "rev_occupation")
	{
		auto res = [](const void *a, const void *b)
		{ return ((UC *)a)->getStudentCount() > ((UC *)b)->getStudentCount(); };
		return res;
	}
	return NULL;
}

/**
 * Goes through the map and checks if the content validates the function passed.
 * If so, this content is added to a list
 * @param toDisplay The list used to store the output shown
 * @param f Function used to check if the element is supposed to be shown
 * @note Complexity: O(n)
*/
void UI::read_if_UC(std::list<void *> &toDisplay, bool (*f)(void *)) {
	std::map<std::string, UC*> ucmap = manager->getUcMap();
	for (auto i = ucmap.begin(); i != ucmap.end(); i++)
	{
		if (f(i->second))
			toDisplay.push_back(i->second);
	}
}

/**
 * Prints the UC list, according to the results from the two filters.
 * @param tree_filter Lambda function to filter the content
 * @param sort_filter Lambda function to sort the content
 * @note Complexity: O(n log n)
 */
void UI::PrintUC(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *))
{
	toDisplay.clear();

	if (!tree_filter)
		tree_filter = [](void *ptr)
		{ return ptr != NULL; };

	read_if_UC(toDisplay, tree_filter);

	if (sort_filter)
		toDisplay.sort(sort_filter);

	while (1)
	{
		CLEAR;
		std::cout << "Schedules - UC List\n\n"
				  << std::left
				  << std::setw(10) << "Code"
				  << std::setw(5) << "Year"
				  << "  Occupation"
				  << "\n\n";

		for (auto i : toDisplay)
		{
			UC *uc = (UC *)i;
			std::cout << std::left
					  << std::setw(10) << uc->getName()
					  << " " << std::setw(7) << std::left << uc->getYear()
					  << uc->getStudentCount()
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
			auto new_filter = uc_parse_search_filter(option);
			if (!new_filter) {
				HelpUC("Invalid field", "search [code|year|minOccupation] [query]");
				continue;
			}
			PrintUC(new_filter, sort_filter);
			break;
		}
		if (option.substr(0, 5) == "sort ") {
			auto new_filter = uc_parse_sort_filter(option);
			if (!new_filter && option != "sort code") {
				HelpUC("Invalid field", "sort [code|rev_code|year|occupation|rev_occupation]");
				continue;
			}
			PrintUC(tree_filter, new_filter);
			break;
		}
		if (option == "reset") {
			PrintUC(NULL, NULL);
			break;
		}
		if (option.substr(0, 6) == "select")
			ShowUC(option);
		else if (option == "help")
			HelpUC("", "");
		else
			HelpUC("Command not found or incomplete", "help - Shows all commands");
	}
}

/**
 * Shows a UC's schedule based on its code 
 * @param option The string with the full request
 * @note Complexity: O(n^2)
*/
void UI::ShowUC(std::string option) {
	CLEAR;
	std::istringstream is(option);
	std::string code;
	is >> code >> code;
	if (code.length() < 1)
	{
		HelpUC("Please insert a valid code.", "select [code]");
		return;
	}
	auto ucmap = manager->getUcMap();
	auto ucIter = ucmap.find(code);
	if (ucIter == ucmap.end())
	{
		HelpUC("The UC was not found.", "select [code]");
		return;
	}

	UC *uc = ucIter->second;

	while (1)
	{
		std::cout
			<< "UC Inspector - "
			<< uc->getName()
			<< "/Y" << uc->getYear()
			<< " Schedule\n";

		std::list<Session*> weekdays[7];
		for (auto s : uc->getSessionList())
		{
			std::istringstream wday(s->getDay());
			std::tm time;
			wday >> std::get_time(&time, "%a");
			weekdays[time.tm_wday].push_back(s);
		}

		bool print = true;
		for (auto i : weekdays) {
			i.sort([](Session *a, Session* b) { return a->getTime() < b->getTime(); });
			for (auto a : i) {
				if (print)
				{
					std::cout << "\n " << a->getDay() << "\n\n";
					print = false;
				}
				int time = a->getTime() * 60;
				int duration = a->getDuration() * 60;
				std::cout << std::setfill(' ') << std::right
					<< "   Class: " << a->getName()
					<< " | Type: " << std::setw(2) << a->getType()
					<< " | Start: " << std::setfill('0') << std::setw(2) << time / 60 << ":" << std::setw(2) << time % 60
					<< " | Duration: " << std::setw(2) << duration / 60 << ":" << std::setw(2) << duration % 60
					<< " | Occupation: " << a->getSessionCount()
					<< std::setfill(' ') << "\n";
			}
			print = true;
		}
		std::string option;
		std::cout << std::left << "\n [B] Go back\n\n$> ";
		getline(std::cin, option);
		if (option == "b" || option == "B")
			break;
	}
}

/**
 * Prints the help menu if both arguments are equal to "".
 * Otherwise, shows an error message.
 * It waits for user input to proceed.
 * @note Complexity: O(1)
*/
void UI::HelpUC(std::string error, std::string usage)
{
	CLEAR;
	std::cout << "Schedules - UC List\n\n";
	if (error != "" && usage != "") {
		std::cout << "Invalid operation!\n"
				  << "\n Problem: " << error
				  << "\n Usage: " << usage
				  << "\n\nPress ENTER to continue...";
	} else {
		std::cout << "Commands available for the UC page:"
				  << "\n reset - Reset listing to the default sorting and search scheme"
				  << "\n search [code|year|minOccupation] [query] - Search the list (case-sensitive)"
				  << "\n sort [code|rev_code|year|occupation|rev_occupation] - Sort the current list"
				  << "\n select [code] - Show the UC's schedule"
				  << "\n b - Go back to the main menu"
				  << "\n\nNote: The commands and the respective arguments are case-sensitive."
				  << "\n\nPress ENTER to continue...";
	}
	while (std::cin.get() != '\n') { }
}
