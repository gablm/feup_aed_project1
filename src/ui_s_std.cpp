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
	auto tree_filter = [](void *ptr){ return ((Student *)ptr)->getName()[0] == 'M';};
	// Sort in reverse name alphabetical order
	auto sort_filter = [](const void * a, const void *b) { return ((Student *)a)->getName() > ((Student *)b)->getName(); };
	PrintStudent(tree_filter, sort_filter);
	// Default ordering >> PrintStudent(NULL, NULL)
}

std::string query;
bool (*parse_filter())(void *)
{
	std::string field;
	std::cin >> field;
	std::cin >> query;

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
			std::cout << "(No results)\n";

		std::cout << "\nOptions: \n reset \n search [code|name] [query]\n\n$> ";
		std::string option;
		std::cin >> option;
		if (option == "b" || option == "B")
			break;
		if (option == "search")
		{
			auto new_filter = parse_filter();
			if (!new_filter)
			{
				system(CLEAR);
				std::cout << "INVALID OPERATION\n s [field] [query]\n";
				usleep(700000);
				continue;
			}
			PrintStudent(new_filter, sort_filter);
			break;
		}
		if (option == "reset")
			PrintStudent(NULL, NULL);
			break;
	}
}
