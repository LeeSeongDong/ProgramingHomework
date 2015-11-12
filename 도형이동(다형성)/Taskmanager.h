#ifndef __TASKMANAGER_H__
#define __TASKMANAGER_H__

#include "FigureHandler.h"

class Taskmanager
{
private :

public :
	Taskmanager() {};
	~Taskmanager() {};

	//도형이동모드
	void figureMoveMode(ShapeList &sl, FigureHandler &fh, Plane &plane);

	//사용자입력모드
	void putShapeList(ShapeList &sl);
	void insertShape(ShapeList &sl, Plane &plane);
	void deleteShape(ShapeList &sl, Plane &plane);
	void moveShape(ShapeList &sl);
	void changeShape(ShapeList &sl, Plane &plane);

	//실행
	void runPgm(ShapeList &sl, FigureHandler &fh, Plane &plane);
};

#endif
