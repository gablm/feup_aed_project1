#ifndef SESSION_H
#define SESSION_H

#include <string>
#include <ostream>
#include <list>

class Student;

class Session {
	private:
		std::string name;
		std::string day;
		double time;
		double duration;
		std::string type;
		std::list<Student*> studentList;
	public:
		Session(std::string name, std::string day, double time, double duration, std::string type);
		std::string getDay() const;
		double getTime() const;
		double getDuration() const;
		std::string getName() const;
		std::string getType() const;
		void addStudent(Student *student);
};

#endif