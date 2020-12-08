from sys import stdin
from queue import Queue, PriorityQueue

grafo = []
grafo_sin_peso = []
puedo_dormir = []
peso = []

def bfs():
    global grafo_sin_peso
    cola = Queue()
    visitados = [-1 for i in range(len(grafo_sin_peso))]
    visitados[1] = 0
    cola.put(1)
    while not cola.empty():
        u = cola.get()
        if u == len(grafo_sin_peso) - 1: return visitados[u] - 1

        for v in grafo_sin_peso[u]:
            if visitados[v] == -1:
                visitados[v] = visitados[u] + 1
                cola.put(v)
    
    return -1


def dikstra(inicio):
    global grafo, grafo_sin_peso, puedo_dormir, peso
    cola = PriorityQueue()
    peso[inicio] = 0
    cola.put((0, inicio))
    while not cola.empty():
        dist, u = cola.get()
        if peso[u] == dist:
            if (puedo_dormir[u] == 1 and u != inicio) or u == len(grafo) - 1:
                grafo_sin_peso[u].add(inicio)
                grafo_sin_peso[inicio].add(u)
        
        for v, temp in grafo[u]:
            if temp + dist < peso[v] and temp + dist <= 600:
                peso[v] = temp + dist
                cola.put((peso[v], v))


def busqueda():
    global peso, grafo_sin_peso
    for i in range(1, len(grafo) - 1):
        peso = [2147483647 for i in range(len(grafo_sin_peso))]
        if i == 1 or puedo_dormir[i] == 1:
            dikstra(i)
    
    return bfs()


def main():
    global grafo, puedo_dormir, grafo_sin_peso
    ciudades = eval(input())
    while ciudades != 0:
        puedo_dormir = [0 for i in range(ciudades + 1)]
        grafo = [[] for i in range(ciudades + 1)]
        grafo_sin_peso = [set() for i in range(ciudades + 1)]
        temp = list(map(int, stdin.readline().split()))
        hoteles = temp[0]
        for i in range(hoteles):
            key = temp[1 + i]
            puedo_dormir[key] = 1

        caminos = eval(input())
        for i in range(caminos):
            ini, fin, peso = list(map(int, stdin.readline().split()))
            grafo[ini].append((fin, peso))
            grafo[fin].append((ini, peso))
        
        print(busqueda())
        ciudades = eval(input())


main()