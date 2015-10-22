#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <malloc.h>

struct grafo
{
	//maximo numero de nodos : 100
	int v[100];
	
	//maximo numero de aristas : 100
	int e[100][3];
	int n;
	int m;
};

typedef struct grafo *Grafo;

Grafo crearGrafo(int n, int m);

Grafo insertarVertice(Grafo g,int v);

Grafo insertarArista(Grafo g,int v1,int v2,int c);

int obtenerNumeroVertices(Grafo g);

int obtenerNumeroAristas(Grafo g);

int obtenerCostoArista(Grafo g,int v1,int v2);
