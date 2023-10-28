#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <iomanip>
#include <algorithm>
#include "manager.h"

#ifdef __linux__
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

class UI {
    private:
		Manager *manager;
		std::list<void *> toDisplay;
        void UcMenu();
        void StudentMenu();
        void ClassMenu();
		void ChangeMenu();
		void PrintStudent(bool (*tree_filter)(void *), bool (*sort_filter)(const void *, const void *));

		void TestFunc();
    public:
        UI(Manager *manager);
		~UI();
		void ClearAndExit();
        void MainMenu();
};

#endif