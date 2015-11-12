#include "WordList.h"

void WordList::insertWord(Word word)
{

	if (size == capacity)
	{
		doubleCapacity();
	}

	++size;
	wordList[size - 1] = word;

}


void WordList::doubleCapacity()
{
		int beforCapacity = capacity;

		capacity *= 2;

		Word *temp = new Word[capacity];

		for (int i = 0; i < beforCapacity; ++i)
		{
			temp[i] = wordList[i];
		}

		delete[]wordList;

		wordList = temp;
}