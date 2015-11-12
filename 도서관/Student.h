#ifndef __STUDENT_H__
#define __STUDENT_H__

#include "Header.h"

class Student
{
private :
	int stdNum;
	string stdName;

public :
	Student() {};
	Student(int stdNum, string stdName)
	{
		this->stdNum = stdNum;
		this->stdName = stdName;
	}
	~Student() {};

	int getStdNum() const
	{
		return stdNum;
	}
	string getStdName() const
	{
		return stdName;
	}

};
#endif