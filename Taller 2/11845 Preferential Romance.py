from sys import stdin
from queue import Queue

grafo = []
invertices = []
string_numero = {}

def segunda_Veri(cant):
    global grafo, invertices
    for i in range(len(invertices)):
        if invertices[i] == 1:
            invertice_temp = invertices.copy()
            cola = Queue()
            cola.put(i)
            invertice_temp[i] = 0
            temp = cant
            while cola.empty() == False:
                u = cola.get()
                for j in range(len(grafo[u])):
                    k = grafo[u][j]
                    invertice_temp[k] -= 1
                    if invertice_temp[k] == 0:
                        cola.put(k)
                temp += 1
        
            if(temp == len(invertices)):
                return True

    return False


def kahn_topo():
    global invertices, grafo
    cant = 0
    cola = Queue()
    for i in range(len(invertices)):
        if invertices[i] == 0:
            cola.put(i)

    while(cola.empty() == False):
        u = cola.get()
        cant += 1
        for i in range(len(grafo[u])):
            j = grafo[u][i]
            invertices[j] -= 1
            if invertices[j] == 0:
                cola.put(j)
    return cant


def main():
    global grafo, invertices, string_numero
    nombre1 , nombre2  = list(map(str, stdin.readline().split()))
    while(nombre1 != "*" and nombre2 != "*"):
        grafo = []
        invertices = []
        string_numero = {}
        num = 0
        for j in range(2):
            lista = list(map(str, stdin.readline().split()))
            i = 1
            ini = 0
            fin = 0
            if len(lista) > 0:
                ini = string_numero.get(lista[0])
                if(ini == None):
                    string_numero[lista[0]] = num
                    num += 1
                    ini = num - 1
                    grafo.append([])
                    invertices.append(0)

            while i < len(lista) - 1:
                if(lista[i] == ","):
                    i += 1
                    fin = string_numero.get(lista[i])
                    if(fin == None):
                        string_numero[lista[i]] = num
                        num += 1
                        grafo.append([])
                        invertices.append(0)
                        fin = num - 1
                    
                    ini = fin
                    i += 1
                    continue
                fin = string_numero.get(lista[i])
                if(fin == None):
                    string_numero[lista[i]] = num
                    num += 1
                    grafo.append([])
                    invertices.append(0)
                    fin = num - 1
                grafo[ini].append(fin)
                invertices[fin] += 1
                ini = fin
                i += 1

        cant = kahn_topo()
        if cant == len(invertices):
            print("F")
        else:
            if segunda_Veri(cant) == True:
                print("P")
            else:
                print("N")
        nombre1 , nombre2  = list(map(str, stdin.readline().split()))


main()