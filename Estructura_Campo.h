#ifndef _USER_H
#define _USER_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "Lista_Doble.h"
#define TAMAX_Y 13//un tamaño mayor no se apreciaria bien a la hora de imprimir
#define TAMAX_X 65
#define TAMIN 3 //el tamaño minimo para columnas y filas
#define TAM_direccion 255
typedef struct {
	int dificultad;
	int X,Y;//numero de columnas y numero de filas respectivamente.
	int num_minas;
	int matrix[TAMAX_X][TAMAX_Y];//Matriz que representa el campo de juego
}Minas;

typedef struct {
	int columnas,filas;
	int dificultad;
	char direccion[TAM_direccion];
}OptionsGame;

Minas campo;
DobleLista explorados;
OptionsGame ajuste;

void gotoxy(int x,int y);
int rdtsc();
int Calc_minas(int nivel,int x,int y);//calcula el numero de minas dependiendo del tamaño y dificultad
void init_Matrix(Minas *campo,int nivel,int x,int y);

#endif
