from sys import stdin

grafo = []
dist = 0
quien = 0

def dfs(u, padre, peso):
    global grafo, dist, quien
    for v, temp in grafo[u]:
        if v != padre: dfs(v, u, peso + temp)

    if peso > dist:
        dist = peso
        quien = u


def main():
    global grafo, dist, quien
    grafo = [[] for i in range(10001)]
    for temp in stdin:
        temp = temp.strip()
        if len(temp) == 0:
            dist, quien = 0, 0
            dfs(1, 0, 0)
            dfs(quien, 0, 0)
            print(dist)
            grafo = [[] for i in range(10001)]
        
        else:
            ini, fin, peso = list(map(int, temp.split()))
            grafo[ini].append((fin, peso))
            grafo[fin].append((ini, peso))
    
    dist, quien = 0, 0
    dfs(1, 0, 0)
    dfs(quien, 0, 0)
    print(dist)


main()
