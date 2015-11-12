#ifndef __FIGUREHANDLER_H__
#define __FIGUREHANDLER_H__

#include "IoHandler.h"

class FigureHandler
{
private :

	void printPlane(Plane &plane) const;//도형출력
	void moveShapeOnPlane(Shape *s, Plane &plane);//도형이동
	void updatePlane(ShapeList &sl, Plane &plane);
	void insertShapeOnPlane(const Shape *s, Plane &plane);//도형추가
	void deleteShapeOnPlane(const Shape *s, Plane &plane);//도형삭제
	void deleteVariationPoint(ShapeList &sl);//변화량0으로 세팅

public :
	FigureHandler() {};
	~FigureHandler() {};
	
	void figureMode(ShapeList &sl, Plane &plane);
};

#endif
