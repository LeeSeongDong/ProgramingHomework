#ifndef __TRIANGLE_H__
#define __TRIANGLE_H__

#include "Shape.h"

class Triangle : public Shape
{
private :
	int height;

public :
	Triangle() : Shape()
	{
		height = 4;
	};
	~Triangle() {};

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
