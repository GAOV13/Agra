#include <iostream>
#include <vector>
#include <stack>

#define vvi vector<vector<int> >
#define vi vector<int>
#define si stack<int>
#define endl '\n'

using namespace std;

vi sscInd;
vvi componentes; 
vi enPila;

void tarjan_aux(vvi &grafo, vi &visitados, si &pila, int u, int &t){
    visitados[u] = sscInd[u] = ++t;
    pila.push(u);
    enPila[u] = 1;
    for(int i = 0; i < grafo[u].size(); ++i){
        int v = grafo[u][i];
        if(!visitados[v]){
            tarjan_aux(grafo, visitados, pila, v, t);
            sscInd[u] = min(sscInd[u], sscInd[v]);
        }

        else if(enPila[v] == 1){
            sscInd[u] = min(sscInd[u], sscInd[v]);
        }
    }

    if(sscInd[u] == visitados[u]){
        vi temp;
        bool ver = true;
        while(ver){
            int w = pila.top(); pila.pop();
            if(u == w) ver = false;

            enPila[w] = 0;
            temp.push_back(w);
        }
        componentes.push_back(temp);
    }
}

void tarjan(vvi &grafo){
    int t = 0;
    vi visitados(grafo.size(), 0);
    si pila;
    for(int i = 1; i < visitados.size(); ++i){
        if(!visitados[i]) tarjan_aux(grafo, visitados, pila, i, t);
    }
}

int main(){
    int n, m;
    while(cin >> n >> m, n && m){
        sscInd.clear();
        sscInd.resize(n + 1, 0);
        enPila.clear();
        enPila.resize(n + 1), 0;
        componentes.clear();
        vvi grafo(n + 1);
        for(int i = 0; i < m; ++i){
            int ini, fin, k;
            cin >> ini >> fin >> k;
            grafo[ini].push_back(fin);
            if(k == 2) grafo[fin].push_back(ini);
        }
        
        tarjan(grafo);;
        if(componentes.size() == 1) cout << 1 << endl;

        else cout << 0 << endl;
    }
    return 0;
}
