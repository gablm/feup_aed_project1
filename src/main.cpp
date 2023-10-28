#include "ui.h"
#include "manager.h"

int main(int argc, char **argv) {
    Manager *manager = new Manager();
    manager->load_map();
	//manager->test_map();
	manager->load_students();
	//manager->test_students();
	UI ui(manager);
    ui.MainMenu();
	return 0;
}
