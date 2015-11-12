#ifndef __FIGUREHANDLER_H__
#define __FIGUREHANDLER_H__

#include "IoHandler.h"

class FigureHandler
{
private :

	void printPlane(Plane &plane) const;//�������
	void moveShapeOnPlane(Shape *s, Plane &plane);//�����̵�
	void updatePlane(ShapeList &sl, Plane &plane);
	void insertShapeOnPlane(const Shape *s, Plane &plane);//�����߰�
	void deleteShapeOnPlane(const Shape *s, Plane &plane);//��������
	void deleteVariationPoint(ShapeList &sl);//��ȭ��0���� ����

public :
	FigureHandler() {};
	~FigureHandler() {};
	
	void figureMode(ShapeList &sl, Plane &plane);
};

#endif
