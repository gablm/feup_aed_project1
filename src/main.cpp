#include "ui.h"
#include "manager.h"

int main(int argc, char **argv) {
    Manager manager;
    manager.load_map();
	//manager.test_map();
	manager.load_students();
	manager.test_students();
	manager.dealocate_memory();
    //UI ui = UI();
    //ui.MainMenu();
	return 0;
}
