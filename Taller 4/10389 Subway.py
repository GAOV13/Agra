from queue import PriorityQueue
from sys import stdin
from math import sqrt, ceil, floor

grafo = []
lista = []
dist = []
caminata = 2.77777778
metro = 11.11111111

class Estacion():
    def __init__(self, x, y, linea, indice, pos):
        self.x = x
        self.y = y
        self.linea = linea
        self.indice = indice
        self.pos = pos


def dikstra():
    global grafo, lista, dist
    cola = PriorityQueue()
    cola.put((0, 0))
    dist[0] = 0
    while cola.empty() == False:
        peso, u = cola.get()
        if dist[u] == peso:
            linea = lista[u].linea
            indice = lista[u].indice
            for v in grafo[linea][indice]:
                x = lista[u].x - lista[v].x
                y = lista[u].y - lista[v].y
                distancia = sqrt((x*x) + (y*y))
                segundos = distancia / metro
                if dist[u] + segundos < dist[v]:
                    dist[v] = dist[u] + segundos
                    cola.put((dist[v], v))
            
            for v in lista:
                x = lista[u].x - v.x
                y = lista[u].y - v.y
                distancia = sqrt((x*x) + (y*y))
                segundos = distancia / caminata
                if dist[u] + segundos < dist[v.pos]:
                    dist[v.pos] = dist[u] + segundos
                    cola.put((dist[v.pos], v.pos))
            


def main():
    global grafo, lista, dist
    n = eval(input())
    temp = stdin.readline()
    while n != 0:
        x1, y1, x2, y2 = list(map(int, stdin.readline().split()))
        e = Estacion(x1, y1, 0, 0, 0)
        grafo = [[[]]]
        lista = [e]
        linea = 1
        tam = 1
        for temp in stdin:
            temp = temp.strip()
            if temp == "":
                break
            
            grafo.append([])
            temp = list(map(int, temp.split()))
            i = 0
            indice = 0
            temp1 = []
            while i < len(temp) - 2:
                grafo[linea].append([])
                e = Estacion(temp[i], temp[i + 1], linea, indice, tam)
                i += 2
                indice += 1
                tam += 1
                temp1.append(e)

            for i in range(len(temp1) - 1):
                u = temp1[i]
                v = temp1[i + 1]
                grafo[linea][i].append(v.pos)
                grafo[linea][i + 1].append(u.pos)

            linea += 1
            lista += temp1

        e = Estacion(x2, y2, linea, 0, tam)
        grafo.append([[]])
        lista.append(e)
        dist = [4294967295 for i in range(tam + 1)]
        dikstra()
        dev = dist[tam]
        dev = dev/60
        if dev - floor(dev) < 0.5:
            dev = floor(dev)
        
        else:
            dev = ceil(dev)
        
        print(dev)
        n -= 1
        if n != 0:
            print()


main()