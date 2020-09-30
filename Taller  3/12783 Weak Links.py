from sys import stdin
from queue import PriorityQueue

grafo = []
visitados = []
padre = []
low = []
conec = PriorityQueue()
t = 0

def tarjan_B_aux(u):
    global grafo, visitados, low, t, padre, conec
    visitados[u] = t
    low[u] = t
    t += 1
    for v in grafo[u]:
        if visitados[v] == 0:
            padre[v] = u
            tarjan_B_aux(v)
            low[u] = min(low[u], low[v])
            if(low[v] > visitados[u]):
                temp = [min(u, v), max(u, v)]
                conec.put(temp)
        elif v != padre[u]:
            low[u] = min(low[u], visitados[v])


def tarjan_B():
    global grafo, visitados, low, t, padre, conec
    visitados = [0 for i in range(len(grafo))]
    low = [0 for i in range(len(grafo))]
    padre = [-1 for i in range(len(grafo))]
    t = 1
    conec = PriorityQueue()
    for i in range(len(visitados)):
        if visitados[i] == 0:
            tarjan_B_aux(i)


def main():
    global grafo, conec
    n, m = list(map(int, stdin.readline().split()))
    while n != 0 and m != 0:
        grafo = [[] for i in range(n)]
        for i in range(m):
            ini, fin = list(map(int, stdin.readline().split()))
            grafo[ini].append(fin)
            grafo[fin].append(ini)

        tarjan_B()
        print(conec.qsize(), end="")
        while conec.empty() == False:
            temp = conec.get()
            print(" {} {}".format(temp[0], temp[1]), end="")
            
        print()
        n, m = list(map(int, stdin.readline().split()))

main()
