#ifndef __CIRCLE_H__
#define __CIRCLE_H__

#include "Shape.h"

const double PI = 3.14;

class Circle : public Shape
{
private :

public :
	Circle() {};
	~Circle() {};

	void putShape() const;
	double getArea() const;
	void changeShape(Plane &plane);
	void setShapeOnPlane(Plane &plane) const;
	void deleteShapeOnPlane(Plane &plane) const;
};

#endif
