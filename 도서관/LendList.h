#ifndef __LENDLIST_H__
#define __LENDLIST_H__

#include"Lend.h"

class LendList
{
private :
	int numOfLend;
	Lend lendList[MAX_BOOK];
	bool sortFlag;	//sort되었는지	true : 정렬된상태

	bool isMax();
	void swap(int i, int j);

public :
	LendList()
	{
		sortFlag = false;
		numOfLend = 0;
	};
	~LendList() {};

	void insert(Lend lend);
	void deleteLend(int index);

	int getNumOfLend() const
	{
		return numOfLend;
	}
	int getIndexByStd(int stdNum) const;
	int getIndexByBook(string bookNum) const;
	Lend getLend(int index) const;

	void sort();
	bool isSort() const;
};
#endif