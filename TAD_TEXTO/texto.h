#include <stdio.h>
#include <string.h>
#include <malloc.h>

struct texto
{
	char letra;
	struct texto * proximoTexto;
};

typedef struct texto *Texto;

Texto crearTexto(const char * txt);

Texto anexarLetra(Texto t,char letra);

int obtenerLongitud(Texto t);

int compararTexto(Texto t1,Texto t2);

Texto concatenarTexto(Texto t1,Texto t2);

void imprimirTexto(Texto t);
