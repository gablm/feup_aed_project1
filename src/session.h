#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <ostream>
#include <list>

class Student;

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

/**
 * A Sessions represents a specific class (as in, "aula") with a specific name and place in the schedule. The name was chosen to avoid
 * confusion with the c++ Classes.
*/
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