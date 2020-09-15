from sys import stdin
from queue import Queue

visitados = [0 for i in range(27)]
padre = [-1 for i in range(27)]
lista = []

def bfs(inicio, fin):
    global visitados, padre, lista
    cola = Queue()
    cola.put(inicio)
    visitados[inicio] = 1
    while(cola.empty() == False):
        nodo = cola.get()
        if(nodo == fin):
            break
        for i in range(len(lista[nodo])):
            k = lista[nodo][i]
            if(visitados[k] == 0):
                visitados[k] = 1
                padre[k] = nodo
                cola.put(k)
    

def main():
    global visitados, padre, lista
    n = eval(input())
    flag = False
    while n > 0:
        if(flag):
            print("")
        
        flag = True
        aristas = stdin.readline()
        aristas, casos = list(map(int, stdin.readline().split()))
        lista = [[] for i in range(27)]
        for i in range(aristas):
            inicio, fin = list(map(str, stdin.readline().split()))
            inicio = ord(inicio[0]) - 65
            fin = ord(fin[0]) - 65
            lista[inicio].append(fin)
            lista[fin].append(inicio)

        for i in range(casos):
            visitados = [0 for i in range(27)]
            padre = [-1 for i in range(27)]
            inicio, fin = list(map(str, stdin.readline().split()))
            inicio = ord(inicio[0]) - 65
            fin = ord(fin[0]) - 65
            bfs(inicio, fin)
            dev = chr(fin + 65)
            ver = True
            temp = fin
            while(ver):
                temp = padre[temp]
                dev += chr(temp + 65)
                if(temp == inicio):
                    ver = False
            j = len(dev) - 1
            while(j >= 0):
                print(dev[j], end = "")
                j -= 1
            print("")
        
        n -= 1


main()
