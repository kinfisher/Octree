#pragma once

#include "nodeOctree.h"


class Octree
{	
public:
	Octree(pointOctree,pointOctree,pointOctree,int);
	int max_points;
	bool insertar(pointOctree);
	bool buscar(pointOctree,nodeOctree*&);
	nodeOctree *head;
	void dibujar(nodeOctree*&);
	void subdivision(nodeOctree*&);


	~Octree();
};

