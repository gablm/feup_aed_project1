#include <iostream>
#include <string>

int main(int argc, char **argv) {
	
	std::cout << u8"\033[2J\033[1;1H"; 
	while (1)
	{
		std::cout << 
"University of Porto - Faculty of Engineering\n\
\n\
Welcome to the Schedules service!\n\
Please select an option [0-1]:\n\
\n\
  [0] Students\n\
  [1] UCs\n\
\n\
Option: ";
		std::string str;
		std::cin >> str;
		std::cout << u8"\033[2J\033[1;1H";
	}
	return 0;
}
