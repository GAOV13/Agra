from sys import stdin

string_numero = {}
numero_string = []
visitados = []
grafo = []
dev = []

def lectura(num, string):
    global string_numero, numero_string, visitados, grafo
    temp = list(map(str, string.split(";")))
    for u in temp:
        ini_n = string_numero.get(u[0])
        if(ini_n == None):
            string_numero[u[0]] = num
            ini_n = num
            num += 1
            numero_string.append(u[0])
            grafo.append([])
    
        for i in range(2, len(u)):
            fin_n = string_numero.get(u[i])
            if(fin_n == None):
                string_numero[u[i]] = num
                fin_n = num
                num += 1
                numero_string.append(u[i])
                grafo.append([])

            grafo[ini_n].append(fin_n)

    return num


def dfs(mino, theseo, k):
    global string_numero, numero_string, visitados, grafo, dev
    i = 0
    ver = False
    dev = []
    while not ver:
        ver1 = True
        if i%k == 0 and i > 0:
            i = 0
            visitados[theseo] = 2
            dev.append(theseo)
        
        elif visitados[theseo] == 0:
            visitados[theseo] = 1
        
        for index in range(len(grafo[mino])):
            j = grafo[mino][index]
            if visitados[j] == 0:
                if visitados[theseo] == 1:
                    visitados[theseo] = 0

                theseo = mino
                mino = j
                i += 1
                ver1 = False
                break
        
        if ver1:
            ver = True
            dev.append(mino)


def main():
    global string_numero, numero_string, visitados, grafo, dev
    temp = stdin.readline().strip()
    while temp != "#":
        grafo = []
        numero_string = []
        string_numero = {} 
        temp = list(map(str, temp.split()))
        temp[0] = temp[0][:len(temp[0]) - 1]
        tam = lectura(0, temp[0])
        if string_numero.get(temp[2]) == None:
            string_numero[temp[2]] = tam
            tam += 1
        
        visitados = [0 for i in range(tam)]
        dfs(string_numero[temp[1]], string_numero[temp[2]], int(temp[3]))
        for i in range(len(dev) - 1):
            if i == 0:
                print(numero_string[dev[i]], end = "")
            
            else:
                print(" " + numero_string[dev[i]], end = "")
        
        if(len(dev) > 1):
            print(" ", end = "")
        
        print("/" + numero_string[dev[len(dev) - 1]])
        temp = stdin.readline().strip()


main()