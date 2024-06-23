#include <stdio.h>
#include <math.h>
#include <conio.h>
#include <stdlib.h>
#include <windows.h>
#include "Estructura_Campo.h"
#include "Pila.h"
#define TAMAX_Y 13//un tamaño mayor no se apreciaria bien a la hora de imprimir
#define TAMAX_X 65

Pila PEZ_X;
Pila PEZ_Y;

int init_struct(int x, int y, int nivel);//realiza la inicializacion y toda la costruccion de la matriz
int init_matrix(int x,int y);
int Calc_minas(int nivel,int x,int y);
void insert_minas ();
void insert_indicadores();
void print_matrix();
void gotoxy(int x,int y);
int rdtsc();
int modulo(int dividendo,int divisor);

//para la estructura OptionsGame

void init_options();
int insert_columnas(int num);
int insert_filas(int num);
int insert_dificultad(int num);
void save_settings();



int init_struct(int x, int y, int nivel){
	int fix; //por si existe algun error en la inicialización
	campo.X=x;
	campo.Y=y;
	campo.dificultad=nivel;
	if(init_matrix(x,y)!=0) return -1;
	if(init_pila(&PEZ_X)!=0&&init_pila(&PEZ_Y)!=0) return -2;
	campo.num_minas=Calc_minas(nivel,x,y);
	fix=campo.num_minas;
	if(fix==-1)return -3;
	insert_minas();
	insert_indicadores();
	return 0;
}

//inicializar en ceroz el espacio de la matriz a ocupar e inicializar el campo según su dificultad
int init_matrix(int x,int y){
	if(x>TAMAX_X || y>TAMAX_Y) return -1;
	int i,j;
	for(j=0;j<y;j++){
		for(i=0;i<x;i++){
			campo.matrix[i][j]=0;
		}
	}
	return 0;
}

//calcular el numero de minas según el nivel
int Calc_minas(int nivel,int x,int y){
	if(x<=1||y<=1){
		return -1;
	}
	
	switch(nivel){
		case 1:
			return (x*y*10)/100;//facil
		case 2:
			return (x*y*15)/100;//normal
		case 3:
			return (x*y*20)/100;//dificil
		case 4:
			return (x*y*30)/100;//hardcore
		default:
			return -1;
	}
}

//genera las minas
void insert_minas (){
	int i,ejex,ejey;
	for(i=0;i<campo.num_minas;i++){
		srand(rdtsc());//crea una semilla random
		ejex=rand()%(campo.X);//añade la ordenada aleatoria que este dentro de el max num de renglones
		srand(rdtsc());
		ejey=rand()%(campo.Y);
		
		if(campo.matrix[ejex][ejey]==-1)
			i--;	//si la posición ya está llena la omite
		else {
			campo.matrix[ejex][ejey]=-1;	//si no, la llena
			push_pila(&PEZ_X,ejex);	//documenta las casillas con minas en una pila
			push_pila(&PEZ_Y,ejey);
		}
	}
}

//realiza el calculo de los indicadores del numero de minas en cada casilla libre
void insert_indicadores(){
	int i,j,k,j_min,j_max,k_max,X,Y;
	for(i=0;i<campo.num_minas;i++){
		X=pop_pila(&PEZ_X);	//verifica en la pila las coordenadas de las minas
		Y=pop_pila(&PEZ_Y);
		//validaciones para no pasarse de los limites de la matriz
		if(X==0) j_min=0;
		else j_min=X-1;
		if(Y==0) k=0;
		else k=Y-1;
		
		if(X==(campo.X-1)) j_max=X;
		else j_max=X+1;
		if(Y==(campo.Y-1)) k_max=Y;
		else k_max=Y+1;
		//explorar y poner los indicadores de las minas
		for(;k<=k_max;k++){
			for(j=j_min;j<=j_max;j++){
				
				if(campo.matrix[j][k]!=-1){//si no hay una mina en la casilla cercana
				
				
					if(campo.dificultad!=4)//sí, no esta en la dificultad 4
						campo.matrix[j][k]++;//aumenta el indicador de numero de minas
					else{
						srand(rdtsc());
						if(rand()%20!=10)//para generar una probabilidad
							campo.matrix[j][k]++;
						else campo.matrix[j][k]=100;//sí el numero aleatorio es 10 se generará un signo de interrogación ahí
					}
					
					
				}
			}
		}
	}
}

//imprimir los valores del campo
void print_matrix(){
	int i,j;
	for(j=0;j<campo.Y;j++){
		printf("\n");
		for(i=0;i<campo.X;i++){
			if(campo.matrix[i][j]<0)
			 printf(" %d",campo.matrix[i][j]);
			else
			 printf("  %d",campo.matrix[i][j]);
		}
	}
}

