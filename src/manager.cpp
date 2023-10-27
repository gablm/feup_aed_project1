#include "manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Manager::Manager() : students(BST()), ucMap() {}

void Manager::load_data() {

    string line, sessionName, UCName, sessionDay, sessionType, sessionTimestr, sessionDurationstr;
    double sessionTime, sessionDuration;

    ifstream file;
    file.open("data/classes.csv");

    getline(file,line); //removes the first line, which has no usable values

    while(!file.eof()){
		getline(file,line);
        istringstream ss(line);

        // inserts the contents of the line into the apropriate variables, for the non-string variables an extra line was needed

        std::getline(ss, sessionName, ',');
        std::getline(ss, UCName, ',');
        std::getline(ss, sessionDay, ',');
        std::getline(ss, sessionTimestr, ',');
        sessionTime = stof(sessionTimestr);
        std::getline(ss, sessionDurationstr, ',');
        sessionDuration = stof(sessionDurationstr);
        std::getline(ss, sessionType, ',');

        Session temp_session(sessionName, sessionDay, sessionTime, sessionDuration, sessionType);

        cout << UCName << "\n";



        //std::cout << sessionName << " " << UCName << " " << sessionDay << " " << sessionTime << " " << sessionDuration << " " << sessionType << '\n';
        
    }
    file.close();
}