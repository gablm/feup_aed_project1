#include <string>
#include <ostream>

class Time {
	public:
		Time(int h, int m) : hour(h), minute(m) {}
		int getHour() const { return hour; }
		int getMinte() const { return minute; }
	private:
		int hour;
		int minute;
};

std::ostream& operator<<(std::ostream& os, const Time& obj)
{
    os << obj.getHour() << ":" << obj.getMinte();
    return os;
}

class Session {
	private:
		Time time;
		//List students?
	public:
		//...
};