//Aldana Zarate

#include <string.h>
#include <stdio.h>
#include <stdlib.h>

//Declaración de funciones relacionadas al funcionamiento del programa

int revisarValores(int reinas[][2], int n);
int archivoEntrada(int reinas[][2]);
int revisarFilas(int reinas[][2],int n);
int revisarColumnas(int reinas[][2],int n);
int revisarDiagonales(int reinas[][2],int n);
void tableroCorrecto(int reinas[][2],int n, char res[]);
void archivoSalida( char resultado[]);

int main(){

	int n,reinas[17][2];
	char res[200];
	n=archivoEntrada(reinas);
	tableroCorrecto(reinas,n,res);
	archivoSalida(res);

}

// Devuelve False si algún valor se encuentra fuera de rango y True en caso contrario.
int revisarValores(int reinas[][2], int n){
	int valoresCorrectos = 1;
	for(int i=0; i < n && valoresCorrectos;i++){
		valoresCorrectos = (reinas[i][0] >=0 && reinas[i][0] < n && reinas[i][1] >= 0 && reinas[i][1] < n);
	}
	return valoresCorrectos;
}


// revisa los valores de cada fila en búsqueda de reinas en misma fila.
int revisarFilas(int reinas[][2],int n){
	int filasCorrectas = 1;
	for(int i=0; i < (n-1) && filasCorrectas;i++){
		for(int j=i+1;j<n && filasCorrectas;j++){
		filasCorrectas = (reinas[i][0] != reinas[j][0]);
		}
	}
	return filasCorrectas;	
}

// Similar a revisarFila(), pero controlando las columnas.
int revisarColumnas(int reinas[][2],int n){
	int columnasCorrectas = 1;
	for(int i=0; i < (n-1) && columnasCorrectas;i++){
		for(int j=i+1;j<n && columnasCorrectas;j++){
		columnasCorrectas = (reinas[i][1] != reinas[j][1]);
		}
	}
	return columnasCorrectas;
}

// Similar a revisarFila(), pero controlando los diagonales.
int revisarDiagonales(int reinas[][2],int n){
	int diagonalesCorrectas = 1;
	for(int i=0; i < (n-1) && diagonalesCorrectas;i++){
		for(int j=i+1;j<n && diagonalesCorrectas;j++){
			diagonalesCorrectas = ((reinas[i][0]+reinas[i][1]) != (reinas[j][0]+reinas[j][1]) && (reinas[i][0]-reinas[i][1]) != (reinas[j][0]-reinas[j][1]));
		}
	}
	return diagonalesCorrectas;
}

//La función verifica las cuatro condiciones que debe cumplir un tablero con N reinas bien resuelto.
void tableroCorrecto(int reinas[][2],int n, char res[]){

	if(revisarValores(reinas,n) && revisarFilas(reinas,n) && revisarColumnas(reinas,n) && revisarDiagonales(reinas,n)){
		strcpy(res,"El tablero es valido");
		return;
	}

	if(!revisarValores(reinas,n)){
		strcpy(res,"El tablero posee valores fuera de los rangos establecidos por la dimension del tablero");
		return;
	}

	if(!revisarFilas(reinas,n)){
		strcpy(res,"El tablero posee al menos dos reinas en una misma fila");
		return;
	}

	if(!revisarColumnas(reinas,n)){
		strcpy(res,"El tablero posee al menos dos reinas en una misma columna");
		return;
	}
	
	if(!revisarDiagonales(reinas,n)){
		strcpy(res,"El tablero posee al menos dos reinas en una misma diagonal");
		return;
	}

}


/*
archivoEntrada: int[][] -> void
La función archivoEntrada toma como parámetro un array de dos dimensiones en donde serán
almancenadas las posiciones de las reinas del archivo tablero.txt.
Donde, en la primer dimensión indica el número de reina, y en esta, el primer elemento es la fila donde está ubicada
y el segundo la columna.
*/
int archivoEntrada(int reinas[][2]){
	int n=0;
	FILE * fp;
	fp = fopen("tablero.txt", "r");

	for(int i=0; !feof(fp);i++){
		fscanf(fp,"%d %d\n",&reinas[i][0],&reinas[i][1]);
		n++;
	}
	fclose(fp);
	return n;
}

/*
archivoSalida: char[] -> void
La función archivoSalida toma como parámetro un array de caracteres que
representa la condición en la que se encuentra el tablero, que será copiada al archivo salida.txt
*/
void archivoSalida( char res[]){
	FILE * fp;
	fp = fopen("salida.txt", "w+");

	int largoPalabra= strlen(res);
	res[largoPalabra]='\0';
	fprintf(fp, "%s", res);

	fclose(fp);
}