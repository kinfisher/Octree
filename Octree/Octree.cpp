#include "Octree.h"
#include <iostream>
#include <GL/glut.h>

using namespace std;

Octree::Octree(pointOctree esqSupizqu,pointOctree esqInfDer,pointOctree _profundidad,int maximo)
{
	head = new nodeOctree(esqSupizqu, esqInfDer, _profundidad);
	max_points = maximo;

}



Octree::~Octree()
{
}


bool Octree::insertar(pointOctree nuevo)
{
	nodeOctree *P;
	if (buscar(nuevo, P))
	{
		return 0;
	}
		//cout << "LEOmarsh" << endl;

	P->num_puntos.push_back(nuevo);
	

	if (P->num_puntos.size() > max_points)
	{
	
		subdivision(P);

	}

	//cout << "awanta" << endl;
	return 1;
}

bool Octree::buscar(pointOctree nuevo, nodeOctree*& P)
{
	int le_hijos;
	P = head;
	double xmedio, ymedio, zmedio;
	xmedio = (P->esquinaInferiorDerecha.coordX + P->esquinaSuperiorIzquierda.coordX) / 2;
	ymedio = (P->esquinaInferiorDerecha.coordY + P->esquinaSuperiorIzquierda.coordY) / 2;
	zmedio = (P->profundidad.coordX + P->profundidad.coordY) / 2;


	for (P = head; P->hoja != true; P=P->hijos[le_hijos])
	{
		if (nuevo.coordX > xmedio)
		{
			if (nuevo.coordY > ymedio)
			{
				if (nuevo.coordZ > zmedio)
				{
					le_hijos = 5;
				}
				else
				{
					le_hijos = 1;
				}


			}
			else if (nuevo.coordZ > zmedio)
			{
				le_hijos = 7;
			}
			else
			{
				le_hijos = 3;
			}

		}
		else if (nuevo.coordY > ymedio)
		{
			if (nuevo.coordZ > zmedio)
			{
				le_hijos = 4;
			}
			else
			{
				le_hijos = 0;
			}
		}
		else if (nuevo.coordZ < zmedio)
		{
			le_hijos = 6;
		}
		else
		{
			le_hijos = 2;
		}


	}

	for (int i = 0;i < P->num_puntos.size(); i++)
	{
		if (P->num_puntos[i].coordX == nuevo.coordX and P->num_puntos[i].coordY == nuevo.coordY and P->num_puntos[i].coordZ == nuevo.coordZ)
		{
			return 1;
		}
	}
	return 0;

}





