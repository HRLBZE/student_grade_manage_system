#include "Student_data.h"
#include<sstream>

Student_data::Student_data()
{
}

Student_data::Student_data(uint32 number, const std::string& name, const std::string& grade, uint32 math, uint32 chinese, uint32 english)
	:number(number), name(name), grade(grade), math(math), chinese(chinese), english(english)
{
}

std::string Student_data::formatIn()
{
	std::stringstream ss;
	ss << number << "\t" << name << "\t" << grade << "\t" << math << "\t" << chinese << "\t" << english << std::endl;

	return ss.str();
}

Student_data Student_data::fromString(const std::string& str)
{
	Student_data stu;
	std::stringstream ss(str);
	ss >> stu.number >> stu.name >> stu.grade >> stu.chinese >> stu.math >> stu.english;
	return stu;
}