void gotoxy(int x,int y){
	HANDLE hcon;  
      hcon = GetStdHandle(STD_OUTPUT_HANDLE);  
      COORD dwPos;  
      dwPos.X = x;  
      dwPos.Y= y;  
      SetConsoleCursorPosition(hcon,dwPos); 
}
int rdtsc(){
	__asm__ __volatile__("rdtsc");
}

int modulo(int dividendo,int divisor){
/*  
	el algoritmo por defaut del modulo '%',
    calcula mal con los numeros negativos 
	(almenos en mi caso)
*/	
	int i;
	for(i=0;i*abs(divisor)<abs(dividendo);i++);//busca el cosiente (se pasa por uno; pero eso se aprobecha)
	if(dividendo%divisor==0)//solo calcula bien los numeros multiplos del divisor
		return 0;
	else if(dividendo>=0)
		return dividendo-(abs(divisor)*--i);//dado que se pasa por uno, se resta uno a 'i'
	else
		return dividendo+(abs(divisor)*i);//si el dividendo < 0 => el cosiente por el divisor tiene que ser mayor al absoluto del dividendo, para tener un residuo positivo
		
/*
	como vierón no importa el signo del divisor, pero ai el de el dividendo ejemplos:
	operador default			operador propio
	5%3=2 <-bien				5%3=2 <-bien
	-8%5=-3 <- mal				-8%5=2 <- bien
	30%-10=0 <- bien			30%-10=0 <- bien
	-22%-10=-2 <- mal			-22%-10=8 <- bien
	
	nota: en el operador modulo, no existen resultados negativos,
	independientemente del divisor o el dividendo; el residuo debe ser positivo
*/
}

//-----------***************-------

void init_options(){//lee las configuraciones de settings.bin
	char contenido;
	short i;
	FILE *registro;
	registro = fopen("settings.bin","rb");//abre el archivo binario
	if(registro!=NULL){
		fread(&ajuste.columnas,sizeof(int),1,registro);//lee el num de col
		fread(&ajuste.filas,sizeof(int),1,registro);// || filas
		fread(&ajuste.dificultad,sizeof(int),1,registro);// lee la dificultad
	}
	else{ //sí, no existe el archivo se pone una configuración por default
		gotoxy(13,35);
		printf("ERROR! no se pudieron cargar los datos      ");
		ajuste.columnas = 15;
		ajuste.filas = 5;
		ajuste.dificultad = 1;
	}
	fclose(registro);
	
	//checa la dirección del ejecutable
	//GetModuleFileName( NULL, ajuste.direccion, 100);// funciona igual que la sig función.
	//_fullpath(ajuste.direccion,"BuscaMinas.exe",TAM_direccion);//14 caracteres tiene el "BuscaMinas.exe"
	
	//esto es por si se mueve la dirección del ejecutable
	registro = fopen("direccion.txt","r");//abre el archivo de texto
	if(registro!=NULL){
		
		for(i=0;i<TAM_direccion;i++)//resetea la cadena (si ya habia una guardada)
			ajuste.direccion[i]=0;
		
		contenido = getc(registro);
		
		for(i = 0;contenido != EOF;i++){
			ajuste.direccion[i] = contenido;
			contenido = getc(registro);
		}
	}
	else{ //sí, no existe el archivo se pone una configuración por default
		strcpy(ajuste.direccion, "C:\\Users\\pipel\\Desktop\\carpetas\\ESCOM!!\\MisProyectos\\Buscaminas");
	}
	fclose(registro);
	strcat(ajuste.direccion,"\\recursos");//lo direcciona a la carpeta recursos, donde están los audios
}

int insert_columnas(int num){
	if(num<TAMIN){
		ajuste.columnas = TAMIN;
		return 1;
	}
	if(num>=TAMAX_X){
		ajuste.columnas = TAMAX_X;
		return 2;
	}
	ajuste.columnas = num;
	return 0;
}

int insert_filas(int num){
	if(num<TAMIN){
		ajuste.filas = TAMIN;
		return 1;
	}
	if(num>=TAMAX_Y){
		ajuste.filas = TAMAX_Y;
		return 2;
	}
	ajuste.filas = num;
	return 0;
}

int insert_dificultad(int num){
	if( num < 1 || num > 4){
		ajuste.dificultad = modulo(num,4);
		return 1;
	}
	ajuste.dificultad = num;
	return 0;
}

void save_settings(){
	FILE *registro;
	registro = fopen("settings.bin","wb");
	if(registro!=NULL){
		fwrite(&ajuste.columnas,sizeof(int),1,registro);
		fwrite(&ajuste.filas,sizeof(int),1,registro);
		fwrite(&ajuste.dificultad,sizeof(int),1,registro);
		play_sound("return");
	}
	else{
		gotoxy(13,35);
		printf("ERROR! no se pudieron guardar los datos      ");
		play_sound("fall");
	}
	fclose(registro);
}
