#include "headers/ui.h"

size_t ucAmmount(std::vector<std::pair<UC *, Session *>> iterList)
{
	size_t res = 0;
	UC *uc = NULL;
	for (auto i = iterList.begin(); i != iterList.end(); i++)
	{
		if (!uc)
			uc = i->first;
		if (uc->getName() != i->first->getName())
		{
			uc = i->first;
			res++;
		}
	}
	if (uc)
		res++;
	return (res);
}

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
	if (field == "minUC")
	{
		auto res = [](void *a)
		{ auto name = ((Student *)a)->getSchedule();
								return ucAmmount(name) >= std::stod(query); };
		return res;
	}
	return NULL;
}

bool (*UI::st_parse_sort_filter(std::string option))(const void *a, const void *b)
{
	std::string field;
	std::istringstream is(option);
	is >> field;
	if (is.eof())
		return NULL;
	is >> field;

	if (field == "name")
	{
		auto res = [](const void *a, const void *b)
		{ return ((Student *)a)->getName() < ((Student *)b)->getName(); };
		return res;
	}
	if (field == "rev_name")
	{
		auto res = [](const void *a, const void *b)
		{ return ((Student *)a)->getName() > ((Student *)b)->getName(); };
		return res;
	}
	if (field == "rev_code")
	{
		auto res = [](const void *a, const void *b)
		{ return ((Student *)a)->getCode() > ((Student *)b)->getCode(); };
		return res;
	}
	if (field == "minUC")
	{
		auto res = [](const void *a, const void *b)
		{ return ucAmmount(((Student *)a)->getSchedule()) < ucAmmount(((Student *)b)->getSchedule()); };
		return res;
	}
	if (field == "rev_minUC")
	{
		auto res = [](const void *a, const void *b)
		{ return ucAmmount(((Student *)a)->getSchedule()) > ucAmmount(((Student *)b)->getSchedule()); };
		return res;
	}
	return NULL;
}

/* Takes two filters, one for search and one for sorting */
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
		system(CLEAR);
		std::cout << "Schedules - Student List\n\n"
				  << std::setw(10) << "Code"
				  << std::setw(11) << "Uc number"
				  << "Name"
				  << "\n\n";

		for (auto i : toDisplay)
		{
			Student *a = (Student *)i;
			std::cout << std::left
					  << std::setw(10) << a->getCode()
					  << "    " << std::setw(6) << std::left << ucAmmount(a->getSchedule())
					  << a->getName()
					  << "\n";
		}
		if (toDisplay.empty())
			std::cout << "(No results)\n\nWarning: Search is case sensitive!\n";

		std::cout << "\nOptions:"
				  << "\n reset - Reset listing to the default sorting and search scheme"
				  << "\n search [code|name|minUC] [query] - Search the list"
				  << "\n sort [name|rev_name|code|rev_code|minUC|rev_minUC] - Sort the current list"
				  << "\n select [code] - Show the student's schedule"
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
			auto new_filter = st_parse_search_filter(option);
			if (!new_filter)
			{
				system(CLEAR);
				std::cout << "INVALID OPERATION\n\n Usage: search [code|name|minUC] [query]\n";
				SLEEP(1);
				continue;
			}
			PrintStudent(new_filter, sort_filter);
			break;
		}
		if (option.substr(0, 5) == "sort " && option != "sort code")
		{
			auto new_filter = st_parse_sort_filter(option);
			if (!new_filter)
			{
				system(CLEAR);
				std::cout << "INVALID OPERATION\n\n Usage: sort [name|rev_name|code|rev_code|minUC|rev_minUC]\n";
				SLEEP(1);
				continue;
			}
			PrintStudent(tree_filter, new_filter);
			break;
		}
		if (option == "reset")
		{
			PrintStudent(NULL, NULL);
			break;
		}
		if (option.substr(0, 6) == "select")
		{
			ShowStudent(option);
		}
	}
}

void UI::ShowStudent(std::string option)
{
	system(CLEAR);
	std::istringstream is(option);
	std::string up;
	is >> up >> up;
	if (up.length() != 9)
	{
		system(CLEAR);
		std::cout << "INVALID OPERATION - INVALID CODE\n\n Usage: select [code]\n";
		SLEEP(1);
		return;
	}
	void *content = manager->getStudents().search(std::stod(up));
	if (!content)
	{
		system(CLEAR);
		std::cout << "INVALID OPERATION - NOT FOUND\n\n Usage: select [code]\n";
		SLEEP(1);
		return;
	}

	Student *student = (Student *)content;

	while (1)
	{
		std::cout
			<< "Student Inspector - "
			<< student->getCode()
			<< "/" << student->getName()
			<< " Schedule\n\n";

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
					std::cout << " " << a->getDay() << "\n\n";
					print = false;
				}
				int time = a->getTime() * 60;
				int duration = a->getDuration() * 60;
				std::cout
					<< "   UC: " << session.first->getName()
					<< " | Class: " << a->getName()
					<< "\n	 Type: " << a->getType()
					<< "\n	 Start time: " << std::right << std::setfill('0') << time / 60 << ":" << std::setw(2) << time % 60
					<< "\n	 Duration: " << std::setw(2) << duration / 60 << ":" << std::setw(2) << duration % 60
					<< std::setfill(' ') << "\n\n";
			}
			print = true;
		}

		std::string option;
		std::cout << " [B] Go back\n\n$> ";
		getline(std::cin, option);
		if (option[0] == 'b' || option[0] == 'B' && option.length() == 1)
			break;
	}
}
