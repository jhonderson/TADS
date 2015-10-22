#include "arbol.h"

/*
	precondicion : posibles espacios vacios
	postcondicion : no tener en cuenta esos espacios
*/

void ignorarEspacios(const char * array , int *vv)
{
	int v=*vv;
	char t = array[v];
	
	while(t == ' ')
	{
		v++;
		t = array[v];
	}
	*vv = v;
}

/*
	precondicion : variable tipo char (caracter)
	postcondicion : variable tipo int (entera) obtenida de realizar una conversion del caracter inicial
*/

int charAEntero(char t)
{
	return t - '0';
}

/*
	precondicion : expresion aritmetica en forma de texto
	postcondicion : numero en determinada posicion de la expresion aritmetica
*/

int obtenerNumero(const char * array , int *vv)
{
	int v=*vv;
	
	int valor=0,c = 0;
	char t = array[v];
	
	while(isdigit(t))
	{
		valor = valor*10 + (charAEntero(t));
		
		v++;
		c++;
		
		t = array[v];
	}
	*vv = v;
	
	return valor;
}

/*
	precondicion : x y y, enteros, (y positivo)
	postcondicion : resultado de elevar x a la potencia y
*/

int pot(int x, int y)
{
	int resultado = 1;
	int i = 0;
	for(i=0;i<y;i++)
	{
		resultado = resultado * x;
	}
	return resultado;
}

/*
	precondicion : un rango y una posicion, que deberia estar en dicho rango
	postcondicion : si la posicion esta en el rango, se retorna la posicion , de lo contrario, se retorna un extremo dependiendo de la posicion 
*/

int validarPosicion(int posicion,int inferior,int superior)
{
	if(posicion <= inferior)
		return inferior;
	else if(posicion >= superior)
		return superior-1;
	else
		return posicion;
}

/*
	precondicion : expresion aritmetica en texto en notacion infija
	postcondicion : arreglo con elementos (operandos u operadores) de la expresion aritmetica, en notacion postfija
*/

void expresionPostFijaEqv(const char * exp, int expresionFinal[] , int control[], int *cabecera)
{
	int longitud = strlen(exp);
	
	int pila[longitud];
	
	int cabeceraPila1=0,cabeceraPila2=0;
	
	int i = 0;
	
	while(i < longitud)
	{
		ignorarEspacios(exp, &i);
		
		char v = exp[i];
		
		if(v == '(')
		{
			pila[validarPosicion(cabeceraPila2,0,longitud)] = v;
			cabeceraPila2++;
		}
		else if(v == ')')
		{
			int bool = 1 ;
			while(bool)
			{
				char op = pila[validarPosicion(cabeceraPila2-1,0,longitud)];
				pila[validarPosicion(cabeceraPila2-1,0,longitud)] = ' ';
				cabeceraPila2--;
				
				if(op == '(')
					bool = 0;
				else
				{
					expresionFinal[validarPosicion(cabeceraPila1,0,longitud)] = (int)op;
					control[validarPosicion(cabeceraPila1,0,longitud)] = 0;
					cabeceraPila1++;
				}
			}
		}
		else if(isdigit(v))
		{
			int valor = obtenerNumero(exp, &i);
			
			expresionFinal[validarPosicion(cabeceraPila1,0,longitud)] = valor;
			control[validarPosicion(cabeceraPila1,0,longitud)] = 1;
			cabeceraPila1++;
			
			i--;
		}
		else
		{
			int bool = 1 ;
			while(bool)
			{
				if(((pila[validarPosicion(cabeceraPila2-1,0,longitud)]) == '(' ) || (cabeceraPila2 == 0))
				{
					pila[validarPosicion(cabeceraPila2,0,longitud)] = v;
					cabeceraPila2++;
					
					bool = 0;
				}
				else if(((v == '/') || (v == '*')) && ((pila[validarPosicion(cabeceraPila2-1,0,longitud)] == '+') || (pila[validarPosicion(cabeceraPila2-1,0,longitud)] == '-')))
				{
					pila[validarPosicion(cabeceraPila2,0,longitud)] = v;
					cabeceraPila2++;
					
					bool = 0;
				}
				else
				{
					char op = pila[validarPosicion(cabeceraPila2 - 1,0,longitud)];
					pila[validarPosicion(cabeceraPila2 - 1,0,longitud)] = ' ';
					cabeceraPila2--;
					
					expresionFinal[validarPosicion(cabeceraPila1,0,longitud)] = (int)op;
					control[validarPosicion(cabeceraPila1,0,longitud)] = 0;
					cabeceraPila1++;
				}
			}
		}
		i++;
	}
	int bool = 1 ;
	while(bool)
	{
		if(cabeceraPila2 == 0)
			bool = 0;
		else
		{
			char op = pila[validarPosicion(cabeceraPila2 - 1,0,longitud)];
			pila[validarPosicion(cabeceraPila2 - 1,0,longitud)] = ' ';
			cabeceraPila2--;
			expresionFinal[validarPosicion(cabeceraPila1,0,longitud)] = (int)op;
			control[validarPosicion(cabeceraPila1,0,longitud)] = 0;
			cabeceraPila1++;
		}
	}
	
	*cabecera = cabeceraPila1;
}

