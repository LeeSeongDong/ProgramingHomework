#include "Plane.h"

void Plane::makePlane()
{
	coordinate = new int*[MAX_Y];

	for (int i = 0; i < MAX_Y; ++i)
	{
		coordinate[i] = new int[MAX_X];
	}

	for (int i = 0; i < MAX_Y; ++i)
	{
		for (int j = 0; j < MAX_X; ++j)
		{
			coordinate[i][j] = 0;
		}
	}
}

void Plane::deletePlane()
{
	for (int i = 0; i < MAX_Y; ++i)
	{
		delete []coordinate[i];
	}

	delete[]coordinate;
}

int** Plane::getPlane()
{
	return coordinate;
}

void Plane::printPlane() const
{
	for (int i = MAX_Y-1; i >= 0; --i)
	{
		for (int j = 0; j < MAX_X; ++j)
		{
			if (coordinate[i][j] > 0)
			{
				cout << "*";
			}
			else
			{
				cout << " ";
			}
		}
		cout << endl;
	}
}
