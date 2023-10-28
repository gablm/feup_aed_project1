#include "ui.h"

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
	//auto tree_filter = [](void *ptr){ return ((Student *)ptr)->getName()[0] == 'M';};
	// Sort in reverse name alphabetical order
	//auto sort_filter = [](const void * a, const void *b) { return ((Student *)a)->getName() > ((Student *)b)->getName(); };
	PrintStudent(NULL, NULL);
	// Default ordering >> PrintStudent(NULL, NULL)
}

std::string query;
bool (*parse_search_filter(std::string option))(void *)
{
	std::string field;
	std::istringstream is(option);
	is >> field >> field;
	getline(is, query);
	query = query.substr(1);

	if (field == "code")
	{
		auto res = [](void * a) { std::string code = std::to_string(((Student *)a)->getCode());
								return code.find(query) != code.npos; };
		return res;
	}
	if (field == "name")
	{
		auto res = [](void * a) { std::string name = ((Student *)a)->getName();
								return name.find(query) != name.npos; };
		return res;
	}
	return NULL;
}

bool (*parse_sort_filter(std::string option))(const void * a, const void *b)
{
	std::string field;
	std::istringstream is(option);
	is >> field >> field;

	if (field == "name")
	{
		auto res = [](const void * a, const void *b) { return ((Student *)a)->getName() < ((Student *)b)->getName(); };
		return res;
	}
	if (field == "rev_name")
	{
		auto res = [](const void * a, const void *b) { return ((Student *)a)->getName() > ((Student *)b)->getName(); };
		return res;
	}
	if (field == "rev_code")
	{
		auto res = [](const void * a, const void *b) { return ((Student *)a)->getCode() > ((Student *)b)->getCode(); };
		return res;
	}
	return NULL;
}

/* Takes two filters, one for search and one for sorting */	
void UI::PrintStudent(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *)) {
	toDisplay.clear();

	// Filter things
	if (!tree_filter)
		tree_filter = [](void *ptr){ return ptr != NULL; };
	read_if_student(manager->getStudents().getNode(), toDisplay, tree_filter);

	// Sort things
	if (sort_filter)
		toDisplay.sort(sort_filter);
	
	while (1) {
		system(CLEAR);
		std::cout.width(30);	
		std::cout << std::left
		<< std::setw(10) << "Code"
		<< std::setw(30) << "Name"
		<< "Number of UCs" << "\n\n";
		
		for (auto i : toDisplay) {
			Student *a = (Student *)i;
			std::cout << std::left
			<< std::setw(10) << a->getCode()
			<< std::setw(30) << a->getName()
			<< len(a->getSchedule())
			<< "\n";
		}
		if (toDisplay.empty())
			std::cout << "(No results)\n\nWarning: Search is case sensitive!\n";

		std::cout << "\nOptions:"
				  << "\n reset - Reset listing to the default sorting and search scheme" 
				  << "\n search [code|name] [query] - Search the current list"
				  << "\n sort [name|rev_name|code|rev_code] - Sort the current list"
				  << "\nNote: The terminal will wait for all the arguments for each operation."
				  << "\n\n$> ";
		std::string option;
		getline(std::cin, option);
		if (option[0] == 'b' || option[0] == 'B' && option.length() == 1)
			break;
		if (option.substr(0, 7) == "search ")
		{
			auto new_filter = parse_search_filter(option);
			if (!new_filter)
			{
				system(CLEAR);
				std::cout << "INVALID OPERATION\n search [name|code] [query]\n";
				usleep(700000);
				continue;
			}
			PrintStudent(new_filter, sort_filter);
			break;
		}
		if (option.substr(0, 5) == "sort ")
		{
			auto new_filter = parse_sort_filter(option);
			if (!new_filter)
			{
				system(CLEAR);
				std::cout << "INVALID OPERATION\n sort [type]\n";
				usleep(700000);
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
	}
}
