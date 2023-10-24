#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <ostream>
#include <list>

class Student;

class Time {
	public:
		Time(int h, int m) : hour(h), minute(m) {}
		int getHour() const { return hour; }
		int getMinte() const { return minute; }
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
		std::list<Student> studentList;
		//...
	public:
		//...
};

#endif