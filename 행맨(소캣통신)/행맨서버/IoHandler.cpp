#include "IoHandler.h"

void IoHandler::loadUserFile(string userFile, UserList &userList)
{
		ifstream inputFile;

		inputFile.open(userFile);

		if (inputFile.fail())
		{
			cout << "����� ������ ã�� ���߽��ϴ�.";
			return;
		}

		string name;
		string loadWinCount;
		string loadLoseCount;

		int winCount;
		int loseCount;
		int userCount = 0;

		string temp;

		while (!inputFile.eof())
		{


			inputFile >> name;

			while (name.at(name.size()-1) != ']')		//�̸��� ������ �ִ°��
			{
				inputFile >> temp;
				name = name + " " + temp;
			}

			inputFile >> loadWinCount;
			inputFile >> loadLoseCount;

			//[ ] ���̿� �ִ� ���ڿ��� ����
			name = name.substr(1, name.size() - 2);
			loadWinCount = loadWinCount.substr(1, loadWinCount.size() - 1);
			loadLoseCount = loadLoseCount.substr(1, loadLoseCount.size() - 1);

			// ���д� string���� int������ ����
			winCount = atoi(loadWinCount.c_str());
			loseCount = atoi(loadLoseCount.c_str());

			//�̸�, ��, �и� user�� ������ userList�� ����
			User user(name, winCount, loseCount);
			userList.insertUser(user);
		}

		inputFile.close();
	}


void IoHandler::loadWordFile(string wordFile, WordList &wordList)
{
	ifstream inputFile;

	inputFile.open(wordFile);

	if (inputFile.fail())
	{
		cout << "�ܾ� ������ ã�� ���߽��ϴ�.";
		return;
	}

	string wordName;
	string partOfSpeech;
	string meaning;

	int wordCount = 0;

	string temp;

	while (!inputFile.eof())
	{
		inputFile >> wordName;

		while (wordName.at(wordName.size() - 1) != ']')		//�ܾ ������ �ִ°��
		{
			inputFile >> temp;
			wordName = wordName + " " + temp;
		}

		inputFile >> partOfSpeech;

		while (partOfSpeech.at(partOfSpeech.size() - 1) != ']')		//ǰ�翡 ������ �ִ°��
		{
			inputFile >> temp;
			partOfSpeech = partOfSpeech + " " + temp;
		}

		//inputFile >> space;			//�������� ��ĭ�� ���ֱ�����

		getline(inputFile, meaning, '\n');	//�ǹ̺κ��� ������ ���� ��� ������ getline���


		wordName = wordName.substr(1, wordName.size() - 2);

		Word word(wordName, partOfSpeech, meaning);

		wordList.insertWord(word);
	}

	inputFile.close();
}


void IoHandler::saveUserFile(string userFile, UserList &userList)
{
	ofstream outputFile;

	outputFile.open(userFile);

	if (outputFile.fail())
	{
		cout << "������ ã���� �����ϴ�.";
		return;
	}

	for (int i = 0; i < userList.getSize(); ++i)
	{
		outputFile << "[" << userList.getUserByIndex(i).getName() << "]" << " ";
		outputFile << "[" << userList.getUserByIndex(i).getWinCount() << "]" << " ";
		outputFile << "[" << userList.getUserByIndex(i).getLoseCount() << "]";
		if (i != userList.getSize() - 1)
		{
			outputFile << endl;
		}
	}

	outputFile.close();
}
