#ifndef UI_H
#define UI_H

#include <iostream>
#include <string>
#include <cstdlib>
#include <set>
#include <iomanip>
#include "manager.h"

#ifdef __linux__
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

class UI {
    private:
		Manager *manager;
		std::set<void *> toDisplay;
        void UcMenu();
        void StudentMenu();
        void ClassMenu();
		void ChangeMenu();
		void TestFunc();
    public:
        UI(Manager *manager);
		~UI();
		void ClearAndExit();
        void MainMenu();
};

#endif