#include "Taskmanager.h"

void Taskmanager::putShapeList(ShapeList &sl)
{
	IoHandler ioh;
	int size = sl.getSize();

	ioh.putMsg("��ȣ \t Ÿ�� \t �ʺ� \t ���� \t ���� \t �߽���ǥ \t ��ȭ�� \n");

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
		ioh.putMsg("�߰��� ������ ������ �����ϼ��� (t : �ﰢ��, r : �簢��, c : ��) : ");
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
			ioh.putMsg("�߸��� ���� �Է��Դϴ�.");
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
		ioh.putMsg("������ ������ �����ϴ�. \n");
		return;
	}

	putShapeList(sl);

	while (true)
	{
		ioh.putMsg("������ ������ ��ȣ�� �Է��ϼ��� : ");

		num = ioh.inputNum();

		if (num > 0 && num <= sl.getSize())
		{
			break;
		}
		else
		{
			ioh.putMsg("�߸��� ������ȣ�Դϴ�. \n");
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
		ioh.putMsg("������ ������ �����ϴ�. \n");
		return;
	}

	putShapeList(sl);

	while (true)
	{
		ioh.putMsg("�̵��� ������ ��ȣ�� �Է��ϼ��� : ");

		num = ioh.inputNum();

		if (num > 0 && num <= sl.getSize())
		{
			break;
		}
		else
		{
			ioh.putMsg("�߸��� ������ȣ�Դϴ�. \n");
		}
	}

	ioh.putMsg("������ ��ǥ �������� �Է��ϼ��� (x y) : ");
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
		ioh.putMsg("������ ������ �����ϴ�. \n");
		return;
	}

	putShapeList(sl);

	while (true)
	{
		ioh.putMsg("ũ�⸦ ������ ������ ��ȣ�� �Է��ϼ��� : ");

		num = ioh.inputNum();

		if (num > 0 && num <= sl.getSize())
		{
			break;
		}
		else
		{
			ioh.putMsg("�߸��� ������ȣ�Դϴ�. \n");
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
		ioh.putMsg("������ ������ �����ϴ�. \n");
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
		ioh.putMsg("0. ������� \n");
		ioh.putMsg("1. �������� \n");
		ioh.putMsg("2. ����ũ�⺯�� \n");
		ioh.putMsg("3. �����̵� \n");
		ioh.putMsg("4. �������� \n");
		ioh.putMsg("5. �����̵���� ���� \n");
		ioh.putMsg("6. ���� \n");
		ioh.putMsg("����� �����ϼ��� (1~6) :");

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
			ioh.putMsg("�߸��� ����Է� \n");
			ioh.putNewLine();
			break;
		}
		}
	}
}