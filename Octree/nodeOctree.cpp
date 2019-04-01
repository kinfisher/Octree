#include "nodeOctree.h"



nodeOctree::nodeOctree(pointOctree esqSupIzq, pointOctree esqInfDer, pointOctree _profundidad)
{
	esquinaInferiorDerecha = esqInfDer;
	esquinaSuperiorIzquierda = esqSupIzq;
	profundidad = _profundidad;  //Tendra los limites del eje z
	hoja = true;
	hijos[0] = hijos[1] = hijos[2] = hijos[3] = hijos[4] = hijos[5] = hijos[6] = hijos[7] = 0;
}


nodeOctree::~nodeOctree()
{
}
