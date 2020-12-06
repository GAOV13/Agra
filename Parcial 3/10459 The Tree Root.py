from sys import stdin
from queue import Queue
from collections import deque

tree = []
padre = []
ruta = []
distMax = 0
nodoMax = 0

def dfs(u, n):
    global tree, padre, distMax, nodoMax
    pila = deque()
    visitados = [-1 for i in range(n)]
    visitados[u] = 0
    pila.append(u)
    while(len(pila) != 0):
        u = pila.pop()
        for v in tree[u]:
            if visitados[v] == -1:
                padre[v] = u
                visitados[v] = visitados[u] + 1
                pila.append(v)
                if visitados[v] > distMax:
                    distMax = visitados[v]
                    nodoMax = v
        
            
def bfs(u, n):
    global tree
    visitados = [0 for i in range(n)]
    visitados[u] = 1
    altura = 1
    dev = [u]
    cola = Queue()
    cola.put(u)
    while not cola.empty():
        u = cola.get()
        for v in tree[u]:
            if visitados[v] == 0:
                visitados[v] = visitados[u] + 1
                cola.put(v)
                if visitados[v] == altura: dev.append(v)

                else:
                    altura = visitados[v]
                    dev = [v]

    return dev


def diametro(n):
    global padre, ruta, distMax, nodoMax, j
    ruta = []
    distMax = 0
    nodoMax = 0
    padre = [0 for i in range(n)]
    j = 0
    dfs(1, n)
    j = 0
    padre = [0 for i in range(n)]
    distMax = 0
    dfs(nodoMax, n)
    u = nodoMax
    while u != 0:
        ruta.append(u)
        u = padre[u]

    return distMax


def main():
    global tree, ruta
    for n in stdin:
        n = int(n)
        tree = [[] for i in range(n + 1)]
        for i in range(1, n + 1):
            temp = list(map(int, stdin.readline().split()))
            temp = temp[1:]
            tree[i] = temp.copy()

        
        dist = diametro(n + 1)
        mejores = [ruta[(dist + 1)//2]]
        peores = []
        if dist % 2 == 1: mejores.append(ruta[((dist + 1)//2) - 1])

        for u in mejores:
            peores += bfs(u, n + 1)
            
        mejores.sort()
        peores.sort()
        print("Best Roots  :", end="")
        for v in mejores: print(" {}".format(v), end="")

        print("\nWorst Roots :", end="")
        for v in peores: print(" {}".format(v), end="")

        print()
        
        
main()