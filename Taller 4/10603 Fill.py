from sys import stdin
from queue import PriorityQueue

tanka = []
tankb = []
tankc = []
tankba = []
tankbb = []
tankbc = []

def operacion(num1, num2, tam):
    dist = tam - num2
    ini = 0
    fin = 0
    if num1 - dist < 0:
        dist = num1
        fin = num2 + num1
    else:
        ini = num1 - dist
        fin = tam
    return (ini, fin, dist)


def dikstra(d, tama, tamb, tamc):
    global tanka, tankb, tankc, tankba, tankbb, tankbc
    cola = PriorityQueue()
    cola.put((0, 0, 0, tamc))
    pesoMin = 0
    d_min = 0
    if tamc <= d:
        d_min = tamc
    while cola.empty() == False:
        peso, a, b, c = cola.get()
        if tankba[a] == False or tankbb[b] == False or tankbc[c] == False:
            if a == d or b == d or c == d:
                return (peso, d)
            
            tankba[a] = True
            tankbb[b] = True
            tankbc[c] = True
            if (a > d_min and a < d):
                pesoMin = peso
                d_min = a
            if (b > d_min and b < d):
                pesoMin = peso
                d_min = b
            if (c > d_min and c < d): 
                pesoMin = peso
                d_min = c
            
            if c > 0:
                if a < tama:
                    ini, fin, dist = operacion(c, a, tama)
                    if (peso + dist < tanka[fin] and tankba[fin] == False) or (peso + dist < tankb[b] and tankbb[b] == False) or (peso + dist < tankc[ini] and tankbc[ini] == False):
                        tanka[fin] = peso + dist
                        tankb[b] = peso + dist
                        tankc[ini] = peso + dist
                        cola.put((peso + dist, fin, b, ini))
                if b < tamb:
                    ini, fin, dist = operacion(c, b, tamb)
                    if (peso + dist < tanka[a] and tankba[a] == False) or (peso + dist < tankb[fin] and tankbb[fin] == False) or (peso + dist < tankc[ini] and tankbc[ini] == False):
                        tanka[a] = peso + dist
                        tankb[fin] = peso + dist
                        tankc[ini] = peso + dist
                        cola.put((peso + dist, a, fin, ini))
            
            if b > 0:
                if a < tama:
                    ini, fin, dist = operacion(b, a, tama)
                    if (peso + dist < tanka[fin] and tankba[fin] == False) or (peso + dist < tankb[ini] and tankbb[ini] == False) or (peso + dist < tankc[c] and tankbc[c] == False):
                        tanka[fin] = peso + dist
                        tankb[ini] = peso + dist
                        tankc[c] = peso + dist
                        cola.put((peso + dist, fin, ini, c))
                if c < tamc:
                    ini, fin, dist = operacion(b, c, tamc)
                    if (peso + dist < tanka[a] and tankba[a] == False) or (peso + dist < tankb[ini] and tankbb[ini] == False) or (peso + dist < tankc[fin] and tankbc[fin] == False):
                        tanka[a] = peso + dist
                        tankb[ini] = peso + dist
                        tankc[fin] = peso + dist
                        cola.put((peso + dist, a, ini, fin))
            
            if a > 0:
                if c < tamc:
                    ini, fin, dist = operacion(a, c, tamc)
                    if (peso + dist < tanka[ini] and tankba[ini] == False) or (peso + dist < tankb[b] and tankbb[b] == False) or (peso + dist < tankc[fin] and tankbc[fin] == False):
                        tanka[ini] = peso + dist
                        tankb[b] = peso + dist
                        tankc[fin] = peso + dist
                        cola.put((peso + dist, ini, b, fin))
                if b < tamb:
                    ini, fin, dist = operacion(a, b, tamb)
                    if (peso + dist < tanka[ini] and tankba[ini] == False) or (peso + dist < tankb[fin] and tankbb[fin] == False) or (peso + dist < tankc[c] and tankbc[c] == False):
                        tanka[ini] = peso + dist
                        tankb[fin] = peso + dist
                        tankc[c] = peso + dist
                        cola.put((peso + dist, ini, fin, c))
                     
    return (pesoMin, d_min)


def main():
    global tanka, tankb, tankc, tankba, tankbb, tankbc
    n = int(stdin.readline().strip())
    while n > 0:
        a, b, c, d = list(map(int, stdin.readline().split()))
        tanka = [2147483647 for i in range(a + 1)]
        tankb = [2147483647 for i in range(b + 1)]
        tankc = [2147483647 for i in range(c + 1)]
        tankba = [False for i in range(a + 1)]
        tankbb = [False for i in range(b + 1)]
        tankbc = [False for i in range(c + 1)]
        mini, d = dikstra(d, a, b, c)
        print("{} {}".format(mini, d))
        n -= 1


main()