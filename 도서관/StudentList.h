#ifndef __STUDENTLIST_H__
#define __STUDENTLIST_H__

#include "Student.h"

class StudentList
{
private :
	int numOfStd;
	Student stdList[MAX_STD];

	bool isMax();

public :
	StudentList()
	{
		numOfStd = 0;
	};
	~StudentList() {};

	void insert(Student std);

	int getNumOfStd() const
	{
		return numOfStd;
	}
	int getIndex(int stdNum) const;
	Student getStudent(int index) const;


};
#endif