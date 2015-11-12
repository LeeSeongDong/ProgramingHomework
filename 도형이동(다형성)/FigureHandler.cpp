#include "FigureHandler.h"

void FigureHandler::printPlane(Plane &plane) const
{
	plane.printPlane();
}

void FigureHandler::insertShapeOnPlane(const Shape *s, Plane &plane)
{
	s->setShapeOnPlane(plane);
}

void FigureHandler::deleteShapeOnPlane(const Shape *s, Plane &plane)
{
	s->deleteShapeOnPlane(plane);
}

void FigureHandler::moveShapeOnPlane(Shape *s, Plane &plane)
{
	s->deleteShapeOnPlane(plane);

	Point p = s->getPoint();
	p += s->getVariationPoint();
	if (p.x < 0)
	{
		p.x += (MAX_X - 1);
	}
	if (p.y < 0)
	{
		p.y += (MAX_Y - 1);
	}
	s->setPoint(p.x % (MAX_X - 1), p.y % (MAX_Y - 1));

	s->setShapeOnPlane(plane);
}

void FigureHandler::updatePlane(ShapeList &sl, Plane &plane)
{
	int size = sl.getSize();

	for (int i = 0; i < size; ++i)
	{
		moveShapeOnPlane(sl.getShape(i), plane);
	}
}

void FigureHandler::deleteVariationPoint(ShapeList &sl)
{
	int size = sl.getSize();

	for (int i = 0; i < size; ++i)
	{
		sl.getShape(i)->setVariationPoint(0, 0);
	}
}

void FigureHandler::figureMode(ShapeList &sl, Plane &plane)
{
	system("cls");
	for (int i = 0; i < 10; ++i)
	{
		printPlane(plane);
		updatePlane(sl, plane);
		Sleep(1000);
		system("cls");
	}

	deleteVariationPoint(sl);
}