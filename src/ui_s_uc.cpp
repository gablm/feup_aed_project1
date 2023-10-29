#include "headers/ui.h"

static std::string query;
/**
 * Complexity: O(1)
 * Parses user input and returns the appropriate function to search the list 
 * @param option String with the request
 * @return Lambda function
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
 * Complexity: O(1)
 * Parses user input and returns the appropriate function to sort the list 
 * @param option String with the request
 * @return Lambda function
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
 * Complexity: O(n)
 * Goes through the map and checks if the content validates the function passed.
 * If so, this content is added to a list
 * @param toDisplay The list used to store the output shown
 * @param f Function used to check if the element is supposed to be shown
 * @return Lambda function
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
 * Complexity: O(n^2)
 * Prints the UC list, according to the results from the two filters.
 * @param tree_filter Lambda function to filter the content
 * @param sort_filter Lambda function to sort the content
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
		system(CLEAR);
		std::cout << "Schedules - UC List\n\n"
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
			std::cout << "(No results)\n\nWarning: Search is case sensitive!\n";

		std::cout << "\nOptions:"
				  << "\n reset - Reset listing to the default sorting and search scheme"
				  << "\n search [code|year|minOccupation] [query] - Search the list"
				  << "\n sort [code|rev_code|year|occupation|rev_occupation] - Sort the current list"
				  << "\n select [code] - Show the UC's schedule"
				  << "\n b - Go back"
				  << "\nNote: The terminal will wait for all the arguments for each operation."
				  << "\n\n$> ";
		std::string option;
		getline(std::cin, option);
		if ((option[0] == 'b' || option[0] == 'B') && option.length() == 1)
			break;
		if ((option[0] == 'q' || option[0] == 'Q') && option.length() == 1)
		{
			toDisplay.clear();
			ClearAndExit();
		}
		if (option.substr(0, 7) == "search ")
		{
			auto new_filter = uc_parse_search_filter(option);
			if (!new_filter)
			{
				system(CLEAR);
				std::cout << "INVALID OPERATION\n\n Usage: search [code|year|minOccupation] [query]\n";
				SLEEP(1);
				continue;
			}
			PrintUC(new_filter, sort_filter);
			break;
		}
		if (option.substr(0, 5) == "sort ")
		{
			auto new_filter = uc_parse_sort_filter(option);
			if (!new_filter && option != "sort code")
			{
				system(CLEAR);
				std::cout << "INVALID OPERATION\n\n Usage: sort [code|rev_code|year|occupation|rev_occupation]\n";
				SLEEP(1);
				continue;
			}
			PrintUC(tree_filter, new_filter);
			break;
		}
		if (option == "reset")
		{
			PrintUC(NULL, NULL);
			break;
		}
		if (option.substr(0, 6) == "select")
		{
			ShowUC(option);
		}
	}
}

/**
 * Complexity: O(n log n)
 * Shows a UC's schedule based on its code 
 * @param option The string with the full request
*/
void UI::ShowUC(std::string option) {
	system(CLEAR);
	std::istringstream is(option);
	std::string code;
	is >> code >> code;
	if (code.length() < 1)
	{
		system(CLEAR);
		std::cout << "INVALID OPERATION - INVALID CODE\n\n Usage: select [code]\n";
		SLEEP(1);
		return;
	}
	auto ucmap = manager->getUcMap();
	auto ucIter = ucmap.find(code);
	if (ucIter == ucmap.end())
	{
		system(CLEAR);
		std::cout << "INVALID OPERATION - NOT FOUND\n\n Usage: select [code]\n";
		SLEEP(1);
		return;
	}

	UC *uc = ucIter->second;

	while (1)
	{
		std::cout
			<< "UC Inspector - "
			<< uc->getName()
			<< "/Y" << uc->getYear()
			<< " Schedule\n\n";

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
					std::cout << " " << a->getDay() << "\n\n";
					print = false;
				}
				int time = a->getTime() * 60;
				int duration = a->getDuration() * 60;
				std::cout
					<< "   Class: " << a->getName()
					<< "\n	 Type: " << a->getType()
					<< "\n	 Start time: " << std::right << std::setfill('0') << time / 60 << ":" << std::setw(2) << time % 60
					<< "\n	 Duration: " << std::setw(2) << duration / 60 << ":" << std::setw(2) << duration % 60
					<< "\n	 Allocation: " << a->getSessionCount()
					<< std::setfill(' ') << "\n\n";
			}
			print = true;
		}

		std::string option;
		std::cout << " [B] Go back\n\n$> ";
		getline(std::cin, option);
		if ((option[0] == 'b' || option[0] == 'B') && option.length() == 1)
			break;
	}
}