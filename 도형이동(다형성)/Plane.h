#ifndef __PLANE_H__
#define __PLANE_H__

#include "Point.h"

const int MAX_X = 80;
const int MAX_Y = 20;

class Plane
{
private :

	int **coordinate;

	void makePlane();
	void deletePlane();

public:
	Plane()
	{
		makePlane();
	}
	~Plane()
	{
		deletePlane();
	}

	int** getPlane();
	void printPlane() const;
};

#endif
