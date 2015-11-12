#include "Triangle.h"

void Triangle::putShape() const
{
	cout << "�ﰢ��\t " << getWidth() << " \t " << height << " \t " << getArea() << " \t (" << getPoint().x << ", " << getPoint().y << ")" << " \t (" << getVariationPoint().x << ", " << getVariationPoint().y << ")";
}

double Triangle::getArea() const
{
	return ((double)(height * getWidth()) / 2);
}

void Triangle::changeShape(Plane &plane)
{
	deleteShapeOnPlane(plane);
	int w, h;

	while (true)
	{
		cout << "������ �ﰢ���� �ʺ�� ���̸� �Է��ϼ��� : ";

		cin >> w >> h;

		if (w > MAX_X || h > MAX_Y)
		{
			cout << "ȭ��ũ�⺸�� ū���Դϴ�." << endl;
		}
		else
		{
			break;
		}
	}

	setWidth(w);
	height = h;

	setShapeOnPlane(plane);
}

void Triangle::setShapeOnPlane(Plane &plane) const
{
	int** p = plane.getPlane();

	int x, y;

	int slope = 2 * height / getWidth();

	x = getPoint().x - getWidth() / 2;
	y = getPoint().y - height / 2;

	for (int i = 0; x + i < getPoint().x; ++i)
	{
		int tempX = x+i;
		int tempY = y;

		if (tempX <= 0)
		{
			tempX += (MAX_X - 1);

		}
		if (tempY <= 0)
		{
			tempY += (MAX_Y - 1);
		}

		++p[tempY % (MAX_Y - 1)][tempX % (MAX_X - 1)];

		if (i != 0)
		{
			++p[(tempY + (slope * i)) % (MAX_Y - 1)][tempX % (MAX_X - 1)];
		}
	}

	x = getPoint().x + getWidth() / 2;
	y = getPoint().y - height / 2;

	for (int i = 0; x - i >= getPoint().x; ++i)
	{
		int tempX = x - i;
		int tempY = y;

		if (tempX <= 0)
		{
			tempX += (MAX_X - 1);

		}
		if (tempY <= 0)
		{
			tempY += (MAX_Y - 1);
		}

		++p[tempY % (MAX_Y - 1)][tempX % (MAX_X - 1)];

		if (i != 0)
		{
			++p[(tempY + (slope * i)) % (MAX_Y - 1)][(tempX) % (MAX_X - 1)];
		}
	}
}

void Triangle::deleteShapeOnPlane(Plane &plane) const
{
	int** p = plane.getPlane();

	int slope = 2 * height / getWidth();

	int x, y;

	x = getPoint().x - getWidth() / 2;
	y = getPoint().y - height / 2;

	for (int i = 0; x + i < getPoint().x; ++i)
	{
		int tempX = x + i;
		int tempY = y;

		if (tempX <= 0)
		{
			tempX += (MAX_X - 1);

		}
		if (tempY <= 0)
		{
			tempY += (MAX_Y - 1);
		}

		--p[tempY % (MAX_Y - 1)][tempX % (MAX_X - 1)];

		if (i != 0)
		{
			--p[(tempY + (slope * i)) % (MAX_Y - 1)][tempX % (MAX_X - 1)];
		}
	}

	x = getPoint().x + getWidth() / 2;
	y = getPoint().y - height / 2;

	for (int i = 0; x - i >= getPoint().x; ++i)
	{
		int tempX = x - i;
		int tempY = y;

		if (tempX <= 0)
		{
			tempX += (MAX_X - 1);

		}
		if (tempY <= 0)
		{
			tempY += (MAX_Y - 1);
		}

		--p[tempY % (MAX_Y - 1)][tempX % (MAX_X - 1)];

		if (i != 0)
		{
			--p[(tempY + (slope * i)) % (MAX_Y - 1)][(tempX) % (MAX_X - 1)];
		}
	}
}