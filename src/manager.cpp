#include "manager.h"
using namespace std;

Manager::Manager() : students(BST()), ucMap() {}

void Manager::load_data() {

    string line;

    ifstream file;
    file.open("data/classes.csv");

    while(!file.eof()){
		getline(file,line);
        cout << line << "\n";

        
    }
}