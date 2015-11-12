#include "MyRectangle.h"

void MyRectangle::putShape() const
{
	cout << "사각형\t " << getWidth() << " \t " << height << " \t " << getArea() << " \t (" << getPoint().x << ", " << getPoint().y << ")" << " \t (" << getVariationPoint().x << ", " << getVariationPoint().y << ")";
}

double MyRectangle::getArea() const
{
	return (double)height*getWidth();
}

void MyRectangle::changeShape(Plane &plane)
{
	deleteShapeOnPlane(plane);
	int w, h;

	while (true)
	{
		cout << "변경할 사각형의 너비와 높이를 입력하세요 : ";

		cin >> w >> h;

		if (w > MAX_X || h > MAX_Y)
		{
			cout << "화면크기보다 큰값입니다." << endl;
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

void MyRectangle::setShapeOnPlane(Plane &plane) const
{
	int **p = plane.getPlane();

	int x, y;

	for (x = getPoint().x - getWidth() / 2; x <= getPoint().x + getWidth() / 2; ++x)
	{
		for (y = getPoint().y - height / 2; y <= getPoint().y + height / 2; ++y)
		{
			if (x == getPoint().x - getWidth() / 2 || x == getPoint().x + getWidth() / 2 || y == getPoint().y + height / 2 || y == getPoint().y - height / 2)
			{
				int tempX = x;
				int tempY = y;
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

void MyRectangle::deleteShapeOnPlane(Plane &plane) const
{
	int **p = plane.getPlane();

	int x, y;

	for (x = getPoint().x - getWidth() / 2; x <= getPoint().x + getWidth() / 2; ++x)
	{
		for (y = getPoint().y - height / 2; y <= getPoint().y + height / 2; ++y)
		{
			if (x == getPoint().x - getWidth() / 2 || x == getPoint().x + getWidth() / 2 || y == getPoint().y + height / 2 || y == getPoint().y - height / 2)
			{
				int tempX = x;
				int tempY = y;
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