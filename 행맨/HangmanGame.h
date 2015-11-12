#ifndef __HANGMANGAME_H__
#define __HANGMANGAME_H__

#include "UserList.h"
#include "WordList.h"
#include "IoHandler.h"

class HangmanGame
{
private :
	int hangmanCount = 0;
	string questionWord;
	string partOfSpeech;
	string meaning;

	string data;
	char usableLetter [26];
	string findLetter;

public :
	HangmanGame() {};
	~HangmanGame() {};
	
	void makeQuestion(WordList &wordList);
	void putQuestion();

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

	void endGame()
	{
		hangmanCount = 0;
	}

	void putUsableLetter();
	void putFindLetter();
	void putHangman();
	void putGameHeader(User currentUser);
};

#endif