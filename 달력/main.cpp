#include "IoHandler.h"

int main()
{
	cout << "�Է��� ���� �޷��� ����ϴ� ���α׷� �Դϴ�." << endl;
	IoHandler ioh;

	Calender cld( ioh.inputYear("�⵵�� �Է��ϼ���. : ") );

	cld.setCalender();

	ioh.printYear();
	ioh.printCalender(cld);

	return 0;
}