#include "texto.h"

Texto crearTexto(const char * txt)
{	
	Texto t = NULL;
	
	int longitud = strlen(txt);
	
	int i= 0;
	
	for(i = 0 ; i < longitud ; i++)
	{
		t = anexarLetra(t,txt[i]);
	}
	
	return t;
}

Texto anexarLetra(Texto t,char letra)
{	
	
	Texto nuevoTexto = (Texto)malloc(sizeof(struct texto));
	nuevoTexto->letra = letra;
	
	if(t == NULL)
	{
		t = nuevoTexto;		
		return t;
	}
	
	Texto temp = t;
	
	while(1)
	{
		if(temp->proximoTexto == NULL)
		{
			temp->proximoTexto = nuevoTexto;
			return t;
		}
		temp = temp->proximoTexto;
	}
	
	return t;
}

int obtenerLongitud(Texto t)
{
	int longitud = 0;
	while(1)
	{
		if(t == NULL)
		{
			return longitud;
		}
		longitud = longitud + 1;
		t = t->proximoTexto;
	}
	return longitud;
}

void imprimirTexto(Texto t)
{
	Texto temporal = t;
	while(temporal != NULL)
	{
		char c = temporal->letra;
		printf("%c",c);
		temporal = temporal->proximoTexto;
	}
}

int compararTexto(Texto t1,Texto t2)
{
	int long1=0,long2=0;
	
	long1 = obtenerLongitud(t1);
	long2 = obtenerLongitud(t2);
	
	if(long1 != long2)
	{
		return 0;
	}

	Texto temporal1 = t1;
	Texto temporal2 = t2;

	while(temporal1 != NULL)
	{
		char c1=temporal1->letra;
		char c2=temporal2->letra;
		
		if(c1 != c2)
		{
			return 0;
		}
		temporal1 = temporal1->proximoTexto;
		temporal2 = temporal2->proximoTexto;
	}

	return 1;
}

Texto concatenarTexto(Texto t1,Texto t2)
{
	Texto textoSalida = t1;
	
	Texto temp = t2;
	while(temp != NULL)
	{
		char c = temp->letra;
		
		textoSalida = anexarLetra(textoSalida,c);
		
		temp = temp->proximoTexto;
	}
	return textoSalida;
}

int main()
{
	Texto t1 = crearTexto("Angelica Gonzalez y ");
	
	Texto t2 = crearTexto("Adriana Gonzalez");
	
	Texto t3 = crearTexto("AbCdEfG");
	
	Texto t4 = crearTexto("AbCdEfG");
	
	t1 = concatenarTexto(t1,t2);
	
	imprimirTexto(t1);
	
	printf("\n");
	
	printf("comparacion %i \n",compararTexto(t3,t4));
	
	return 0;
}
