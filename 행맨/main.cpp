#include "Taskmanager.h"

int main(int argc, char** argv)		//argv[1] : 사전파일명, argv[2] : 사용자파일명
{
	IoHandler ioh;

	WordList wordList;
	UserList userList;

	Taskmanager tm;
	HangmanGame hg;

	char menu;
	
	if (argc != 3)
	{
		ioh.putMsg("사전파일명, 사용자파일명 순으로 입력해주세요");
		return 0;
	}
	
	ioh.loadWordFile(argv[1], wordList);
	ioh.loadUserFile(argv[2], userList);

	userList.setUserWinningRate();
	userList.sortByWinningRate();

	tm.loadUser(userList);

	while (true)
	{
		ioh.printMenuHeader(tm.getCurrentUser());

		menu = tm.selectMenu(ioh.inputMenu(tm.getCurrentUser()), hg, userList, wordList, argv[2]);

		if (menu == 'Q' || menu == 'Z')
		{
			return 0;
		}
	}
}
