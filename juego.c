#include <stdio.h>
#include <windows.h>
#include <conio.h>
#include "Lista_Doble.h"
#include "Estructura_campo.h"

char gameMatrix[65][13];

void init_mapa();
void print_mapa();
int update_mapa(int x,int y);
int cavarEnCampo(int x,int y);
int jugar();
void play_sound(char sonido[]);


//inicia el campo de juego para el usuario
void init_mapa(){
	int i,j;
	for(j=0;j<campo.Y;j++){
		for(i=0;i<campo.X;i++){
			gameMatrix[i][j]=254;//254 = cuadrado; tambien -2=cuadrado dado que el numero max de caracteres es de 256
		}
	}
}


//imprime el campo de juego para el usuario
void print_mapa(){
	int i,j;
	int ESI=201,ESD=187,Back=8,tuboV=186;//ESI=Esquina Superior Izquierda (caracter)
	int tubo=205,CS=203,CC=206,CIz=204;
	int CD=185,Cinf=202,EII=200,EID=188;//CS=Conexion Superior
	//comienza la imprecion del juego
	
	//limites superiores
	printf("\n\n\n\t%c",ESI);
	
	for(i=0;i<campo.X;i++)
		printf("%c%c",tubo,CS);
	printf("%c%c",Back,ESD);
	
	//cuerpo
	for(j=0;j<campo.Y;j++){
		
		printf("\n\t%c",tuboV);
		for(i=0;i<campo.X;i++)
			printf("%c%c",gameMatrix[i][j],tuboV);
			
		printf("\n\t");
		if(j!=campo.Y-1){
			printf("%c",CIz);
			for(i=0;i<campo.X;i++)
				printf("%c%c",tubo,CC);
			printf("%c%c",Back,CD);
		}
		//pies
		else{
			printf("%c",EII);
			for(i=0;i<campo.X;i++)
				printf("%c%c",tubo,Cinf);
			printf("%c%c",Back,EID);
		}
	}
	
}

//funcion que actualiza y verifica elementos dados en un campo minado
int update_mapa(int x,int y){
	if(campo.matrix[x][y]<0){
		gameMatrix[x][y]='*';
		return -1;
	}
	if(campo.matrix[x][y]==0){
		gameMatrix[x][y]=' ';//espacio si es 0
		return 0;
	}
	else if(campo.matrix[x][y]>10)
		gameMatrix[x][y]='?';
	else
		gameMatrix[x][y]=campo.matrix[x][y]+48;//48 para que se guarde en caracteres numericos
	return 1;
}

//realiza la excabación de minas
int cavarEnCampo(int x,int y){
	if(gameMatrix[x][y]!=-2 || gameMatrix[x][y]==1)//si se da clik en un campo ya explorado (-2=cuadrado) o marcado como que hay una mina
		return 0;
	int j,k,j_min,j_max,k_max;
	int answer=update_mapa(x,y);//cava en el cuadro elegido
	gotoxy((x*2)+9,(y*2)+9);// se va a la posicion de la pantalla de la mina para imprimir
	printf("%c",gameMatrix[x][y]);
	if (answer==-1)//checa sí no se ha empezado a cavar sobre una mina
		return -1;//si era una mina regresa -1
	
	insertI(&explorados,x,y);
	//validaciones para no pasarse de los limites de la matriz
	if(x==0) j_min=0;
	else j_min=x-1;
	if(y==0) k=0;
	else k=y-1;
		
	if(x==(campo.X-1)) j_max=x;
	else j_max=x+1;
	if(y==(campo.Y-1)) k_max=y;
	else k_max=y+1;
	//explorar y poner los indicadores de las minas
	for(;k<=k_max;k++){
		for(j=j_min;j<=j_max;j++){
			if(campo.matrix[j][k]==0&&search_data(&explorados,j,k)<=0){
				cavarEnCampo(j,k);// realiza la misma operacion con casillas alejadas de cualquier mina
			}
			else if(campo.matrix[j][k]>0&&gameMatrix[j][k]!=1){//si la casilla indica una mina cerca
				update_mapa(j,k); //actualiza la matriz de juego
				if(search_data(&explorados,j,k)<=0)
				insertI(&explorados,j,k);//marca su posición como ya explorada
				gotoxy((j*2)+9,(k*2)+9); //se va a la posición de ese indicador
				printf("%c",gameMatrix[j][k]); //solo imprime el indicador
			}
		}
		Sleep(50);
	}
	return 0;
}

int jugar(){
	short int numMinas = campo.num_minas;
	int x=0,y=0,ans=0;
	char move;
	print_game();
	do{
		gotoxy((x*2)+9,(y*2)+9);
		move=getch();
		switch(move){
			case 'w':
				y=modulo((y-1),campo.Y);
				play_sound("step4");
				Sleep(150);
				break;
			case 's':
				y=modulo((y+1),campo.Y);
				play_sound("step4");
				Sleep(150);
				break;
			case 'a':
				x=modulo((x-1),campo.X);
				play_sound("step4");
				Sleep(150);
				break;
			case 'd':
				x=modulo((x+1),campo.X);
				play_sound("step4");
				Sleep(150);
				break;
			case 13:
				play_sound("cavar");
				ans=cavarEnCampo(x,y);
				break;
			case '+':
				if(gameMatrix[x][y]==-2){//si es un cuadrito (-2 == cuadrito en ascii)
					play_sound("step2");
					printf("%c",219);
					gameMatrix[x][y]=1;//marca la casilla con un cuadro grande
					numMinas--;//reduce el numero teorico de minas
					gotoxy(48,1);
					printf("%d Minas    ",numMinas);//imprime el numero teorico de minas
				}
				break;
			case '{':
				if(gameMatrix[x][y]==1){//si esta en un cuadrado grande
					play_sound("step");
					printf("%c",254);
					gameMatrix[x][y]=254;//marca cuadradito
					numMinas++;//aumenta el numero teorico de minas
					gotoxy(48,1);
					printf("%d Minas    ",numMinas);//imprime el numero teorico de minas
				}
		}
	}while(ans!=-1 && (campo.X*campo.Y-explorados.num_nodos)!=campo.num_minas);
	print_game();
	Sleep(200);
	
	if(ans==-1){
		play_sound("Bomba");
		print_game_lose();
	}
	else{
		print_game_win();
	}
}

/*
	En la sig funcion se reproducen los sonidos
	de la carpeta recursos y solo hace falta escribir el nombre del sonido
	sin la extención.wav
*/

void play_sound(char sonido[]){
	char archivo[20] ="\\";
	strcat(archivo,sonido);
	strcat(archivo,".wav");
	char adressound[TAM_direccion+20];
	strcpy(adressound,ajuste.direccion);//la direccion del sonido
	strcat(adressound,archivo);
	PlaySound(adressound,NULL,SND_ASYNC);
}
