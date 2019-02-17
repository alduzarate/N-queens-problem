#Aldana Zarate
#Final Febrero 2019

"""
Descripción general:

Representación de los datos
Tablero: List[int]
Solucion/es: List[List[int]]

donde dicha lista representa una solución  al problema y cada elemento de la lista representa el
número de columna en la cual está colocada la reina correspondiente a la fila (índice del elemento de la lista).
Resumidamente, lo que se utilizó en este trabajo es un algoritmo DFS para poder encontrar una solución al problema.
Siempre se comienza colocando una reina en la esquina superior izquierda, para ver si así se puede llegar a una distribución
válida. Si de ninguna manera se puede encontrar una solución con este comienzo, se vuelve hacia atrás y se la coloca en la 2da columna.
Las reinas se van colocando de a por filas, y en esta, se busca alguna columna disponible que no tenga conflicto.
Al buscar esta columna, siempre se lo hace con un i diferente, es decir, un numero de fila diferente. (Me aseguro que no haya
más de 1 en una misma fila). 
Luego, para las columnas, existe el array visitados que guarda dichas columnas que ya han sido visitadas.
Para el chequeo de las diagonales, se puede observar que cada suma y/o resta de las diagonales es única.
Es decir, una vez que coloco una reina en la pila de la solución, agrego la suma y resta de sus coordenadas (fila+columna)
a los arrays sumas[] y restas[] respectivamete, destinados a fin de que no se coloque ninguna reina en sus respectivas diagonales.
En caso de que el camino que se estaba siguiendo no conduce a ninguna distribución válida,
se vuelve al estado anterior sacando de la pila el último insertado, y se prueba un nuevo camino aún no visitado.
Si ya se ha encontrado la única solución que deseamos, procedemos a limpiar la pila con las llamadas recursivas a la función y así retornar la lista con las columnas de
las reinas.
Nota: este programa está diseñado de manera que se puedan conseguir el número de soluciones que se deseen (siendo este número acotado, por supuesto, debido al ritmo de
crecimiento del número de soluciones cuando n crece). Por ello existe la constante con el número de soluciones deseadas, de manera que así el programa para de tratar de
conseguir soluciones aún no exploradas (si es que existen).
Por esto es que el resultado final es una lista de listas de enteros, donde cada sublista representa una solución al problema.
Por ejemplo, si tenemos como un resultado (un elemento de la lista) a la lista [1,3,0,2], esto significa que las posiciones de las reinas son:
Reina1: fila 0 columna 1
Reina2: fila 1 columna 3
Reina3: fila 2 columna 0
Reina4: fila 3 columna 2
"""

CANTSOLUCIONES = 1 #guardo la cantidad de soluciones deseadas en una constante

#Función principal
def principal():
    n=int(input("Ingrese la cantidad de reinas a colocar en el tablero"))
    print("\n")
    tablero=resolver(n)
    #mostrar(tablero,n)
    guardar(tablero)

"""
resolver: int -> List[List[int]]
Toma como parámetro el número de reinas a ubicar y devuelve la lista con la/s solucion/es
"""
def resolver(n):
    res = []
    reinas = []
    #para no tener elementos repetidos y así agilizar los chequeos
    restas = set()
    sumas = set()
    visitados = [False]*n
    res=ubicarReinas(res,visitados,reinas, restas, sumas,n)
    return res

"""
ubicarReinas: List[List[int]], List[int], List[int], List[int], List[int], int -> List[List[int]]
Función recursiva encargada de brindar la cantidad de soluciones deseadas al problema.
"""
def ubicarReinas(res,visitados,reinas, restas, sumas, n):

        # i=número de fila, j número de columna a intentar colocar
        i = len(reinas)
        if i == n:
        #ya colocamos una reina en cada fila, se encontró una solución
            res.append(reinas[:]) #se la agrega al resultado final
            return  #si se desean más soluciones, acá es donde hacemos backtrack
        
        for j in range(n):
            if not visitados[j] and i+j not in sumas and i-j not in restas: #condiciones: si no es una columna que ya se visitó (y que puede
                                                                            #haber fallado) y no está en ataque en alguna de las diagonales
                visitados[j] = True
                reinas.append(j)
                sumas.add(i+j)
                restas.add(i-j)
                ubicarReinas(res,visitados,reinas, restas, sumas,n)        
                if len(res) == CANTSOLUCIONES: 
                #para obtener una sola solución y no se haga backtrack para encontrar otras posibles. Se empieza a limpiar la pila con los estados anteriores
                    return res
                visitados[j] = False
                reinas.pop() #saco la última agregada de la pila para intentar otro camino
                sumas.remove(i+j)
                restas.remove(i-j)
                #vuelve al estado anterior

"""
guardar: List[List[int]] -> None
Función guardar: toma el tablero con la solución y la guarda 
en el archivo tablero.txt de manera que en cada renglón, el primer número es la fila de la reina y el segundo la columna
en la que está ubicada."""
def guardar(tablero):
    reinas = open("tablero.txt", "r+")
    reinas.truncate(0)

    for res in tablero:
        i=0
        for fila in res:
            print(i," ",fila)
            reinas.write(str(i)+" "+str(fila))
            reinas.write("\n")
            i += 1

    reinas.close()
    return


"""
mostrar: List[List[int]], int -> None
Imprime de manera que quede un tablero nxn. Si se desea ver el resultado
del tablero generado en pantalla, quitarle el comentario a la llamada a la función mostrar"""
def mostrar(tablero,n):
    resultado = [["_ "*i + "R" + " _"*(n-i-1) for i in sol] for sol in tablero]
    for res in resultado:
        for fila in res:
            print(fila)
            print("\n")
    return

principal()
