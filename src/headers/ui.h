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
		std::string field, filter;
		
		void ChangeMenu();

		// Student
		void PrintStudent(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *));
		void ShowStudent(std::string option);
		void read_if_student(BSTnode *node, std::list<void *> &toDisplay, bool (*f)(void *));
		bool (*st_parse_search_filter(std::string option))(void *);
		bool (*st_parse_sort_filter(std::string option))(const void *a, const void *b);

		// UC
		void PrintUC(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *));
		void ShowUC(std::string option);
		void read_if_UC(std::list<void *> &toDisplay, bool (*f)(void *));
		bool (*uc_parse_search_filter(std::string option))(void *);
		bool (*uc_parse_sort_filter(std::string option))(const void *a, const void *b);
    public:
        UI(Manager *manager);
		~UI();
		void ClearAndExit();
        void MainMenu();
};

#endif