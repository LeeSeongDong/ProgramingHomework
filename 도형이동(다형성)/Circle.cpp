#include "Circle.h"

void Circle::putShape() const
{
	cout << "�� \t " << getWidth() << " \t " << " " << " \t " << getArea() << " \t (" << getPoint().x << ", " << getPoint().y << ")" << " \t (" << getVariationPoint().x << ", " << getVariationPoint().y << ")";
}

double Circle::getArea() const
{
	return ((double)getWidth() / 2)*((double)getWidth() / 2) *PI;
}

void Circle::changeShape(Plane &plane)
{
	deleteShapeOnPlane(plane);

	int r;

	while (true)
	{
		cout << "������ ���� �������� �Է��ϼ��� : ";

		cin >> r;

		if (r > MAX_Y)
		{
			cout << "ȭ��ũ�⺸�� ū���Դϴ�." << endl;
		}
		else
		{
			break;
		}
	}

	setWidth(2*r);

	setShapeOnPlane(plane);
}

void Circle::setShapeOnPlane(Plane &plane) const
{
	int** p = plane.getPlane();

	int r = getWidth() / 2;
	int x = getPoint().x;
	int y = getPoint().y;

	for (int i = -r; i <= r; ++i)
	{
		for (int j = -r; j <= r; ++j)
		{
			if (j*j + i*i == r*r)
			{
				int tempX = x + j;
				int tempY = y + i;

				if (tempX < 0)
				{
					tempX += (MAX_X - 1);

				}
				if (tempY < 0)
				{
					tempY += (MAX_Y - 1);
				}

				++p[tempY % (MAX_Y - 1)][tempX % (MAX_X - 1)];
			}
		}
	}
}

void Circle::deleteShapeOnPlane(Plane &plane) const
{
	int** p = plane.getPlane();

	int r = getWidth() / 2;
	int x = getPoint().x;
	int y = getPoint().y;

	for (int i = -r; i <= r; ++i)
	{
		for (int j = -r; j <= r; ++j)
		{
			if (j*j + i*i == r*r)
			{
				int tempX = x + j;
				int tempY = y + i;

				if (tempX < 0)
				{
					tempX += (MAX_X - 1);

				}
				if (tempY < 0)
				{
					tempY += (MAX_Y - 1);
				}

				--p[tempY % (MAX_Y - 1)][tempX % (MAX_X - 1)];
			}
		}
	}
}