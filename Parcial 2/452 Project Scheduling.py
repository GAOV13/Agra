from sys import stdin
from queue import PriorityQueue

grafo = []
peso = []
inicios = []
dist = []

def dikstra():
    global grafo, peso, inicios, dist
    cola = PriorityQueue()
    dev = 0
    for v in inicios:
        dev = max(dev, peso[v])
        dist[v] = peso[v]
        cola.put((dist[v] * -1, v))
    
    while not cola.empty():
        pes, u = cola.get()
        pes *= -1
        if pes == dist[u]:
            dev = max(pes, dev)
            for v in grafo[u]:
                if(pes + peso[v] > dist[v]):
                    dist[v] = pes + peso[v]
                    cola.put((dist[v] * -1, v))
    
    return dev


def main():
    global grafo, peso, inicios, dist
    n = eval(input())
    temp = stdin.readline()
    while(n != 0):
        grafo = [[] for i in range(26)]
        peso = [0 for i in range(26)]
        dist = [0 for i in range(26)]
        inicios = []
        n -= 1
        temp = list(map(str, stdin.readline().split()))
        while len(temp) > 0:
            indice = ord(temp[0]) - 65
            peso[indice] = int(temp[1])
            if len(temp) == 3:
                for u in temp[2]:
                    indice1 = ord(u) - 65
                    grafo[indice1].append(indice)
            
            else: inicios.append(indice)
            
            temp = list(map(str, stdin.readline().split()))

        print(dikstra())
        if(n != 0): print()


main()