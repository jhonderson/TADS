#include <stdio.h>
#include <string.h>
#include <malloc.h>
#include <math.h>

struct arbol
{
	//1 si el dato es un operando, 0 si el dato es un operador 
	int operando;
	
	//dato que puede ser un operador o un operando
	double dato;
	
	//sub arbol izquierdo
	struct arbol * arbolIzquierdo;
	
	//sub arbol derecho
	struct arbol * arbolDerecho;
};

typedef struct arbol * Arbol;

Arbol crearArbol(int exp[],int control[], int i,int f);

double evaluarArbol(Arbol a);

void imprimirArbol(Arbol a);
