#ifndef __WORDLIST_H__
#define __WORDLIST_H__

#include "Word.h"

class WordList
{
private : 
	int capacity = 10;
	int size = 0;
	
	Word *wordList;

	void doubleCapacity();

public :
	WordList() 
	{
		wordList = new Word[capacity];
	};
	~WordList()
	{ 
		delete[]wordList;
	};


	Word getWordByIndex(int index)
	{
		return wordList[index];
	}
	int getWordListSize()
	{
		return size;
	}
	void insertWord(Word word);

	void deleteWordList()
	{
		delete []wordList;
	}
};

#endif