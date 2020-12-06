from sys import stdin

def busqueda(preo, ino):
    if preo != "":
        raiz = preo[0]
        temppd, tempid, temppi, tempii = "", "", "", ""
        j = 1
        for i in range(len(ino)):
            if ino[i] == raiz:
                tempii = ino[i + 1:]
                temppi = preo[j:]
                break

            temppd += preo[j]
            tempid += ino[i]
            j += 1
        
        busqueda(temppd, tempid)
        busqueda(temppi, tempii)
        print(raiz, end="")


def main():
    n = eval(input())
    while n != 0:
        m, preo, ino = list(map(str, stdin.readline().split()))
        busqueda(preo, ino)
        print()
        n -= 1


main()
