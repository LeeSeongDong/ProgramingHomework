#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "FigureHandler.h"

class Taskmanager
{
private :

public :
	Taskmanager() {};
	~Taskmanager() {};

	//�����̵����
	void figureMoveMode(ShapeList &sl, FigureHandler &fh, Plane &plane);

	//������Է¸��
	void putShapeList(ShapeList &sl);
	void insertShape(ShapeList &sl, Plane &plane);
	void deleteShape(ShapeList &sl, Plane &plane);
	void moveShape(ShapeList &sl);
	void changeShape(ShapeList &sl, Plane &plane);

	//����
	void runPgm(ShapeList &sl, FigureHandler &fh, Plane &plane);
};

#endif
