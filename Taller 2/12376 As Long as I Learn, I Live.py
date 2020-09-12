from sys import stdin
from queue import PriorityQueue

dev = [0, 0]

def DFS_LINEAL(grafo, indice, acum):
    global dev
    temp = grafo[indice].get()
    acum = acum + temp[0]
    if(grafo[temp[1]].qsize() == 0):
        dev[0] = acum
        dev[1] = temp[1]
    
    else:
        DFS_LINEAL(grafo, temp[1], acum)


def main():
    global dev
    n = eval(input())
    n = int(n)
    caso = 0
    while(n > 0):
        n -= 1
        caso += 1
        grafo = stdin.readline()
        nodos, aristas = list(map(int, stdin.readline().split()))
        peso = list(map(int, stdin.readline().split()))
        grafo = []

        for i in range(nodos):
            temp = PriorityQueue()
            grafo.append(temp)

        for i in range(aristas):
            padre, hijo = list(map(int, stdin.readline().split()))
            pareja = (peso[hijo]*-1, hijo)
            grafo[padre].put(pareja)

        DFS_LINEAL(grafo, 0, 0)
        print("Case {}: {} {}".format(caso, dev[0]*-1, dev[1]))


main()

