#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <ostream>
#include <list>
#include "student.h"

class Time {
	public:
		Time();
		Time(int h, int m);
		int getHour() const;
		int getMinute() const;
	private:
		int hour;
		int minute;
};

class SessionName {
	public:
		int year;
		std::string course_id;
		int number;
};

class Session {
	private:
		SessionName name;
		Time time;
		std::string type;
		std::list<Student*> studentList;
	public:
		Session(SessionName name, Time time, std::string type);
		Time getTime() const;
		SessionName getName() const;
		std::string getType() const;
		void addStudent(Student *student);
};

#endif