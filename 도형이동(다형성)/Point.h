#ifndef __POINT_H__
#define __POINT_H__

#include "Header.h"

struct Point
{
	int x;
	int y;

	void operator+=(const Point &p)
	{
		x += p.x;
		y += p.y;
	}
};



#endif
