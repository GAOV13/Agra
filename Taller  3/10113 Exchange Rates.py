from sys import stdin
from queue import Queue
from math import ceil

lista = []
grafo = []
stringNum = {}
visitados = []

def bfs(ini, fin):
    global grafo, visitados
    cola = Queue()
    cola.put(ini)
    visitados[ini] = 1
    while cola.empty() == False:
        u = cola.get()
        if u == fin:
            break

        for tupla in grafo[u]:
            v, star, end = tupla
            if visitados[v] == -1:
                visitados[v] = (visitados[u] * end)/star
                cola.put(v)


def lectura(tam, a):
    global stringNum, grafo
    grafo.append([])
    stringNum[a] = tam
    return tam + 1


def reducir(a, b):
    i = 2
    while i <= min(a, b):
        if a % i == 0 and b % i == 0:
            a //= i
            b //= i

        else:
            i += 1

    return [a, b]


def main():
    global grafo, visitados, stringNum, lista
    tam = 0
    lista = list(map(str, stdin.readline().split()))
    while lista[0] != ".":
        if lista[0] == "!":
            temp = reducir(int(lista[1]), int(lista[4]))
            ini_n = stringNum.get(lista[2])
            if ini_n == None:
                tam = lectura(tam, lista[2])
                ini_n = tam - 1

            fin_n = stringNum.get(lista[5])
            if fin_n == None:
                tam = lectura(tam, lista[5])
                fin_n = tam - 1

            grafo[ini_n].append((fin_n, temp[0], temp[1]))
            grafo[fin_n].append((ini_n, temp[1], temp[0]))

        else:
            ini_n = stringNum.get(lista[1])
            if ini_n == None:
                tam = lectura(tam, lista[1])
                ini_n = tam - 1

            fin_n = stringNum.get(lista[3])
            if fin_n == None:
                tam = lectura(tam, lista[3])
                fin_n = tam - 1
            
            visitados = [-1 for i in range(tam)]
            bfs(ini_n, fin_n)

            if visitados[fin_n] != -1:
                i = 1
                m = visitados[fin_n]
                a = m
                while (i * m) - ((i * m)//1) != 0:
                    i += 1
                    a = i * m
                    b = int(a)
                    c = a - b 
                    if c > 0.9999999999999:
                        a = ceil(a)
                        break

                print("{} {} = {} {}".format(i, lista[1], ceil(a), lista[3]))
            
            else:
                print("? {} = ? {}".format(lista[1], lista[3]))
        lista = list(map(str, stdin.readline().split()))


main()