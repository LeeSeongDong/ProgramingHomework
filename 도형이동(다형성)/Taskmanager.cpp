#include "Taskmanager.h"

void Taskmanager::putShapeList(ShapeList &sl)
{
	IoHandler ioh;
	int size = sl.getSize();

	ioh.putMsg("번호 \t 타입 \t 너비 \t 높이 \t 면적 \t 중심좌표 \t 변화량 \n");

	for (int i = 0; i < size; ++i)
	{
		ioh.putMsg("[ ");
		ioh.putNum(i + 1);
		ioh.putMsg(" ] \t ");

		sl.getShape(i)->putShape();
		ioh.putNewLine();
	}
}

void Taskmanager::insertShape(ShapeList &sl, Plane &plane)
{
	IoHandler ioh;

	while (true)
	{
		ioh.putMsg("추가할 도형의 유형을 선택하세요 (t : 삼각형, r : 사각형, c : 원) : ");
		char type = ioh.inputChar();

		switch (type)
		{
		case 'T':
		case 't':
		{
			sl.insert('t', plane);
			break;
		}
		case 'R':
		case 'r':
		{
			sl.insert('r', plane);
			break;
		}
		case 'C':
		case 'c':
		{
			sl.insert('c', plane);
			break;
		}
		default:
		{
			ioh.putMsg("잘못된 유형 입력입니다.");
			ioh.putNewLine();
			continue;
		}
		}

		break;
	}
}

void Taskmanager::deleteShape(ShapeList &sl, Plane &plane)
{
	IoHandler ioh;
	int num;

	if (!sl.getSize())
	{
		ioh.putMsg("생성된 도형이 없습니다. \n");
		return;
	}

	putShapeList(sl);

	while (true)
	{
		ioh.putMsg("삭제할 도형의 번호를 입력하세요 : ");

		num = ioh.inputNum();

		if (num > 0 && num <= sl.getSize())
		{
			break;
		}
		else
		{
			ioh.putMsg("잘못된 도형번호입니다. \n");
		}
	}

	sl.deleteShape(num - 1, plane);
}

void Taskmanager::moveShape(ShapeList &sl)
{
	IoHandler ioh;
	int num;

	if (!sl.getSize())
	{
		ioh.putMsg("생성된 도형이 없습니다. \n");
		return;
	}

	putShapeList(sl);

	while (true)
	{
		ioh.putMsg("이동할 도형의 번호를 입력하세요 : ");

		num = ioh.inputNum();

		if (num > 0 && num <= sl.getSize())
		{
			break;
		}
		else
		{
			ioh.putMsg("잘못된 도형번호입니다. \n");
		}
	}

	ioh.putMsg("설정할 좌표 증가값을 입력하세요 (x y) : ");
	int x = ioh.inputNum();
	int y = ioh.inputNum();

	sl.getShape(num-1)->setVariationPoint(x, y);
}

void Taskmanager::changeShape(ShapeList &sl, Plane &plane)
{
	IoHandler ioh;
	int num;

	if (!sl.getSize())
	{
		ioh.putMsg("생성된 도형이 없습니다. \n");
		return;
	}

	putShapeList(sl);

	while (true)
	{
		ioh.putMsg("크기를 변경할 도형의 번호를 입력하세요 : ");

		num = ioh.inputNum();

		if (num > 0 && num <= sl.getSize())
		{
			break;
		}
		else
		{
			ioh.putMsg("잘못된 도형번호입니다. \n");
		}
	}

	sl.getShape(num - 1)->changeShape(plane);
	sl.sort(num - 1);
}

void Taskmanager::figureMoveMode(ShapeList &sl, FigureHandler &fh, Plane &plane)
{
	IoHandler ioh;
	if (!sl.getSize())
	{
		ioh.putMsg("생성된 도형이 없습니다. \n");
		return;
	}

	fh.figureMode(sl, plane);
}

void Taskmanager::runPgm(ShapeList &sl, FigureHandler &fh, Plane &plane)
{
	IoHandler ioh;

	int menu;

	while (true)
	{
		ioh.putMsg("0. 도형출력 \n");
		ioh.putMsg("1. 도형생성 \n");
		ioh.putMsg("2. 도형크기변경 \n");
		ioh.putMsg("3. 도형이동 \n");
		ioh.putMsg("4. 도형삭제 \n");
		ioh.putMsg("5. 도형이동모드 실행 \n");
		ioh.putMsg("6. 종료 \n");
		ioh.putMsg("기능을 선택하세요 (1~6) :");

		menu = ioh.inputNum();

		switch (menu)
		{
		case 0:
		{
			putShapeList(sl);
			ioh.putNewLine();
			break;
		}
		case 1:
		{
			insertShape(sl, plane);
			ioh.putNewLine();
			break;
		}
		case 2:
		{
			changeShape(sl, plane);
			ioh.putNewLine();
			break;
		}
		case 3:
		{
			moveShape(sl);
			ioh.putNewLine();
			break;
		}
		case 4:
		{
			deleteShape(sl, plane);
			ioh.putNewLine();
			break;
		}
		case 5:
		{
			fh.figureMode(sl, plane);
			ioh.putNewLine();
			break;
		}
		case 6:
		{
			return;
		}
		default:
		{
			ioh.putMsg("잘못된 기능입력 \n");
			ioh.putNewLine();
			break;
		}
		}
	}
}