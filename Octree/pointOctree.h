#pragma once
#include <iostream>
using namespace std;

class pointOctree
{
public:
	pointOctree();
	pointOctree(double, double);
	double coordX, coordY,coordZ;
	pointOctree(double, double,double);
	void imprimirPoint();
	void imprimirCoord();
	~pointOctree();
};

