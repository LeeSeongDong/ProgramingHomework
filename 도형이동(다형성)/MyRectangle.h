#ifndef __MYRECTANGLE_H__
#define __MYRECTANGLE_H__

#include "Shape.h"

class MyRectangle : public Shape
{
private :
	int height;

public :
	MyRectangle() : Shape()
	{
		height = 4;
	};
	~MyRectangle() {};

	void setHeight(int inputHeight)
	{
		height = inputHeight;
	}

	void putShape() const;
	double getArea() const;
	void changeShape(Plane &plane);
	void setShapeOnPlane(Plane &plane) const;
	void deleteShapeOnPlane(Plane &plane) const;
};

#endif
