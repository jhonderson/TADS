#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct hojaCalculo
{
	int altura;
	int anchura;
	int **datos;
};

typedef struct hojaCalculo * HojaCalculo;

HojaCalculo crearHojaCalculo();

void redimensionar(HojaCalculo *,int,int);

int busqueda(HojaCalculo,int,char);

void ordenamiento(int,int);
