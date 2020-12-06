#include <bits/stdc++.h>

#define mii unordered_map<int, int>
#define vi vector<int>
#define MAX_VALUE 100000
#define endl '\n'

using namespace std;

vi info(MAX_VALUE);
vi freq(MAX_VALUE);
vi arbol(MAX_VALUE * 4);

int build(int v, int l, int r){
    if(l == r) arbol[v] = freq[l];
    
    else{
        int m = l + ((r - l) >> 1), v1 = (2 * v) + 1, v2 = 2 * (v + 1);
        arbol[v] = max(build(v1, l, m), build(v2, m + 1, r));
    }

    return arbol[v];
}

int getMax(int v, int L, int R, int l, int r){
    int ans = -1;
    if(l > r) ans = 0;

    else if(l == L && r == R) ans = arbol[v];

    else{
        int m = L + ((R - L) >> 1), v1 = (2 * v) + 1, v2 =  2 * (v + 1);
        ans = max(getMax(v1, L, m, l, min(r, m)), getMax(v2, m + 1, R, max(l, m + 1), r));
    }

    return ans;
}

int busqueda(int ini, int fin, int n){
    int res = 1;

    if(info[ini] == info[fin]) res  = fin - ini + 1;

    else{
        vi::iterator itri = upper_bound(info.begin() + ini, info.begin() + fin, info[ini]);
        vi::iterator itre = lower_bound(info.begin() + ini, info.begin() + fin, info[fin]);
        int cant_left = (itri - info.begin()) - ini, cant_right = (fin + 1) - (itre - info.begin());
        ini = itri - info.begin(); fin = itre - info.begin() - 1;
        res = max({cant_left, cant_right, getMax(0, 0, n - 1, ini, fin)});
    }

    return res;
}

int main(){
    int n, m;
    while(cin >> n, n){
        cin >> m;
        mii mapa;
        for(int i = 0; i < n; ++i){
            cin >> info[i];
            mapa[info[i]]++;
        }

        for(int i = 0; i < n; ++i) freq[i] = mapa[info[i]];

        build(0, 0, n - 1);
        while(m--){
            int ini, fin;
            cin >> ini >> fin;
            cout << busqueda(ini - 1, fin - 1, n) << endl;
        }
    }
    return 0;
}
