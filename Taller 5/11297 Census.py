from sys import stdin

n, c = int(), int()
tree = []


def buildX(a, v, l, r):
    global tree, n, c
    if l != r:
        m = l + ((r - l) >> 1)
        buildX(a, 2 * v + 1, l, m)
        buildX(a, 2 * (v + 1), m + 1, r)
    buildY(a, v, l, r, 0, 0, c - 1)


def buildY(a, vx, lx, rx, vy, ly, ry):
    global tree, n, c
    if ly == ry:
        if lx == rx: tree[vx][vy] = (a[lx][ly], a[lx][ly]) 
        else:
            a1, b1 = tree[2 * vx + 1][vy]
            a2, b2 = tree[2 * (vx + 1)][vy]
            tree[vx][vy] = (max(a1, a2), min(b1, b2))
    else:
        m = ly + ((ry - ly) >> 1)
        buildY(a, vx, lx, rx, 2 * vy + 1, ly, m)
        buildY(a, vx, lx, rx, 2 * (vy + 1), m + 1, ry)
        a1, b1 = tree[vx][2 * vy + 1]
        a2, b2 = tree[vx][2 * (vy + 1)]
        tree[vx][vy] = (max(a1, a2), min(b1, b2))


def minY(vx, vy, LY, RY, ly, ry): 
    global tree, n, c
    ans = None
    if ly > ry: ans = 2147483647
    elif ly == LY and ry == RY: (_, ans) = tree[vx][vy]
    else:
        m = LY + ((RY - LY) >> 1)
        ans = min(minY(vx, 2 * vy + 1, LY, m, ly, min(ry, m)), minY(vx, 2 * (vy + 1), m + 1, RY, max(ly, m + 1), ry))
    return ans


def minX(vx, LX, RX, lx, rx, ly, ry):
    global tree, n, c
    ans = None
    if lx > rx: ans = 2147483647
    elif lx == LX and rx == RX: ans = minY(vx, 0, 0, c - 1, ly, ry)
    else:
        m = LX + ((RX - LX) >> 1)
        ans = min(minX(2 * vx + 1, LX, m, lx, min(rx, m), ly, ry), minX(2 * (vx + 1), m + 1, RX, max(lx, m + 1), rx, ly, ry))
    return ans


def maxY(vx, vy, LY, RY, ly, ry): 
    global tree, n, c
    ans = None
    if ly > ry: ans = 0
    elif ly == LY and ry == RY: (ans, _) = tree[vx][vy]
    else:
        m = LY + ((RY - LY) >> 1)
        ans = max(maxY(vx, 2 * vy + 1, LY, m, ly, min(ry, m)), maxY(vx, 2 * (vy + 1), m + 1, RY, max(ly, m + 1), ry))
    return ans


def maxX(vx, LX, RX, lx, rx, ly, ry):
    global tree, n, c
    ans = None
    if lx > rx: ans = 0
    elif lx == LX and rx == RX: ans = maxY(vx, 0, 0, c - 1, ly, ry)
    else:
        m = LX + ((RX - LX) >> 1)
        ans = max(maxX(2 * vx + 1, LX, m, lx, min(rx, m), ly, ry), maxX(2 * (vx + 1), m + 1, RX, max(lx, m + 1), rx, ly, ry))
    return ans


def updateY(vx, LX, RX, vy, LY, RY, x, y, h):
    global tree, n, c
    if LY == RY:
        if LX == RX: tree[vx][vy] = (h, h)
        else:
            a1, b1 = tree[2 * vx + 1][vy]
            a2, b2 = tree[2 * (vx + 1)][vy]
            tree[vx][vy] = (max(a1, a2), min(b1, b2))
    else:
        m = LY + ((RY - LY) >> 1)
        if y <= m: updateY(vx, LX, RX, 2 * vy + 1, LY, m, x, y, h)
        else: updateY(vx, LX, RX, 2 * (vy + 1), m + 1, RY, x, y, h)
        a1, b1 = tree[vx][2 * vy + 1]
        a2, b2 = tree[vx][2 * (vy + 1)]
        tree[vx][vy] = (max(a1, a2), min(b1, b2))


def updateX(vx, LX, RX, x, y, h):
    global tree, n, c
    if LX != RX:
        m = LX + ((RX - LX) >> 1)
        if x <= m: updateX(2 * vx + 1, LX, m, x, y, h)
        else: updateX(2 * (vx + 1), m +1, RX, x, y, h)
    updateY(vx, LX, RX, 0, 0, c - 1, x, y, h)


def main():
    global tree, n, c
    n = eval(input())
    tree = [[(0, 0) for _ in range(n * 4)] for _ in range(n * 4)]
    a = [[] for i in range(n)]
    lectura = []
    for i in range(n):
        a[i] = list(map(int, stdin.readline().split()))
    
    c = len(a[0])
    buildX(a, 0, 0, n - 1)
    m = eval(input())
    while m != 0:
        lectura = list(map(str, stdin.readline().split()))
        if lectura[0] == "q":
            i_ini, j_ini, i_fin, j_fin = int(lectura[1]), int(lectura[2]), int(lectura[3]), int(lectura[4])
            maxi, mini = 0, 2147483647
            maxi = max(maxi, maxX(0, 0, n - 1, i_ini - 1, i_fin - 1, j_ini - 1, j_fin - 1))
            mini = min(mini, minX(0, 0, n - 1, i_ini - 1, i_fin - 1, j_ini - 1, j_fin - 1))
            print("{} {}".format(maxi, mini))
        
        else:
            fila, col, val = int(lectura[1]), int(lectura[2]), int(lectura[3])
            updateX(0, 0, n - 1, fila - 1, col - 1, val)

        m -= 1


main()