#pragma once
#include"Basc.h"
#include<string>

using uint32 = unsigned int;

class Student_data
{

public:
	Student_data();
	Student_data(uint32 number, const std::string& name, const std::string& grade, uint32 math, uint32 chinese, uint32 english);
	uint32 number;
	std::string name;
	std::string grade;
	uint32 math;
	uint32 chinese;
	uint32 english;
	std::string formatIn();
	static Student_data fromString(const std::string& str);


};

