from sys import stdin
from collections import deque

sscInd = []
enPila = []
componentes = []
grafo = []
visitados = []
pila = []
t = 0

def tarjan_aux(u):
    global visitados, sscInd, grafo, componentes, pila, t, enPila
    visitados[u] = t
    sscInd[u] = t
    t += 1
    pila.append(u)
    enPila[u] = 1
    for v in grafo[u]:
        if visitados[v] == 0:
            tarjan_aux(v)
            sscInd[u] = min(sscInd[u], sscInd[v])
        
        elif enPila[v] == 1: sscInd[u] = min(sscInd[u], sscInd[v])

    if sscInd[u] == visitados[u]:
        componentes.append([])
        w = pila.pop()
        while w != u:
            enPila[w] = 0
            componentes[len(componentes) - 1].append(w)
            w = pila.pop()
        
        componentes[len(componentes) - 1].append(u)
        enPila[u] = 0


def tarjan(n):
    global visitados, pila
    visitados = [0 for i in range(n + 1)]
    pila = deque()
    t = 1
    for i in range(1, n + 1):
        if visitados[i] == 0: tarjan_aux(i)


def main():
    global sscInd, enPila, componentes, grafo
    n, m = list(map(int, stdin.readline().split()))
    while n != 0 and m != 0:
        sscInd = [0 for i in range(n + 1)]
        enPila = [0 for i in range(n + 1)]
        componentes = []
        grafo = [[] for i in range(n + 1)]
        for i in range(m):
            ini, fin, k = list(map(int, stdin.readline().split()))
            grafo[ini].append(fin)
            if k == 2: grafo[fin].append(ini)
        
        tarjan(n)
        if len(componentes) == 1: print(1)

        else: print(0)
        
        n, m = list(map(int, stdin.readline().split()))


main()