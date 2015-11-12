#include "LendList.h"

bool LendList::isMax()
{
	if (numOfLend == MAX_BOOK)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void LendList::insert(Lend lend)
{
	if (!isMax())
	{
		lendList[numOfLend] = lend;
		++numOfLend;

		sortFlag = false;
	}
}

//index위치의 lend삭제
void LendList::deleteLend(int index)
{
	if (index != numOfLend)
	{
		swap(index, numOfLend-1);
		sortFlag = false;
	}

	--numOfLend;
}

//학번으로 lendIndex찾기
int LendList::getIndexByStd(int stdNum) const
{
	int index = EMPTY;

	for (int i = 0; i < numOfLend; ++i)
	{
		if (stdNum == lendList[i].getStdNum())
		{
			index = i;
			break;
		}
	}

	return index;
}

//책번호로 lendIndex찾기
int LendList::getIndexByBook(string bookNum) const
{
	int index = EMPTY;

	for (int i = 0; i < numOfLend; ++i)
	{
		if (lendList[i].getBookNum().compare(bookNum) == 0)
		{
			index = i;
			break;
		}
	}

	return index;
}

Lend LendList::getLend(int index) const
{
	return lendList[index];
}

//학번우선 오름차순정렬, 책번호 오름차순정렬
void LendList::sort()
{
	int k;

	for (int i = 0; i < numOfLend; ++i)
	{
		k = i;
		for (int j = i+1; j < numOfLend; ++j)
		{
			//학번
			if (lendList[k].getStdNum() > lendList[j].getStdNum())
			{
				k = j;
			}
			else if (lendList[k].getStdNum() == lendList[j].getStdNum())
			{
				//책번호
				if (lendList[k].getBookNum().compare(lendList[j].getBookNum()) > 0)
				{
					k = j;
				}
			}
		}

		if (k != i)
		{
			swap(i, k);
		}
	}

	sortFlag = true;
}

//i 인덱스의 lend와 j 인덱스의 lend를 바꿈
void LendList::swap(int i, int j)
{
	int stdNum = lendList[i].getStdNum();
	string bookNum = lendList[i].getBookNum();

	Lend temp(stdNum, bookNum);

	lendList[i].setLend(lendList[j].getStdNum(), lendList[j].getBookNum());
	lendList[j].setLend(temp.getStdNum(), temp.getBookNum());
}

bool LendList::isSort() const
{
	return sortFlag;
}