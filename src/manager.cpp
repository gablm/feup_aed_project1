#include "manager.h"
using namespace std;

Manager::Manager() : students(BST()), ucMap() {}

void Manager::load_data(){
    //these two lines are just for debugging
    string a = "load data from manager.cpp is being debugged here ";
    cout << a;
    int counter = 0;

    string line;

    ifstream file;
    file.open("data/classes.csv");



    while(getline(file,line)){
        counter++;
        cout << line;
        cout << counter;
    }
    cout << "aaaaaaaaaaaaaaaaaaaaaa";


}