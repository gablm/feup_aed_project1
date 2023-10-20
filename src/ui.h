#include <iostream>
#include <string>
#include <list>

#ifdef __linux__
#define CLEAR "clear"
#else
#define CLEAR "cls"
#endif

class UI {
    private:
        void UcMenu();
        void StudentMenu();
        void ClassMenu();
    public:
        UI() = default;
		void ClearAndExit();
        void MainMenu();
};