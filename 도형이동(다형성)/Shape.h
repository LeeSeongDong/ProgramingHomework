#ifndef __SHAPE_H__
#define __SHAPE_H__

#include "Plane.h"

class Shape
{
private :
	int width;
	Point point;
	Point variationPoint;

public :
	Shape()
	{
		width = 4;
		point.x = MAX_X / 2;
		point.y = MAX_Y / 2;
		variationPoint.x = 0;
		variationPoint.y = 0;
	};
	~Shape() {};

	void setWidth(int inputWidth)
	{
		width = inputWidth;
	}

	int getWidth() const
	{
		return width;
	}


	void setPoint(int x, int y)
	{
		point.x = x;
		point.y = y;
	}
	void setVariationPoint(int x, int y)
	{
		variationPoint.x = x;
		variationPoint.y = y;
	}
	Point getPoint() const
	{
		return point;
	}
	Point getVariationPoint() const
	{
		return variationPoint;
	}

	virtual void putShape() const = 0;
	virtual double getArea() const = 0;
	virtual void changeShape(Plane &plane) = 0;
	virtual void setShapeOnPlane(Plane &plane) const = 0;
	virtual void deleteShapeOnPlane(Plane &plane) const = 0;
};

#endif
