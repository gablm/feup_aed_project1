#include "headers/ui.h"
#include "headers/manager.h"

int main(void) {
    Manager *manager = new Manager();
    manager->load_map();
	manager->load_students();
	manager->load_alterations();
	UI ui(manager);
    ui.MainMenu();
	return 0;
}
