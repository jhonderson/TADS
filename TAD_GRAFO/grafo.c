#include "grafo.h"

Grafo crearGrafo(int n, int m)
{
	Grafo g = (Grafo)malloc(sizeof(struct grafo));
	
	int i=0,j=0;
	
	for (i=0; i<n ; i++ )
	{
		g->v[i]=0;
	}
	
	for(i = 0; i < m ; i++)
	{		
		for (j=0; j<3 ; j++ )
	    {
			g->e[i][j]=0;
	    }
	}
	
	g->n= n;
	g->m= m;
	
	return g;
}

Grafo insertarVertice(Grafo g,int v)
{
	int i = 0; 
	for(i = 0 ; i < g->n ; i++)
	{
		if(g->v[i] == 0)
		{
			g->v[i] = v;
			break;
		}
	}
	return g;
}

Grafo insertarArista(Grafo g,int v1,int v2,int c)
{
	int i = 0,j = 0;
	for(i = 0 ; i < g->m ; i++)
	{
		if(g->e[i][0] == 0)
		{
			g->e[i][0] = v1;
			g->e[i][1] = v2;
			g->e[i][2] = c;
			break;
		}
	}
	return g;
}

int obtenerNumeroVertices(Grafo g)
{
	return g->n;
}

int obtenerNumeroAristas(Grafo g)
{
	return g->m;
}

int obtenerCostoArista(Grafo g,int v1,int v2)
{
	int i = 0,j = 0,c = -1;
	for(i = 0 ; i < g->m ; i++)
	{
		if((g->e[i][0] == v1) && (g->e[i][1] == v2))
		{
			c = g->e[i][2];
			return c;
		}
	}
	return c;
}

int main()
{
	Grafo g = crearGrafo(6, 6);
	
	g = insertarVertice(g,1);
	g = insertarVertice(g,3);
	g = insertarVertice(g,5);
	g = insertarVertice(g,7);
	g = insertarVertice(g,8);
	g = insertarVertice(g,10);
	
	g = insertarArista(g,1,3,2);
	g = insertarArista(g,3,10,8);
	g = insertarArista(g,3,5,3);
	g = insertarArista(g,3,8,29);
	g = insertarArista(g,5,10,5);
	g = insertarArista(g,10,7,1);
	
	int matrizAdyacente[g->n][g->n];
	int path[g->n][g->n];
	
	int infinito = -1;
	int i = 0, j = 0, k = 0;
	
	//Se calcula la matriz de adyacencia
	for(i = 0; i<g->n ; i++)
	{
		for(j = 0; j<g->n ; j++)
		{
			matrizAdyacente[i][j] = infinito;
			path[i][j] = infinito;
			
			int estanConectados = obtenerCostoArista(g,g->v[i],g->v[j]);
			
			if(estanConectados != -1)
			{
				matrizAdyacente[i][j] = estanConectados;
				path[i][j] = estanConectados;
			}
		}
	}
	
	//Se calcula el menor costo entre cada vertice a cada vertice
	for(i = 0 ; i < g->n ; i++)
		path[i][i] = 0;

	for(k = 0; k < g->n; k++)
	{
		for(i = 0; i < g->n; i++)
		{
			for(j = 0; j < g->n; j++)
			{
				int dt=0;
				
				if((path[i][k] < 0) || (path[k][j] < 0))
					dt=-1;
					
				else
					dt = path[i][k] + path[k][j];
				
				if((dt < 0) || (path[i][j]<0))
				{
					if((path[i][j]<0)&&(dt >=  0))
						path[i][j] = dt;
						
					else
						continue;
				}
				
				else if(path[i][j] > dt)
					path[i][j] = dt;
			}
		}
	}

	int tiempoMaximo = 30;
	int v1 = 1;
	int v2 = 0; //lo da el usuario
	
	/*
	 * --------------------------------------------------------------- imprimir datos de prueba 
	 * */
	printf("--------------------------------------------------------------");
	for(i = 0; i < g->n; i++)
	{
		for(j = 0; j < g->n; j++)
		{
			int d = path[i][j];
			printf(" %i",d);
		}
		printf("\n");
	}
	printf("-------------------------------------------------------------- \n");
	for(j = 0; j < g->n; j++)
	{
		int t = g->v[j];
		printf(" %i",t);
	}
	printf("-------------------------------------------------------------- \n");
	for(j = 0; j < g->m; j++)
	{
		int t1 = g->e[j][0];
		int t2 = g->e[j][1];
		int t3 = g->e[j][2];
		printf(" %i",t1);
		printf(" %i",t2);
		printf(" %i",t3);
		printf(",");
		
	}
	printf("-------------------------------------------------------------- \n");
	/*
	 * ---------------------------------------------------------------
	 * */
	
	printf ("digite el vertice final : ");
	scanf("%i",&v2);
	
	int o =0,p=0;

	for(i=0 ; i<g->n ; i++ )
	{
		if(g->v[i] == v1)
		{
			o = i;
		}
		if(g->v[i] == v2)
		{
			p = i;
		}
	}

	if(path[o][p] > tiempoMaximo)
	{
		printf("no se puede garantizar el costo maximo T = %i",tiempoMaximo);
		printf("\n");
	}
	else
	{
		printf("costo minimo : %i",path[o][p]);
		printf("\n");
	}
	
	return 0;
}
