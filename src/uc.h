#include <string>
#include <ostream>

class UCname {
	public:
		int year;
		std::string course_id;
		int number;
};

std::ostream& operator<<(std::ostream& os, const UCname& obj)
{
    os << obj.year << obj.course_id << obj.number;
    return os;
}

class UC {
	private:
		UCname name;
		//list of classes?
	public:
		//...
};