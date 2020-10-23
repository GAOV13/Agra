from sys import stdin
from queue import PriorityQueue

grafo = []
visitados = []
aeropuertos = []

def bfs(ini, fin):
    global grafo, visitados, aeropuertos
    cola = PriorityQueue()
    visitados[ini] = aeropuertos[ini]
    if(ini == fin):
        visitados[ini] = 0

    cola.put((visitados[ini], ini))
    while cola.empty() == False:
        peso, u = cola.get()
        if u == fin:
            return True

        if(visitados[u] == peso):
            for v in grafo[u]:
                if peso + aeropuertos[v] < visitados[v]:
                    visitados[v] = peso + aeropuertos[v]
                    cola.put((visitados[v], v))
    
    return False


def main():
    global grafo, visitados, aeropuertos
    n = eval(input())
    casos = 0
    while n != 0:
        casos += 1
        print("Case {}:".format(casos))
        nodos, conec, k = list(map(int, stdin.readline().split()))
        grafo = [[] for i in range(nodos + 1)]
        aeropuertos = [1 for i in range(nodos + 1)]
        temp = list(map(int, stdin.readline().split()))
        for u in temp:
            aeropuertos[u] = 0
        
        for i in range(conec):
            ini, fin = list(map(int, stdin.readline().split()))
            grafo[ini].append(fin)
            grafo[fin].append(ini)

        k = eval(input())
        for i in range(k):
            visitados = [4294967295 for i in range(nodos + 1)]
            ini, fin = list(map(int, stdin.readline().split()))
            conteo = -1
            if(bfs(ini, fin)):
                conteo = visitados[fin]

            print(conteo)
        print()
        n -= 1
        temp = stdin.readline()

main()