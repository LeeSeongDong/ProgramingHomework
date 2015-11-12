#include "IoHandler.h"

int main()
{
	cout << "입력한 해의 달력을 출력하는 프로그램 입니다." << endl;
	IoHandler ioh;

	Calender cld( ioh.inputYear("년도를 입력하세요. : ") );

	cld.setCalender();

	ioh.printYear();
	ioh.printCalender(cld);

	return 0;
}