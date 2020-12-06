from sys import stdin

def busqueda(anterior, info, padre, temp, actual):
    for i in range(1, len(info)):
        var = None
        if anterior == "L" and info[i] == "L":
            padre = actual.copy()
            actual[0] = temp[0] + actual[0]
            actual[1] = temp[1] + actual[1] 
        
        elif anterior == "L" and info[i] == "R":
            var = [padre[0] + actual[0], padre[1] + actual[1]]
            temp = padre.copy()
            anterior = "R"
            padre = actual.copy()
            actual = var.copy()

        elif anterior == "R" and info[i] == "L":
            var = [padre[0] + actual[0], padre[1] + actual[1]]
            temp = padre.copy()
            anterior = "L"
            padre = actual.copy()
            actual = var.copy()

        elif anterior == "R" and info[i] == "R":
            padre = actual.copy()
            actual[0] = temp[0] + actual[0]
            actual[1] = temp[1] + actual[1] 

    return actual


def main():
    n = eval(input())
    while n != 0:
        temp = stdin.readline().strip()
        padre, temp1, actual = [1, 1], [1, 0], [1 , 1]
        
        if temp[0] == "L":
            actual = [1 + 0, 1 + 1]
            temp1 = [0, 1]
        else:
            actual = [1 + 1, 1 + 0]
            temp1 = [1, 0]
        
        actual = busqueda(temp[0], temp, padre, temp1, actual)
        print("{}/{}".format(actual[0], actual[1]))
        n -= 1


main()