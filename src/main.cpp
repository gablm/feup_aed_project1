#include "ui.h"
#include "manager.h"
#include <chrono>

int main(int argc, char **argv) {
    Manager manager;
    manager.load_map();
	//manager.test_map();
	auto start = std::chrono::high_resolution_clock::now();
	manager.load_students();
	manager.test_students();
	manager.dealocate_memory();
	auto stop = std::chrono::high_resolution_clock::now();
	auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(stop - start);
    //UI ui;
    //ui.MainMenu();
	return 0;
}
