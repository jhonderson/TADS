#include "hojaCalculo.h"

HojaCalculo crearHojaCalculo(int h,int w)
{
	HojaCalculo hoja = (HojaCalculo)malloc(sizeof(struct hojaCalculo));
	
	hoja->datos = malloc(sizeof(int * [h]));
	
	int i = 0;
	int j = 0;
	
	for(i = 0 ; i < h ; i++)
	{
		hoja->datos[i] = malloc(sizeof(int [w]));
		
		for(j = 0 ; j < w ; j++)
			hoja->datos[i][j]=0;
	}
	
	hoja->altura = h;
	hoja->anchura = w;
	
	return hoja;
}

void redimensionar(HojaCalculo *hoja,int h,int w)
{
	(*hoja) = NULL;
	(*hoja) = crearHojaCalculo(h,w);	
}

int busqueda(HojaCalculo hoja,int fila,char columna)
{
	int i = fila;
	int j = (int)columna;
	
	if((j >= 97) && (j <= 122))
	{
		j = j - 97;
	}
	else if((j >= 65) && (j <= 90))
	{
		j = j - 65;
	}
	
	int resultado = 0;
	
	if(((i >= 0) && (i < hoja->altura))&&((j >= 0) && (j < hoja->anchura)))
		resultado = hoja->datos[i][j];
	else
		resultado = -1;
	
	return resultado;
}

void ordenamiento(int fila_columna,int que_se_ordenara)
{
	
}

int main()
{
	
	HojaCalculo hoja = crearHojaCalculo(10,10);
	
	int i = 0 , j = 0;
	
	for(i = 0 ; i < 10 ; i++)
	{
		for(j = 0 ; j < 10 ; j++)
		{
			printf(" %i ",hoja->datos[i][j]);
	    }
	}
	
	printf("\n -------------------------------------------------------- \n");
	
	redimensionar(&hoja,20,20);
	
	printf("\n ******************************************************** \n");
	
	printf("epa %i , %i \n",hoja->altura,hoja->anchura);
	
	for(i = 0 ; i < 20 ; i++)
	{
		for(j = 0 ; j < 20 ; j++)
		{
			printf(" %i ",hoja->datos[i][j]);
	    }
	}
	
	printf("\n ++++++++++++++++++++++++++++++++++++++++++++++++++++++++ \n");
	
	hoja->datos[2][2] = 456;
	
	printf(" %i \n",busqueda(hoja,2,'c'));
	
	return 0;
}
