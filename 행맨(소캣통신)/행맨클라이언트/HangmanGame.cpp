#include "HangmanGame.h"

const int UPPER_A = 65;
const int GAP_UPPER_TO_LOWER = 32;
const int NUMBER_OF_ALPHABET = 26;
const int MAX_HANGMAN_COUNT = 7;

void HangmanGame::makeQuestion(WordList &wordList)
{
	srand( (unsigned) time(NULL) );
	int i = rand() % wordList.getWordListSize();

	questionWord = wordList.getWordByIndex(i).getWordName();
	partOfSpeech = wordList.getWordByIndex(i).getPartOfSpeech();
	meaning = wordList.getWordByIndex(i).getMeaning();
}


void HangmanGame::putQuestion()
{
	IoHandler ioh;

	ioh.putMsg("대상 단어: ");
	putFindLetter();
	ioh.putNewLine();

	ioh.putMsg("힌트: ");
	ioh.putMsg(partOfSpeech);
	ioh.putSpace();
	ioh.putMsg(meaning);
	ioh.putNewLine();

}


bool HangmanGame::isLetter()
{
	if (data.size() == 1)
	{
		return true;
	}
	else
	{
		return false;
	}
}


bool HangmanGame::isCorrect()
{
	if (!isLetter())
	{
		if (data == questionWord)
		{
			findLetter = questionWord;

			for (int i = 0; i < NUMBER_OF_ALPHABET; ++i)
			{
				for (int j = 0; j < findLetter.size(); ++j)
				{
					if (usableLetter[i] != '_' && usableLetter[i] == findLetter.at(j))
					{
						usableLetter[i] = '_';
					}
				}
			}

			return true;
		}

		++hangmanCount;
		return false;
	}

	else
	{
		int count = 0;

		for (int i = 0; i < questionWord.size(); ++i)
		{
			if (data.at(0) == questionWord.at(i))
			{
				findLetter.at(i) = questionWord.at(i);
				++count;
			}
		}

		for (int i = 0; i < NUMBER_OF_ALPHABET; ++i)
		{
			if (usableLetter[i] != '_' && usableLetter[i] + GAP_UPPER_TO_LOWER == data.at(0))
			{
				usableLetter[i] = '_';
			}
		}
		
		if (count == 0)
		{
			++hangmanCount;
			return false;
		}
		else
		{
			return true;
		}

	}
}


void HangmanGame::setFindLetter()
{
	findLetter = questionWord;

	for (int i = 0; i < questionWord.size(); ++i)
	{
		findLetter.at(i) = '_';
	}
}


void HangmanGame::setUsableLetter()
{
	for ( int i = 0; i < NUMBER_OF_ALPHABET; ++i)
	{
		usableLetter[i] = UPPER_A + i;
	}
}


bool HangmanGame::isWin()
{
	if(hangmanCount < MAX_HANGMAN_COUNT)
	{
		int count = 0;

		for (int i = 0; i < questionWord.size(); ++i)
		{
			if(findLetter.at(i) != '_')
			{
				++count;
			}
		}

		if(count == questionWord.size())
		{
			return true;
		}
	}
	else
	{
		return false;
	}
}

bool HangmanGame::isLose()
{
	if (hangmanCount >= MAX_HANGMAN_COUNT)
	{
		return true;
	}
	else
	{
		return false;
	}
}


void HangmanGame::putUsableLetter()
{
	IoHandler ioh;

	ioh.putMsg("사용가능한 문자 : ");

	for (int i = 0; i < NUMBER_OF_ALPHABET; ++i)
	{
		ioh.printLetter(usableLetter[i]);

		if (i < NUMBER_OF_ALPHABET - 1)
		{
			ioh.putSpace();
		}
	}
}


void HangmanGame::putFindLetter()
{
	IoHandler ioh;

	for (int i = 0; i < questionWord.size(); ++i)
	{
		ioh.printLetter(findLetter[i]);

		if (i < questionWord.size() - 1);
		{
			ioh.putSpace();
		}

	}
}


void HangmanGame::putHangman()
{
	IoHandler ioh;

	ioh.printHangman(hangmanCount);
}


void HangmanGame::putGameHeader(User currentUser)
{
	IoHandler ioh;

	ioh.printGameHeader(currentUser);
}