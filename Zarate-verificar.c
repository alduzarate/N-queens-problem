//Aldana Zarate

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

//Declaración de funciones relacionadas al funcionamiento del programa

int revisarN(int n, int cantidadReinas);
int revisarValores(int reinas[][2], int n);
int archivoEntrada(int reinas[][2]);
int revisarFilasYColumnas(int reinas[][2],int n, int direccion);
int revisarDiagonales(int reinas[][2],int n);
int tableroCorrecto(int reinas[][2],int n);
void mostrarResultadoEntradas(int estado);
void mostrarResultadoTablero(int estado);

//Declaración de funciones relacionadas al testeo de funciones
void testing();
void test_revisarN();
void test_revisarValores();
void test_revisarFilasYColumnas();
void test_revisarDiagonales();
void test_tableroCorrecto();

int main(){

	testing();

	int n, estado, reinas[17][2];
	estado=archivoEntrada(reinas);

	//Chequeos de las entradas
	if(estado <= 0){
		mostrarResultadoEntradas(estado);
		return 0;
	}
	
	n=estado;

	//Chequeos sobre el contenido del tablero

	estado=tableroCorrecto(reinas,n);
	mostrarResultadoTablero(estado);
		
}
void mostrarResultadoEntradas(int estado){
	if(estado == 0){
		printf("El archivo que desea abrir no existe\n");
		return;
	}
	if(estado == -10){
		printf("El numero ingresado de reinas no esta dentro de los margenes planteados en nuestro problema\n");
		return;
	}
	if(estado == -20){
		printf("El numero esperado de reinas no coincide con el numero de posiciones ingresadas\n");
		return;
	}

}

void mostrarResultadoTablero(int estado){
	if(estado == 1){
		printf("El tablero es valido\n");
		return;
	}

	if(estado == -1){
		printf("El tablero posee valores fuera de los rangos establecidos por la dimension del tablero\n");
		return;
	}
	if(estado == -2){
		printf("El tablero posee al menos dos reinas en una misma fila\n");
		return;
	}
	if(estado == -3){
		printf("El tablero posee al menos dos reinas en una misma columna\n");
		return;
	}
	if(estado == -4){
		printf("El tablero posee al menos dos reinas en una misma diagonal\n");
		return;
	}
}
// Devuelve 0 si algún valor de fila o columna se encuentra fuera de rango y 1 en caso contrario.
int revisarValores(int reinas[][2], int n){
	int valoresCorrectos = 1;
	for(int i=0; i < n && valoresCorrectos;i++){
		valoresCorrectos = (reinas[i][0] >=0 && reinas[i][0] < n && reinas[i][1] >= 0 && reinas[i][1] < n);
	}
	return valoresCorrectos;
}


// revisa los valores de cada fila o columna (segun corresponda), en búsqueda de reinas en misma fila o columna. 
int revisarFilasYColumnas(int reinas[][2],int n, int direccion){
	int valoresCorrectos = 1;
	for(int i=0; i < (n-1) && valoresCorrectos;i++){
		for(int j=i+1;j<n && valoresCorrectos;j++){
		valoresCorrectos = (reinas[i][direccion] != reinas[j][direccion]);
		}
	}
	return valoresCorrectos;	
}

// Similar a revisarFilaYColumnas, pero controlando los diagonales.
int revisarDiagonales(int reinas[][2],int n){
	int diagonalesCorrectas = 1;
	for(int i=0; i < (n-1) && diagonalesCorrectas;i++){
		for(int j=i+1;j<n && diagonalesCorrectas;j++){
			diagonalesCorrectas = ((reinas[i][0]+reinas[i][1]) != (reinas[j][0]+reinas[j][1]) && (reinas[i][0]-reinas[i][1]) != (reinas[j][0]-reinas[j][1]));
		}
	}
	return diagonalesCorrectas;
}

//Revisa que la cantidad de posiciones ingresadas sea la misma que la esperada y que el valor de N esté dentro de los margenes del problema.
int revisarN(int n,int cantidadReinas){
	if(n!=cantidadReinas)
		return -20;

	else
		return n;

}

//La función verifica las cuatro condiciones que debe cumplir un tablero con N reinas bien resuelto.
int tableroCorrecto(int reinas[][2],int n){
	int fila=0, columna=1;

	if(!revisarValores(reinas,n))
		return -1;

	if(!revisarFilasYColumnas(reinas,n,fila))
		return -2;

	if(!revisarFilasYColumnas(reinas,n,columna))
		return -3;
	
	if(!revisarDiagonales(reinas,n))
		return -4;

	else
		return 1;

}


