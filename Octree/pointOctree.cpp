#include "pointOctree.h"



pointOctree::pointOctree()
{
	coordX = coordY = 0;
}

pointOctree::pointOctree(double _x, double _y,double _z)
{
	coordX = _x;
	coordY = _y;
	coordZ = _z;

}

pointOctree::pointOctree(double _x, double _y)
{
	coordX = _x;
	coordY = _y;
	coordZ = 0;
}



pointOctree::~pointOctree()
{
}
