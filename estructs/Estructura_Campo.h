#ifndef _USER_H
#define _USER_H

#include <stdio.h>
#include <stdlib.h>
#include "ListaDoble.h"

#define Tamano_MaximoX 50
#define Tamano_MaximoY 50

typedef struct Campo{
	int dificultad;
	int X,Y;//numero de columnas y numero de filas respectivamente.
	int num_minas;
	ListaD *mapa;
}Minas;

void gotoxy(int x,int y);
int rdtsc();
int Calc_minas(int nivel,int x,int y);//calcula el numero de minas dependiendo del tamaño y dificultad
void init_Matrix(Minas *campo,int nivel,int x,int y);

#endif
