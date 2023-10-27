#include "ui.h"
#include "manager.h"

int main(int argc, char **argv) {
    Manager manager;
    manager.load_data();
	manager.test_map();
    //UI ui = UI();
    //ui.MainMenu();
	return 0;
}
