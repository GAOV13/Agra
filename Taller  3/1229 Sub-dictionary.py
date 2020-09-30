from sys import stdin
from collections import deque

dev = []
padre = []
num_comp = []
componentes = []
stringNum = {}
numString = []
grafo = []
visitados = []
low = []
en_pila = []
pila = deque()
t = 0

def tarjan_SC_aux(u):
    global low, visitados, en_pila, grafo, t, pila, padre, componentes, numString, stringNum, num_comp
    visitados[u] = t + 1
    low[u] = t + 1
    t += 1
    en_pila[u] = 1
    pila.append(u)
    for v in grafo[u]:
        if visitados[v] == 0:
            tarjan_SC_aux(v)
            low[u] = min(low[u], low[v])

        elif en_pila[v] == 1:
            low[u] = min(low[u], low[v])
        
        elif en_pila[v] == 0 and padre[v][0] == - 1:
            for k in componentes[num_comp[v]]:
                padre[stringNum[k]][0] = u
        
        elif en_pila[v] == 0:
            for k in componentes[num_comp[v]]:
                padre[stringNum[k]].append(u)

    if low[u] == visitados[u]:
        v = -1
        temp = []
        while(v != u):
            v = pila[len(pila) - 1]
            pila.pop()
            temp.append(numString[v])
            en_pila[v] = 0

        if  len(pila) != 0:
            v = pila[len(pila) - 1]
            for w in temp:
                padre[stringNum[w]][0] = v
                num_comp[stringNum[w]] = len(componentes)
        else:
            for w in temp:
                num_comp[stringNum[w]] = len(componentes)

        componentes.append(temp)


def tarjan_SC():
    global low, visitados, en_pila, grafo, t, padre, componentes, num_comp
    low = [0 for i in range(len(grafo))]
    visitados = [0 for i in range(len(grafo))]
    en_pila = [0 for i in range(len(grafo))]
    componentes = []
    num_comp = [0 for i in range(len(grafo))]
    padre = [[-1] for i in range(len(grafo))]
    pila.clear()
    for i in range(len(visitados)):
        if visitados[i] == 0:
            tarjan_SC_aux(i)


def dfs(u, temp):
    global grafo, dev, componentes
    if len(componentes[u]) > 1:
        dev += temp
    for i in grafo[u]:
        temp += componentes[i]
        dfs(i, temp)
    
    for i in componentes[u]:
        if i in temp:
            temp.remove(i)


def main():
    global numString, stringNum, grafo, padre, componentes, dev, visitados
    n = eval(input())
    while n != 0:
        grafo = []
        numString = []
        stringNum = {}
        tam = 0
        for i in range(n):
            lista = list(map(str, stdin.readline().split()))
            ini = stringNum.get(lista[0])
            if ini == None:
                stringNum[lista[0]] = tam
                tam += 1
                numString.append(lista[0])
                ini = tam - 1
                grafo.append(set())
            for j in range(1, len(lista)):
                fin = stringNum.get(lista[j])
                if fin == None:
                    stringNum[lista[j]] = tam
                    tam += 1
                    numString.append(lista[j])
                    fin = tam - 1
                    grafo.append(set())
                grafo[fin].add(ini)
        
        tarjan_SC()
        grafo_temp = [[] for i in range(len(componentes))]
        for i in range(len(componentes)):
            for j in range(len(padre[stringNum[componentes[i][0]]])):
                if padre[stringNum[componentes[i][0]]][j] != -1:
                    grafo_temp[i].append(num_comp[padre[stringNum[componentes[i][0]]][j]])
        
        
        grafo = [[] for i in range(len(componentes))]
        for i in range(len(grafo_temp)):
            for u in grafo_temp[i]:
                grafo[u].append(i)


        dev = []
        for i in range(len(componentes)):
            if padre[stringNum[componentes[i][0]]][0] == -1:
                dev += componentes[i]
                dfs(i, [])

        dev = list(set(dev))
        dev.sort()
        print(len(dev))
        print(dev[0], end="")
        for i in range(1, len(dev)):
            print(' ' + dev[i], end="")
        print()
        n = eval(input())


main()
