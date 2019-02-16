#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <assert.h>

//Declaración de funciones relacionadas al funcionamiento del programa

int revisarValores(int reinas[][2], int n);
void archivoEntrada( int reinas[17][2]);
int revisarFilas(int reinas[][2],int n);
int revisarColumnas(int reinas[][2],int n);
int revisarDiagonales(int reinas[][2],int n);
int tableroCorrecto(int reinas[17][2],int n);

//Declaración de funciones relacionadas al testing de las funciones


int main(){
	int n,reinas[17][2];
	printf("Ingrese la dimensión del tablero: \n");
	scanf("%d",&n);
	archivoEntrada(reinas);
	//tableroCorrecto(reinas);
	printf("%d\n",revisarValores(reinas,n));
	printf("%d\n",revisarFilas(reinas,n));
	printf("%d\n",revisarColumnas(reinas,n));
	printf("%d\n",revisarDiagonales(reinas,n));


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
	int valoresCorrectos = 1;
	for(int i=0; i < (n-1) && valoresCorrectos;i++){
		for(int j=i+1;j<n && valoresCorrectos;j++){
		valoresCorrectos = (reinas[i][0] != reinas[j][0]);
		}
	}
	return valoresCorrectos;	
}

// Similar a revisarFila(), pero controlando las columnas.
int revisarColumnas(int reinas[][2],int n){
	int valoresCorrectos = 1;
	for(int i=0; i < (n-1) && valoresCorrectos;i++){
		for(int j=i+1;j<n && valoresCorrectos;j++){
		valoresCorrectos = (reinas[i][1] != reinas[j][1]);
		}
	}
	return valoresCorrectos;
}

// Similar a revisarFila(), pero controlando los diagonales.
int revisarDiagonales(int reinas[][2],int n){
	int valoresCorrectos = 1;
	for(int i=0; i < (n-1) && valoresCorrectos;i++){
		for(int j=i+1;j<n && valoresCorrectos;j++){
		valoresCorrectos = ((reinas[i][0]+reinas[i][1]) != (reinas[j][0]+reinas[j][1]) || (reinas[i][0]-reinas[i][1]) != (reinas[j][0]-reinas[j][1]));
		}
	}
	return valoresCorrectos;
}

//La función verifica las cuatro condiciones que debe cumplir un tablero con N reinas bien resuelto.
int tableroCorrecto(int reinas[17][2],int n){
	if(!revisarValores(reinas,n))
		return 0;
	if(!revisarFilas(reinas,n))
		return 1;
	if(!revisarColumnas(reinas,n))
		return 2;
	if(!revisarDiagonales(reinas,n))
		return 3;
}


/*
archivoEntrada: char[] -> int
La función archivoEntrada toma como parámetro un array de dos dimensiones en donde serán
almancenadas las reinas[][17] del archivo tablero.txt. La función devuelve un número entero 
que representa la cantidad de palabras leídas en el archivo.
*/
void archivoEntrada( int reinas[17][2]){
	//int aux[17][2];
	FILE * fp;
	fp = fopen("entrada.txt", "r");
	
	/*while (!feof(fp)){
    fscanf(fp, "%s", linea);
		strcpy(palabras[lineas],linea);
		lineas++;
	}*/

	for(int i=0; !feof(fp);i++){
		fscanf(fp,"%d %d\n",&reinas[i][0],&reinas[i][1]);
	}
	fclose(fp);
}

/*
archivoSalida: int , char[] -> void
La función archivoSalida toma como parámetro la cantidad de palabras en el array resultado
y el array con las palabras que serán copiadas al archivo salida.txt
*/
/*void archivoSalida( char resultado[][16], int cantPalabrasResultante ){
	FILE * fp;
	fp = fopen("salida.txt", "w+");

	forn( i , cantPalabrasResultante ){
		int largoPalabra= strlen(resultado[i]);
		resultado[i][largoPalabra]='\0';
		fprintf(fp, "%s", resultado[i]);
		fprintf(fp, "\n");
	}

	fclose(fp);
}*/