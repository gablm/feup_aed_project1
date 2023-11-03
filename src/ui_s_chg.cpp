#include "headers/ui.h"
    
void UI::removeLast(std::string path) 
{
    std::ifstream in(path);
    std::ofstream out("edit.tmp");

	std::string line;
    std::getline(in, line);
    for (std::string tmp; std::getline(in, tmp); line.swap(tmp)) {
        out << line << '\n';
    }
	in.close();
    out.close();
	std::rename("edit.tmp", path.c_str());
}

void UI::undoLastChange(std::stack<Request*> &requests)
{
	if (requests.empty())
		return;
	auto elem = requests.top();
    requests.pop();
	removeLast("./changes.log");
	removeLast("./data/changes.csv");

	Student *student = (Student *) manager->getStudents().search(std::stod(elem->studentCode));

	if (elem->type == "remove")
	{
		UC *uc = manager->getUcMap()[elem->UC1];
		auto sessions = uc->find(elem->session1);
		student->editUCcount(1);
		uc->editStudentCount(1);
		for (auto i : sessions)
		{
			i->addStudent(student);
			student->addToSchedule(std::make_pair(uc, i));
		}
	}

	if (elem->type == "add")
	{
		UC *uc = manager->getUcMap()[elem->UC1];
		
		auto removeSessions = uc->find(elem->session1);	
		for (auto i : removeSessions)
		{
			student->removeFromSchedule(std::make_pair(uc, i));
			i->removeStudent(student);
		}
		
		if (elem->session2 == "")
		{
			student->editUCcount(-1);
			uc->editStudentCount(-1);
		}
		else
		{
			auto addSessions = uc->find(elem->session2);
			for (auto i : addSessions)
			{
				student->addToSchedule(std::make_pair(uc, i));
				i->addStudent(student);
			}
		}

		if (elem->type == "swapUC")
		{
			UC *uc1 = manager->getUcMap()[elem->UC1];
			UC *uc2 = manager->getUcMap()[elem->UC2];

			uc1->editStudentCount(1);
			uc2->editStudentCount(-1);

			for (auto i : uc1->find(elem->session1))
			{
				student->addToSchedule(std::make_pair(uc, i));
				i->addStudent(student);
			}

			for (auto i : uc2->find(elem->session2))
			{
				student->removeFromSchedule(std::make_pair(uc, i));
				i->removeStudent(student);
			}
		}
	}
}

void UI::printStack(std::stack<Request*> requests)
{
	if (requests.empty())
		return;
    auto elem = requests.top();
    requests.pop();
    printStack(requests);
    requests.push(elem);
    std::cout << "[" << std::put_time(std::localtime(&elem->timestamp), "%d/%m/%Y %T") << "] ";
	if (elem->type == "add")
		std::cout << "Added pair <" << elem->UC1 << ", " << elem->session1 << "> to " + elem->studentCode;
	if (elem->type == "remove")
		std::cout << "Removed all classes for " <<  elem->UC1 << " of " << elem->studentCode;
	if (elem->type == "swapUC")
		std::cout << "Swapped UC from pair <" << elem->UC1 << ", " << elem->session1 << "> to <" << elem->UC2 << ", " << elem->session2 << "> for " << elem->studentCode;
	std::cout << std::endl;
}

void UI::PrintChangeHistory()
{
	while (1)
	{
		CLEAR;
		std::cout << "Schedules - Change History\n\n";
		auto rStack = manager->getRequestStack();
		if (rStack.empty())
			std::cout << "(No history to show)\n";
		else
			printStack(rStack);
		std::cout << std::left
				  << "\n [U] Undo most recent action (last action on the list)"
				  << "\n [B] Go back"
				  << "\n [Q] Quit"
				  << "\n\n"
				  << " $> ";
		std::string str;
		getline(std::cin, str);
		if (str == "b" || str == "B")
			break;
		if (str == "q" || str == "Q")
			ClearAndExit();
		if ((str == "u" || str == "U") && !rStack.empty())
			undoLastChange(manager->getRequestStack());
	}
}
