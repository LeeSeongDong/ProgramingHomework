#include "ShapeList.h"

void ShapeList::doubleCapacity()
{
	Shape** newShapeList = new Shape*[2 * capacity];

	for (int i = 0; i < size; ++i)
	{
		newShapeList[i] = shapeList[i];
	}

	capacity *= 2;

	delete[] shapeList;

	shapeList = newShapeList;
}

bool ShapeList::isFull()
{
	if (size == capacity)
	{
		return true;
	}
	else
	{
		return false;
	}
}

void ShapeList::deleteShapeList()
{
	for (int i = 0; i < size; ++i)
	{
		delete shapeList[i];
	}

	delete[]shapeList;
}

void ShapeList::insert(char type, Plane &plane)
{
	if (isFull())
	{
		doubleCapacity();
	}

	switch (type)
	{
	case 't':
	{
		shapeList[size] = new Triangle();
		break;
	}
	case 'r':
	{
		shapeList[size] = new MyRectangle();
		break;
	}
	case 'c':
	{
		shapeList[size] = new Circle();
		break;
	}
	default:
		break;;
	}

	shapeList[size]->setShapeOnPlane(plane);

	++size;

	sort(size-1);
}

void ShapeList::deleteShape(int num, Plane &plane)
{
	shapeList[num]->deleteShapeOnPlane(plane);
	delete shapeList[num];

	--size;

	if (num == size)
	{
		return;
	}
	else
	{

		shapeList[num] = shapeList[size];
		sort(num);
	}
}

Shape* ShapeList::getShape(int num)
{
	return shapeList[num];
}

void ShapeList::sort(int index)
{
	int newIndex = 0;

	for (int i = 0; i < size; ++i)
	{
		if (shapeList[i]->getArea() > shapeList[index]->getArea() && i != index )
		{
			newIndex = i;
			break;
		}
		
		if (i == size - 1)
		{
			newIndex = size - 1;
		}
	}

	Shape* temp = shapeList[index];

	if (newIndex > index)
	{
		for (int i = index; i < newIndex; ++i)
		{
			shapeList[i] = shapeList[i + 1];
		}
	}
	else
	{
		for (int i = index; i > newIndex; --i)
		{
			shapeList[i] = shapeList[i - 1];
		}
	}

	shapeList[newIndex] = temp;
}

