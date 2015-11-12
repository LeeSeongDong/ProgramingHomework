#include "StudentList.h"

bool StudentList::isMax()
{
	if (numOfStd == MAX_STD)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void StudentList::insert(Student std)
{
	if (!isMax())
	{
		stdList[numOfStd] = std;
		++numOfStd;
	}
}

//학번으로 index찾기, 학생이 없으면 -1
int StudentList::getIndex(int stdNum) const
{
	int index = EMPTY;

	for (int i = 0; i < numOfStd; ++i)
	{
		if (stdNum == stdList[i].getStdNum())
		{
			index = i;
			break;
		}
	}

	return index;
}

Student StudentList::getStudent(int index) const
{
	return stdList[index];
}