from sys import stdin
from collections import deque
from queue import PriorityQueue

numString = []
stringNum = {}
grafo = []
enPila = []
visitados = []
low = []
pila = deque()
t = 0
dev = PriorityQueue()

def tarjan():
    global grafo, visitados, low, t, dev, enPila
    visitados = [0 for i in range(len(grafo))]
    low = [0 for i in range(len(grafo))]
    enPila = [0 for i in range(len(grafo))]
    dev = PriorityQueue()
    t = 1
    for i in range(len(visitados)):
        if visitados[i] == 0:
            tarjan_aux(i)


def tarjan_aux(u):
    global grafo, enPila, pila, numString, t, dev, visitados, low, dev
    visitados[u] = t
    low[u] = t
    t += 1
    pila.append(u)
    enPila[u] = 1
    for v in grafo[u]:
        if visitados[v] == 0:
            tarjan_aux(v)
            low[u] = min(low[u], low[v])
        elif enPila[v] == 1:
            low[u] = min(low[u], low[v])
    
    if low[u] == visitados[u]:
        v = -1
        temp = []
        while v != u:
            v = pila[len(pila) - 1]
            pila.pop()
            temp.append(numString[v])
            enPila[v] = 0
        temp.sort()
        dev.put(temp)


def main():
    global numString, stringNum, grafo, dev
    n = eval(input())
    ver = False
    while n != 0:
        if ver:
            print()
        
        ver = True
        tam = 0
        numString = []
        stringNum = {}
        grafo = []
        for i in range(n):
            lista = list(map(str, stdin.readline().split()))
            ini = lista.pop()
            ini_n = stringNum.get(ini)
            if ini_n == None:
                stringNum[ini] = tam
                ini_n = tam
                numString.append(ini)
                grafo.append([])
                tam += 1
            for u in lista:
                if u == ini:
                    continue
                fin_n = stringNum.get(u)
                if fin_n == None:
                    stringNum[u] = tam
                    fin_n = tam
                    numString.append(u)
                    grafo.append([])
                    tam += 1
                grafo[ini_n].append(fin_n)
        tarjan()
        while dev.empty() == False:
            temp = dev.get()
            print(temp[0], end="")
            for i in range(1, len(temp)):
                print(" {}".format(temp[i]), end="")

            print()
        n = eval(input())


main()
