#include "pointOctree.h"



pointOctree::pointOctree()
{
	coordX = coordY = coordZ = 0;
}

pointOctree::pointOctree(double _x, double _y,double _z)
{
	coordX = _x;
	coordY = _y;
	coordZ = _z;

}

void pointOctree::imprimirPoint()
{
	cout << "punto en x: " << coordX << endl;
	cout << "punto en y: " << coordY << endl;
	cout << "punto en z: " << coordZ << endl;
}

void pointOctree::imprimirCoord()
{
	cout << "coordenada x: " << coordX << endl;
	cout << "coordenada y: " << coordY << endl;
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
