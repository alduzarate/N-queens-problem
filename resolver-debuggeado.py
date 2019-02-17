#Aldana Zarate
"""
Descripción general:
Representación de los datos
Tablero: List[List[string]]
N: int
donde cada lista del tablero es una solución  al problema y cada elemento de la subslistas representa el
número de columna en la cual está colocada la reina correspondiente a la fila (índice del elemento de la sublista), 
siendo cada fila un string.
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
En caso de llegar a una solución o a encontrar que el camino que se estaba siguiendo no conduce a ninguna distribución válida,
se vuelve al estado anterior sacando de la pila el último insertado, y se prueba un nuevo camino aún no visitado.
"""
CANTSOLUCIONES = 1 #guardo la cantidad de soluciones deseadas en una constante

def principal():
    n=int(input("Ingrese la cantidad de reinas a colocar en el tablero"))
    print("\n")
    tablero=resolver(n)
    mostrar(tablero,n)
    guardar(tablero)

def resolver(n):
    res = []
    reinas = []
    restas = set()
    sumas = set()
    visitados = [False]*n
    res=dfs(res,visitados,reinas, restas, sumas,n)
    #return [["_ "*i + "R" + " _"*(n-i-1) for i in sol] for sol in res]
    print("paso antes de return res")
    return res

def dfs(res,visitados,reinas, restas, sumas,n):
        #debugger
        temp = [["." * i + "Q" + "." * (n - i - 1) for i in reinas]]
        for t in temp:
            for tt in t:
                print(tt)
            print("\n")
        print("\n")
        
        print("aca va res al momento: \n")
        for a in res:
            print(a)
        print("\n")

        # i=número de fila, j número de columna a intentar colocar
        i = len(reinas)
        print("holaaa valor de i antes de ver si ya es n: \n")
        print(i)
        print("\n y n es: \n")
        print(n)
        if i == n:
            for a in res:
                print(a)
            print("\n")
            print("ENTRA EN EL FUJCKING IF DONDE ES IGUAL A N") #ya colocamos una reina en cada fila, se encontró una solución
            res.append(reinas[:]) #se la agrega al resultado final
            for a in res:
                print(a)
            print("\n")
            return  #si se desean más soluciones, acá es donde hacemos backtrack
        
        for j in range(n):
            if not visitados[j] and i+j not in sumas and i-j not in restas: #condiciones: si no es una columna que ya se visitó (y que puede
                                                                            #haber fallado) y no está en ataque en alguna de las diagonales
                visitados[j] = True
                reinas.append(j)
                sumas.add(i+j)
                restas.add(i-j)
                dfs(res,visitados,reinas, restas, sumas,n)        
                if len(res) == CANTSOLUCIONES: 
                    print("ENTRO EN EL DE RES2 LYM")#para obtener una sola solución y no se haga backtrack para encontrar otras posibles
                    return res
                print("hago backtrack.Valor de i: \n")
                print(i)
                print("valor de j: \n")
                print(j)
                visitados[j] = False
                reinas.pop() #saco la última agregada de la pila para intentar otro camino
                sumas.remove(i+j)
                restas.remove(i-j)

def guardar(tablero):
    """Función guardar: toma el tablero con la solución y la guarda 
    en el archivo tablero.txt de manera que en cada renglón, el primer número es la fila de la reina y el segundo la columna
    en la que está ubicada."""
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

def mostrar(tablero,n):
    """imprime de manera que quede un tablero nxn. Si se desea ver el resultado
    del tablero generado en pantalla, quitarle el comentario a la llamada a la función mostrar"""
    resultado = [["_ "*i + "R" + " _"*(n-i-1) for i in sol] for sol in tablero]
    for res in resultado:
        for fila in res:
            print(fila)
            print("\n")





principal()