#ifndef __WORD_H__
#define __WORD_H__

#include <string>

using namespace std;

class Word
{
private :
	string wordName;
	string partOfSpeech;
	string meaning;

public :
	Word() {};
	Word(string loadName, string loadPartOfSpeech, string loadMeaning)
	{
		wordName = loadName;
		partOfSpeech = loadPartOfSpeech;
		meaning = loadMeaning;
	}
	~Word() {};

	string getWordName()
	{
		return wordName;
	}
	string getPartOfSpeech()
	{
		return partOfSpeech;
	}
	string getMeaning()
	{
		return meaning;
	}
};

#endif