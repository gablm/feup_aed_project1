#include <iostream>
#include <string>

int main(int argc, char **argv) {
	
	system("clear");
	std::cout << u8"\033[2J\033[1;1H"; 
	while (1)
	{
		std::cout << "University of Porto - Faculty of Engineering\n"
				  << "\n"
				  << "Welcome to the Schedules service!\n"
				  << "Select an option [0-3]:\n"
				  << "\n"
				  << ">> List and search\n"
				  << "\n"
				  << "[0] Students\n"
				  << "[1] UCs\n"
				  << "[2] Classes\n"
				  << "\n"
				  << ">> Edit data\n"
				  << "\n"
				  << "[3] Change Student schedule\n"
				  << "\n"
				  << "Option: ";
		std::string str;
		std::cin >> str;
		system("clear");
		if (str == "q")
			break;
	}
	return 0;
}
