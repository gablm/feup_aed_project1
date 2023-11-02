#ifndef REQUEST_H
#define REQUEST_H

#include <string>

typedef struct s_request {
	std::string type;
	std::string studentCode;
	std::string UCcode;
	std::string session1;
	std::string session2;	
} Request;

#endif