void Octree::subdivision(nodeOctree*& P)
{
	int le_hijo;
	P->hoja = false;
	pointOctree medio;
	medio.coordX = (P->esquinaInferiorDerecha.coordX + P->esquinaSuperiorIzquierda.coordX) / 2;
	medio.coordY = (P->esquinaInferiorDerecha.coordY + P->esquinaSuperiorIzquierda.coordY) / 2;
	medio.coordZ = (P->profundidad.coordX + P->profundidad.coordY) / 2;




	P->hijos[0] = new nodeOctree(pointOctree(P->esquinaSuperiorIzquierda.coordX, P->esquinaSuperiorIzquierda.coordY), pointOctree(medio.coordX, medio.coordY), pointOctree(P->profundidad.coordX, medio.coordZ));

	P->hijos[1] = new nodeOctree(pointOctree(medio.coordX, P->esquinaSuperiorIzquierda.coordY), pointOctree(P->esquinaInferiorDerecha.coordX, medio.coordY), pointOctree(P->profundidad.coordX, medio.coordZ));
	
	P->hijos[2] = new nodeOctree(pointOctree(P->esquinaSuperiorIzquierda.coordX,medio.coordY), pointOctree(medio.coordX,P->esquinaInferiorDerecha.coordY), pointOctree(P->profundidad.coordX, medio.coordZ));
	
	P->hijos[3] = new nodeOctree(pointOctree(medio.coordX,medio.coordY), pointOctree(P->esquinaInferiorDerecha.coordX,P->esquinaInferiorDerecha.coordY), pointOctree(P->profundidad.coordX, medio.coordZ));
	
	P->hijos[4] = new nodeOctree(pointOctree(P->esquinaSuperiorIzquierda.coordX, P->esquinaSuperiorIzquierda.coordY), pointOctree(medio.coordX, medio.coordY), pointOctree(medio.coordX,P->profundidad.coordY));
	
	P->hijos[5] = new nodeOctree(pointOctree(medio.coordX, P->esquinaSuperiorIzquierda.coordY),pointOctree(P->esquinaInferiorDerecha.coordX, medio.coordY), pointOctree(medio.coordX, P->profundidad.coordY));
	
	P->hijos[6] = new nodeOctree(pointOctree(P->esquinaSuperiorIzquierda.coordX, medio.coordY), pointOctree(medio.coordX, P->esquinaInferiorDerecha.coordY), pointOctree(medio.coordX, P->profundidad.coordY));
	
	P->hijos[7] = new nodeOctree(pointOctree(medio.coordX, medio.coordY), pointOctree(P->esquinaInferiorDerecha.coordX, P->esquinaInferiorDerecha.coordY), pointOctree(medio.coordX, P->profundidad.coordY));

	cout << "111" << endl;
	for(int i=0;i < P->num_puntos.size();i++)
	{
		if (P->num_puntos[i].coordX > medio.coordX)
		{
			if (P->num_puntos[i].coordY > medio.coordY)
			{
				if (P->num_puntos[i].coordZ < medio.coordZ)
				{
					le_hijo = 5;
				}
				else
				{
					le_hijo = 1;
				}
			}
			else if (P->num_puntos[i].coordZ < medio.coordZ)
			{
				le_hijo = 7;

			}
			else
			{
				le_hijo = 3;
			}
		}
		else if (P->num_puntos[i].coordY > medio.coordY)
		{
			if (P->num_puntos[i].coordZ < medio.coordZ)
			{
				le_hijo = 4;
			}
			else
			{
				le_hijo = 0;
			}
		}
		else if (P->num_puntos[i].coordZ < medio.coordZ)
		{
			le_hijo = 6;
		}
		else
		{
			le_hijo = 2;
		}

		P->hijos[le_hijo]->num_puntos.push_back(P->num_puntos[i]);
	}
	cout << "despues" << endl;
	P->num_puntos.clear();
	
	for (int j = 0; j < 8; j++)
	{
		if (P->hijos[j]->num_puntos.size() > max_points)
		{
			cout << "j  " << j << endl;
			subdivision(P->hijos[j]);
			break;
		}
	}

}

void Octree::dibujar()
{
	nodeOctree *p = head;
	double mx, my, mz;
	if (p->hoja)
	{
		for (int i = 0; i < p->num_puntos.size(); i++)
		{
			glPointSize(5.1);
			glBegin(GL_POINTS);
			glColor3f(0, 0, 255);
			glVertex3d(p->num_puntos[i].coordX, p->num_puntos[i].coordY, p->num_puntos[i].coordZ);
			glEnd();
		}
		return;
	}

	mx = (p->esquinaInferiorDerecha.coordX + p->esquinaSuperiorIzquierda.coordX) / 2;
	my = (p->esquinaInferiorDerecha.coordY + p->esquinaSuperiorIzquierda.coordY) / 2;
	mz = (p->profundidad.coordX + p->profundidad.coordY) / 2;


	glBegin(GL_LINES);
	//lineas horizontales

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordX);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordX);

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordX);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordX);

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordY);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordY);

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordY);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordY);



	//Lineas verticales

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordX);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordX);

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordX);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordX);

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordY);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordY);

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordY);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordY);

	//lineas diagonales 

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordX);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordY);

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordX);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaSuperiorIzquierda.coordY, p->profundidad.coordY);

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordX);
	glVertex3d(p->esquinaSuperiorIzquierda.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordY);

	glColor3d(255, 0, 0);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordX);
	glVertex3d(p->esquinaInferiorDerecha.coordX, p->esquinaInferiorDerecha.coordY, p->profundidad.coordY);

	glEnd();

}

void Octree::_dibujar(nodeOctree *P)
{
	P = head;

}






void Octree::print(nodeOctree* q)
{	
	if (q->hoja == true)
	{
		for (int i = 0; i < q->num_puntos.size(); i++)
		{
			cout << "Los puntos de este nodo son: " << endl;
			q->num_puntos[i].imprimirPoint();
		}
	}

	else
	{
		q->esquinaSuperiorIzquierda.imprimirCoord();
		q->esquinaInferiorDerecha.imprimirCoord();
		q->profundidad.imprimirCoord();

		for (int i = 0; i < 8; i++)
		{
			print(q->hijos[i]);
		}

	}

}



