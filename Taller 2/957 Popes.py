from sys import stdin

def upperS(lista, num, low, hi):
    mid = (low + hi) >> 1
    if(low == mid):
        return hi
    
    if(lista[mid] <= num):
        return upperS(lista, num, mid, hi)
    
    else:
        return upperS(lista, num, low, mid)

    
def main():
    for tam in stdin:
        if(tam != "\n"):
            tam = int(tam)
            n = eval(input())
            info = []
            for i in range(n):
                temp = eval(input())
                info.append(temp)
            
            left = right = 0
            cant = 0
            for i in range(n):
                j = upperS(info, info[i] + tam - 1, i, n)
                if(info[j - 1] - info[i] < tam and j - i > cant):
                    left = i
                    right = j - 1
                    cant = j - i 

                if(j == n):
                    break

            print("{} {} {}".format(cant, info[left], info[right]))


main()
