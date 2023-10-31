#include "headers/ui.h"

static std::string query;
/**
 * Complexity: O(1) | 
 * Parses user input and returns the appropriate function to search the list 
 * @param option String with the request
 * @return Lambda function
*/
bool (*UI::ses_parse_search_filter(std::string option))(std::string)
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
		auto res = [](std::string a) { return a.find(query) != a.npos; };
		return res;
	}
	if (field == "year")
	{
		auto res = [](std::string a)
		{ return a[0] == query[0]; };
		return res;
	}
	return NULL;
}

/**
 * Complexity: O(1) | 
 * Parses user input and returns the appropriate function to sort the list 
 * @param option String with the request
 * @return Lambda function
*/
bool (*UI::ses_parse_sort_filter(std::string option))(const std::string a, const std::string b)
{
	std::string field;
	std::istringstream is(option);
	is >> field;
	if (is.eof())
		return NULL;
	is >> field;

	if (field == "code") {
		auto res = [](std::string a, std::string b) { return a < b; };
		return res;
	}

	if (field == "rev_code") {
		auto res = [](std::string a, std::string b) { return a > b; };
		return res;
	}

	if (field == "year") {
		auto res = [](std::string a, std::string b) { return a[0] < b[0]; };
		return res;
	}

	if (field == "rev_year") {
		auto res = [](std::string a, std::string b) { return a[0] > b[0]; };		
		return res;
	}

	return NULL;
}

/**
 * Complexity: O(n) | 
 * Goes through the map and checks if the content validates the function passed.
 * If so, this content is added to a list
 * @param toDisplay The list used to store the output shown
 * @param f Function used to check if the element is supposed to be shown
 * @return Lambda function
*/
void UI::read_if_Session(std::list<std::string> &toDisplayStr, bool (*f)(std::string)) {
	std::set<std::string> IndivSessions = manager->getSessionSet();
	for (auto i = IndivSessions.begin(); i != IndivSessions.end(); i++)
	{
		if (f(*i))
			toDisplayStr.push_back(*i);
	}
}

/**
 * Complexity: O(n log n) | 
 * Prints the UC list, according to the results from the two filters.
 * @param tree_filter Lambda function to filter the content
 * @param sort_filter Lambda function to sort the content
 */
void UI::PrintSession(bool (*tree_filter)(std::string), bool (*sort_filter)(const std::string, const std::string))
{
	toDisplayStr.clear();

	if (!tree_filter)
		tree_filter = [](std::string str) { return str != ""; };

	read_if_Session(toDisplayStr, tree_filter);

	if (sort_filter)
		toDisplayStr.sort(sort_filter);

	while (1)
	{
		system(CLEAR);
		std::cout << "Schedules - Session List\n\n"
				  << std::setw(10) << "Code"
				  << "Year"
				  << "\n\n";

		for (auto i : toDisplayStr)
		{
			std::cout << std::left
					  << std::setw(10) << i
					  << " " << i[0]
					  << "\n";
		}
		if (toDisplayStr.empty())
			std::cout << "(No results)\n";

		std::cout << "\nTo see the available commands, use 'help'!"
				  << "\nTo go back to the main menu, use 'b'."
				  << "\n\n$> ";
		std::string option;
		getline(std::cin, option);
		if (option == "b" || option == "B")
			break;
		if (option == "q" || option == "Q") {
			toDisplayStr.clear();
			ClearAndExit();
		}
		if (option.substr(0, 7) == "search ") {
			auto new_filter = ses_parse_search_filter(option);
			if (!new_filter) {
				HelpSession("Invalid field", "search [code|year] [query]");
				continue;
			}
			PrintSession(new_filter, sort_filter);
			break;
		}
		if (option.substr(0, 5) == "sort ") {
			auto new_filter = ses_parse_sort_filter(option);
			if (!new_filter && option != "sort code") {
				HelpSession("Invalid field", "sort [code|rev_code|year|rev_year]");
				continue;
			}
			PrintSession(tree_filter, new_filter);
			break;
		}
		if (option == "reset") {
			PrintSession(NULL, NULL);
			break;
		}
		if (option.substr(0, 6) == "select")
			ShowSession(option);
		else if (option == "help")
			HelpSession("", "");
		else
			HelpSession("Command not found or incomplete", "help - Shows all commands");
	}
}

/**
 * Complexity: O(n^2) | 
 * Shows a Class's schedule based on its code 
 * @param option The string with the full request
*/
void UI::ShowSession(std::string option) {
	system(CLEAR);
	std::istringstream is(option);
	std::string code;
	is >> code >> code;
	if (code.length() < 4)
	{
		HelpSession("Please insert a valid code.", "select [code]");
		return;
	}
	auto sessionSet = manager->getSessionSet();
	if (sessionSet.find(code) == sessionSet.end())
	{
		HelpSession("The Class was not found.", "select [code]");
		return;
	}

	std::list<std::pair<UC*, Session*>> toDisplayMap[7];
	for (auto pair : manager->getUcMap())
	{
		std::list<Session*> sessions = pair.second->find(code);
		for (Session *s : sessions)
		{
			std::istringstream wday(s->getDay());
			std::tm time;
			wday >> std::get_time(&time, "%a");
			toDisplayMap[time.tm_wday].push_back(std::make_pair(pair.second, s));
		}
	}

	while (1)
	{
		std::cout
			<< "Class Inspector - "
			<< code
			<< " Schedule\n";

		bool print = true;
		for (auto i : toDisplayMap) {
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
	}
}

/**
 * Complexity: O(1) |
 * Prints the help menu if both arguments are equal to "".
 * Otherwise, shows an error message.
 * It waits the the user input to proceed.
*/
void UI::HelpSession(std::string error, std::string usage)
{
	system(CLEAR);
	std::cout << "Schedules - Session/Class List\n\n";
	if (error != "" && usage != "") {
		std::cout << "Invalid operation!\n"
				  << "\n Problem: " << error
				  << "\n Usage: " << usage
				  << "\n\nPress ENTER to continue...";
	} else {
		std::cout << "Commands available for the UC page:"
				  << "\n reset - Reset listing to the default sorting and search scheme"
				  << "\n search [code|year] [query] - Search the list (case-sensitive)"
				  << "\n sort [code|rev_code|year|rev_year] - Sort the current list"
				  << "\n select [code] - Show the Sessions's schedule"
				  << "\n b - Go back to the main menu"
				  << "\n\nNote: The commands and the respective arguments are case-sensitive."
				  << "\n\nPress ENTER to continue...";
	}
	while (std::cin.get() != '\n') { }
}
