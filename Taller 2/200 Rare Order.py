from sys import stdin

string_numero = {}
numero_string = []
grafo = []
topo = []
visitados = []

def dfs(u):
    global topo, visitados, grafo
    for i in range(len(grafo[u])):
        j = grafo[u][i]
        if visitados[j] == 0:
            visitados[j] = 1
            dfs(j)
    topo.append(u)


def dfs_aux():
    global visitados, topo
    topo = []
    for i in range(len(visitados)):
        if visitados[i] == 0:
            visitados[i] = 1
            dfs(i)


def creacion(num, string):
    global string_numero, numero_string, grafo, topo, visitados
    string_numero[string] = num
    numero_string.append(string)
    grafo.append([])
    visitados.append(0)
    num += 1
    return num


def main():
    global string_numero, numero_string, grafo, topo, visitados
    lista = []
    for string in stdin:
        string = string.rstrip()
        if(string == "#"):
            string_numero = {}
            numero_string = []
            grafo = []
            visitados = []
            num = 0
            tam = len(lista)
            for i in range(tam - 1):
                for j in range(len(lista[i])):
                    if lista[i][j] != lista[i + 1][j]:
                        ini = string_numero.get(lista[i][j])
                        fin = string_numero.get(lista[i + 1][j])
                        if(ini == None):
                            num = creacion(num, lista[i][j])
                            ini = num - 1
                        if(fin == None):
                            num = creacion(num, lista[i + 1][j])
                            fin = num - 1
                        grafo[ini].append(fin)
                        break
                        
                    else:
                        ini = string_numero.get(lista[i][j])
                        if(ini == None):
                            num = creacion(num, lista[i][j])
                        fin = string_numero.get(lista[i + 1][j])
                        if(fin == None):
                            num = creacion(num, lista[i + 1][j])

            for i in range(len(lista[tam - 1])):
                ini = string_numero.get(lista[tam - 1][i])
                if(ini == None):
                    num = creacion(num, lista[tam - 1][i])
            dfs_aux()
            i = len(topo) - 1
            while i >= 0:
                print("{}".format(numero_string[topo[i]]), end = "")
                i -= 1

            print()
            lista = []
        else:
            lista.append(string)


main()
