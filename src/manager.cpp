#include "manager.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Manager::Manager(): students(BST()), ucMap() {}

void Manager::load_data() {

    string line, sessionName, UCName, sessionDay, sessionType, sessionTimestr, sessionDurationstr;
    double sessionTime, sessionDuration;
	UC *temp_uc;

    ifstream file;
    file.open("data/classes.csv");

    getline(file,line); //removes the first line, which has no usable values
	
	if (line != "ClassCode,UcCode,Weekday,StartHour,Duration,Type\r"
		&& line != "ClassCode,UcCode,Weekday,StartHour,Duration,Type")
	{
		std::cout << "Invalid Header";
		exit(0);
	}

    while(true) {
		
		if (file.eof())
			break;
		
		getline(file,line);

		if (line.size() < 1)
		{
			std::cout << "[DEBUG] Invalid line" << endl;
			continue;
		}

        istringstream ss(line);

        // inserts the contents of the line into the apropriate variables, for the non-string variables an extra line was needed
		std::getline(ss, sessionName, ',');
        std::getline(ss, UCName, ',');
        std::getline(ss, sessionDay, ',');
        std::getline(ss, sessionTimestr, ',');
        sessionTime = stof(sessionTimestr);
        std::getline(ss, sessionDurationstr, ',');
        sessionDuration = stof(sessionDurationstr);
        std::getline(ss, sessionType, '\r');

		if (!temp_uc)
		{
			temp_uc = new UC(UCName, sessionName[0] - '0');
			ucMap[UCName] = temp_uc;
		}

		if (temp_uc->getName() != UCName)
		{
			if (ucMap.find(UCName) == ucMap.end())
			{
				temp_uc = new UC(UCName, sessionName[0] - '0');
				ucMap[UCName] = temp_uc;
			}
		}

        Session temp_session(sessionName, sessionDay, sessionTime, sessionDuration, sessionType);
        //std::cout << sessionName << " " << UCName << " " << sessionDay << " " << sessionTime << " " << sessionDuration << " " << sessionType << '\n';
        temp_uc->addSession(temp_session);
    }
    file.close();
}

void Manager::test_map()
{
	for (auto i = ucMap.begin(); i != ucMap.end(); i++)
	{
		UC *temp = i->second;
		std::cout << temp->getName() << endl;
		for (Session i : temp->getSessionList())
		{
			std::cout << " ID: " << i.getName() 
			<< " Type: " << i.getType()
			<< " At: " << i.getTime()
			<< " During: " << i.getDuration()
			<< " Day: " << i.getDay() 
			<< "\n";
		}
		std::cout << endl;
	}
}

void Manager::dealocate_memory()
{
	// As UCs as dinamically allocated, they need to be deleted
	for (auto i = ucMap.begin(); i != ucMap.end(); i++)
	{
		UC *p = i->second;
		p->clearSessions();
		delete i->second;
	}
}