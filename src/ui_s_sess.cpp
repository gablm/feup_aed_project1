#include "headers/ui.h"

static std::string query;
/**
 * Complexity: O(1)
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
 * Complexity: O(1)
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
 * Complexity: O(n)
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
 * Complexity: O(n^2)
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
		if ((option[0] == 'b' || option[0] == 'B') && option.length() == 1)
			break;
		if ((option[0] == 'q' || option[0] == 'Q') && option.length() == 1) {
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
		if (option == "help")
			HelpSession("", "");
	}
}

/**
 * Complexity: O(n log n)
 * Shows a Class's schedule based on its code 
 * @param option The string with the full request
*/
void UI::ShowSession(std::string option) {

}

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