/*
	precondicion : arreglo con elementos (operandos u operadores) de una expresion aritmetica, en notacion postfija
	postcondicion : Arbol de sintaxis, donde cada nodo es un operando o un operador
*/

Arbol crearArbol(int exp[],int control[], int i,int f)
{
	Arbol a = (Arbol)malloc(sizeof(struct arbol));
	
	int pos = 0;
	char v;
	
	if(i > f)
	{
		return NULL;
	}
	
	if(i == f)
	{
		a->dato = exp[i];
		a->operando = control[i];
		
		a->arbolIzquierdo = NULL;
		a->arbolDerecho = NULL;
		return a;
	}
	
	else
	{
		a->dato = exp[validarPosicion(f-1,0,f)];
		a->operando = control[validarPosicion(f-1,0,f)];
		
		if((f-1 - i)==2)
		{
			a->arbolIzquierdo = crearArbol(exp,control,i,i);
			a->arbolDerecho = crearArbol(exp,control, i+1,i+1);			
			return a;
		}
		
		int ultimaPos = validarPosicion(f-2,0,f);
		
		int aa = 0 , bb = 0;
		while(ultimaPos >= i)
		{ 
			if(control[ultimaPos])
			{
				bb++;
			}
			
			else
			{
				aa++;
			}
			ultimaPos--;
			if(bb > aa)
			{
				break;
			}
		}		
		a->arbolIzquierdo = crearArbol(exp,control,i,ultimaPos+1);
		a->arbolDerecho = crearArbol(exp,control, ultimaPos+1,f-1);
	}
	
	return a;
}

/*
	precondicion : Arbol de sintaxis
	postcondicion : resultado de evaluar el arbol de sintaxis
*/

double evaluarArbol(Arbol a)
{
	double resultado = 0;
	
	if(a == NULL)
	{
		return resultado = 0;
	}
	
	int operando = a->operando;
	
	if(operando)
	{
		resultado = (double)a->dato;
	}
	
	else
	{
		int operador = (int)a->dato;
		if(operador == '+')
		{
			resultado = (evaluarArbol(a->arbolIzquierdo))+(evaluarArbol(a->arbolDerecho));
		}
		else if(operador == '-')
		{
			resultado = (evaluarArbol(a->arbolIzquierdo))-(evaluarArbol(a->arbolDerecho));
		}
		else if(operador == '*')
		{
			resultado = (evaluarArbol(a->arbolIzquierdo))*(evaluarArbol(a->arbolDerecho));
		}
		else if(operador == '/')
		{
			resultado = (evaluarArbol(a->arbolIzquierdo))/(evaluarArbol(a->arbolDerecho));
		}
	}
	
	return resultado;
}

/*
	precondicion : Arbol de sintaxis
	postcondicion : impresion de la expresion aritmetica equivalente al arbol de sintaxis, en notacion prefija
*/

void imprimirArbol(Arbol a)
{
	if(a == NULL)
	{
		return;
	}
	
	
	int operando = a->operando;
	
	if(operando)
	{
		printf("%.2f",a->dato);
	}
	
	else
	{
		int operador = (int) a->dato;
		
		printf("(");
		imprimirArbol(a->arbolIzquierdo);
		printf(")");
		
		if(operador == '+')
		{
			printf("+");
		}
		else if(operador == '-')
		{
			printf("-");
		}
		else if(operador == '*')
		{
			printf("*");
		}
		else if(operador == '/')
		{
			printf("/");
		}
		
		printf("(");
		imprimirArbol(a->arbolDerecho);
		printf(")");
	}
}

int main()
{	
	//const char * e = "4 - 2";
	//const char * e = " 5 * (4 - 2)";
	//const char * e = " 7 - (5 / (5 * (4 - 2)))";
	//const char * e = " 7 + 5 + ((4 / 2) - ((5 * 9) / 15))";
	const char * e = " (4 / (5 - (9 / 3))) + ( 4 *  5 + 6 ) + ((4 / 2) - ((5 * 9) / 15))";
	
	int longitud = strlen(e);
	int cabecera = 0;
	
	int exp[longitud];
	int control[longitud];
	
	expresionPostFijaEqv(e,exp,control,&cabecera);
	
	Arbol a = crearArbol(exp,control,0,cabecera);
		
	imprimirArbol(a);
	
	printf(" = %.2f \n",evaluarArbol(a));
		
	return 0;
}
