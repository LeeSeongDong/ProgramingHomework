#ifndef __SHAPELIST_H__
#define __SHAPELIST_H__

#include "MyRectangle.h"
#include "Circle.h"
#include "Triangle.h"

class ShapeList
{
private :
	Shape** shapeList;
	int capacity;
	int size;

	void doubleCapacity();
	bool isFull();
	void deleteShapeList();

public :
	ShapeList()
	{
		capacity = 4;
		size = 0;

		shapeList = new Shape*[capacity];
	};
	~ShapeList()
	{
		deleteShapeList();
	};

	int getSize()
	{
		return size;
	}
	void insert(char type, Plane &plane);
	void deleteShape(int num, Plane &plane);
	Shape* getShape(int num);
	void sort(int index);
};

#endif