/*
archivoEntrada: int[][] -> void
La función archivoEntrada toma como parámetro un array de dos dimensiones en donde serán
almancenadas las posiciones de las reinas del archivo tablero.txt.
Donde, en la primer dimensión indica el número de reina, y en esta, el primer elemento es la fila donde está ubicada
y el segundo la columna.
Si:
-el archivo no existe, se retorna 0
-el n ingresado indicando la cantidad de reinas no coincide con la cantidad de posiciones de las reinas, se retorna -20
-el n no está dentro de los márgenes establecidos para nuestro problema, se retorna -10

Si todas estas condiciones se cumplen, retorna n.
*/
int archivoEntrada(int reinas[][2]){
	int n, cantidadReinas=0;
	FILE * fp;
	fp = fopen("tablero.txt", "r");

	if ( fp == NULL){
		return 0;
	}

	fscanf(fp, "%d\n", &n);

	//para evitar una violacion de segmento a la hora de leer las posiciones en el ciclo siguiente
	if(n < 4 || n > 16)
		return -10;

	for(int i=0; !feof(fp) ;i++){
		fscanf(fp,"%d %d\n",&reinas[i][0],&reinas[i][1]);
		cantidadReinas++;
	}

	fclose(fp);

	return revisarN(n,cantidadReinas);

}

void testing(){
	test_revisarN();
	test_revisarValores();
	test_revisarFilasYColumnas();
	test_revisarDiagonales();
	test_tableroCorrecto();
}

void test_revisarN(){
	assert(revisarN(14,7)==-20);
	assert(revisarN(7,7)==7);
}
void test_revisarValores(){
	int array1[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{8,4}};
	int array2[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{9,4}};
	int array3[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{8,8}};
	int arrayok[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{4,4}};
	assert(revisarValores(array1,5)==0);
	assert(revisarValores(array2,5)==0);
	assert(revisarValores(array3,5)==0);
	assert(revisarValores(arrayok,5)==1);
}

void test_revisarFilasYColumnas(){
	int array1[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{0,4} };
	int array2[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{9,4} };
	int array3[5][2] = { {0,0}, {1,2}, {2,2}, {3,3},{8,8} };
	int arrayok[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{4,4} };
	int arrayok2[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{4,5} };
	assert(revisarFilasYColumnas(array1,5,0)==0);
	assert(revisarFilasYColumnas(array2,5,1)==0);
	assert(revisarFilasYColumnas(array3,5,1)==0);
	assert(revisarFilasYColumnas(arrayok,5,0)==1);
	assert(revisarFilasYColumnas(arrayok2,5,1)==1);
}

void test_revisarDiagonales(){
	int array1[4][2] = { {0,1}, {1,0}, {2,3}, {3,2} };
	int array2[4][2] = { {0,0}, {1,1}, {2,3}, {3,2} };
	int array3[4][2] = { {0,3}, {1,1}, {2,1}, {3,3} };
	int array4[4][2] = { {0,0}, {1,2}, {2,1}, {3,2} };
	int arrayok[4][2] = { {0,1}, {1,3}, {2,0}, {3,2} };
	assert(revisarDiagonales(array1,4)==0);
	assert(revisarDiagonales(array2,4)==0);
	assert(revisarDiagonales(array3,4)==0);
	assert(revisarDiagonales(array4,4)==0);
	assert(revisarDiagonales(arrayok,4)==1);
}

void test_tableroCorrecto(){
	int array1[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{8,4} };
	int array2[5][2] = { {0,0}, {1,2}, {2,4}, {3,3},{0,4} } ;
	int array3[5][2] = { {0,0}, {1,1}, {2,2}, {3,3}, {4,0} };
	int array4[4][2] = { {0,2}, {1,3}, {2,0}, {3,1} };
	int arrayok[4][2] = { {0,1}, {1,3}, {2,0}, {3,2} };
	assert(tableroCorrecto(array1,5)==-1);
	assert(tableroCorrecto(array2,5)==-2);
	assert(tableroCorrecto(array3,5)==-3);
	assert(tableroCorrecto(array4,4)==-4);
	assert(tableroCorrecto(arrayok,4)==1);
}
