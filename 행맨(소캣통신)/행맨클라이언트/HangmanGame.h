#ifndef __HANGMANGAME_H__
#define __HANGMANGAME_H__

#include "IoHandler.h"

class HangmanGame
{
private :
	int hangmanCount;
	string questionWord;
	string partOfSpeech;
	string meaning;

	string data;
	char usableLetter [26];
	string findLetter;

public :
	HangmanGame()
	{
		hangmanCount = 0;
	};
	~HangmanGame() {};

	void setQuestion(string word, string partOfSpeech, string meaning)
	{
		this->questionWord = word;
		this->partOfSpeech = partOfSpeech;
		this->meaning = meaning;
	}
	
	void putQuestion();
	void putAnswer();

	string getQuestionWord()
	{
		return questionWord;
	}
	void setInputWord(string inputData)
	{
		data = inputData;
	}
	string getInputWord()
	{
		return data;
	}
	string getFindLetter()
	{
		return findLetter;
	}
	char getUsableLetter(int i)
	{
		return usableLetter[i];
	}

	bool isLetter();
	bool isCorrect();

	void setFindLetter();
	void setUsableLetter();

	bool isWin();
	bool isLose();

	void initGame()
	{
		hangmanCount = 0;
	}

	void putUsableLetter();
	void putFindLetter();
	void putHangman();
	void putGameHeader(User currentUser, int win, int lose);
};

#endif