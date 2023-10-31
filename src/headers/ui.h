#ifndef UI_H
#define UI_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <set>
#include <iomanip>
#include <algorithm>
#include <map>
#include "manager.h"

#ifdef __linux__
# define CLEAR "clear"
# include <unistd.h>
# define SLEEP(x) sleep(x)
#else
# define CLEAR "cls"
# include <windows.h>
# define SLEEP(x) Sleep(x)
#endif

class UI {
    private:
		Manager *manager;
		std::list<void *> toDisplay;
		std::list<std::string> toDisplayStr;
		std::string field, filter;

		// Student
		void PrintStudent(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *));
		void ShowStudent(std::string option);
		void HelpStudent(std::string error, std::string usage);
		void read_if_student(BSTnode *node, std::list<void *> &toDisplay, bool (*f)(void *));
		bool (*st_parse_search_filter(std::string option))(void *);
		bool (*st_parse_sort_filter(std::string option))(const void *a, const void *b);

		// UC
		void PrintUC(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *));
		void ShowUC(std::string option);
		void HelpUC(std::string error, std::string usage);
		void read_if_UC(std::list<void *> &toDisplay, bool (*f)(void *));
		bool (*uc_parse_search_filter(std::string option))(void *);
		bool (*uc_parse_sort_filter(std::string option))(const void *a, const void *b);

		// Session
		void PrintSession(bool (*tree_filter)(std::string), bool (*sort_filter)(const std::string, const std::string));
		void ShowSession(std::string option);
		void HelpSession(std::string error, std::string usage);
		void read_if_Session(std::list<std::string> &toDisplayStr, bool (*f)(std::string));
		bool (*ses_parse_search_filter(std::string option))(std::string);
		bool (*ses_parse_sort_filter(std::string option))(const std::string a, const std::string b);

		// Change Menu
		void PrintChange();
		void RequestDetails(std::string option);
		void HelpRequest(std::string error, std::string usage);
		void NewClass(std::string option);
		void RemoveUC(std::string option, Student *student);
		void SwapUC(std::string option);

    public:
        UI(Manager *manager);
		~UI();
		void ClearAndExit();
        void MainMenu();
};

#endif