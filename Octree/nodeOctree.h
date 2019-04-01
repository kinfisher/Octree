#pragma once
#include "pointOctree.h"
#include <vector>
using namespace std;

class nodeOctree
{
public:
	nodeOctree(pointOctree,pointOctree,pointOctree);  //(esquina superior izquierda,esquina inferior derecha , profundidad en z)
	vector<pointOctree> num_puntos;
	pointOctree esquinaSuperiorIzquierda;
	pointOctree esquinaInferiorDerecha;
	pointOctree profundidad;  // 
	bool hoja;
	nodeOctree* hijos[8];

	~nodeOctree();
};

