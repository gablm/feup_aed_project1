#ifndef UI_H
#define UI_H

#include <iostream>
#include <sstream>
#include <string>
#include <cstdlib>
#include <set>
#include <iomanip>
#include <algorithm>
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
        void UcMenu();
        void StudentMenu();
        void ClassMenu();
		void ChangeMenu();
		void PrintStudent(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *));
		void ShowStudent(std::string option);

		void TestFunc();
    public:
        UI(Manager *manager);
		~UI();
		void ClearAndExit();
        void MainMenu();
};

#endif