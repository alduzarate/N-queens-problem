#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

//Declaración de funciones relacionadas al funcionamiento del programa



//Declaración de funciones relacionadas al testing de las funciones


int main(){


}








/*
archivoEntrada: char[] -> int
La función archivoEntrada toma como parámetro un array de dos dimensiones en donde serán
almancenadas las palabras del archivo entrada.txt. La función devuelve un número entero 
que representa la cantidad de palabras leídas en el archivo.
*/
int archivoEntrada( char palabras[][16] ){
	int lineas=0;
	char linea[6];
	FILE * fp;
	fp = fopen("entrada.txt", "r");
	
	while (!feof(fp)){
    fscanf(fp, "%s", linea);
		strcpy(palabras[lineas],linea);
		lineas++;
	}

	fclose(fp);
	return lineas;
}

/*
archivoSalida: int , char[] -> void
La función archivoSalida toma como parámetro la cantidad de palabras en el array resultado
y el array con las palabras que serán copiadas al archivo salida.txt
*/
void archivoSalida( char resultado[][16], int cantPalabrasResultante ){
	FILE * fp;
	fp = fopen("salida.txt", "w+");

	forn( i , cantPalabrasResultante ){
		int largoPalabra= strlen(resultado[i]);
		resultado[i][largoPalabra]='\0';
		fprintf(fp, "%s", resultado[i]);
		fprintf(fp, "\n");
	}

	fclose(fp);
}