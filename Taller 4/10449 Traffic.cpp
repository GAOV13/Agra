#include <iostream>
#include <vector>
#include <queue>

#define vvi vector<vector<int> >
#define vi vector<int>
#define qi queue<int>
#define endl '\n'

using namespace std;

int ciclo;

void dfs (vvi &grafo, vi &visitados, int u){
    visitados[u] = 1;
    for(int i = 0; i < grafo[u].size(); ++i){
        int v = grafo[u][i];
        if(!visitados[v]) dfs(grafo, visitados, v);
    }
}

bool bellman_ford(vvi &grafo, vi &peso, vi &dist){
    vi enCola(grafo.size());
    vi conteo(grafo.size());
    qi cola;
    if(grafo.size() > 1){
        cola.push(1); 
        dist[1] = 0;
    }
    while(!cola.empty()){
        int u = cola.front(); cola.pop();
        enCola[u] = 0;
        for(int i = 0; i < grafo[u].size(); ++i){
            int v = grafo[u][i]; 

            int temp = peso[v] - peso[u], pes = temp*temp*temp;
            if(dist[u] + pes < dist[v]){
                dist[v] = dist[u] + pes;
                if(!enCola[v]){
                    cola.push(v);
                    ++enCola[v];
                    ++conteo[v];
                    if(conteo[v] > grafo.size()){ 
                        ciclo = v;
                        return false; 
                    }
                }
            }
        }
    }
    return true;
}

int main(){
    int n, casos = 0;
    while(cin >> n){
        vi peso(n + 1);
        vvi grafo(n + 1);
        vi dist(n + 1, 2147483647);
        vi visitados(n + 1);
        for(int i = 1; i <= n; ++i)
            cin >> peso[i];

        int m;
        cin >> m;
        for(int i = 0; i < m; ++i){
            int ini, fin;
            cin >> ini >> fin;
            grafo[ini].push_back(fin);
        }

        if(!bellman_ford(grafo, peso, dist))
            dfs(grafo, visitados, ciclo);

        
        cout << "Set #" << ++casos << endl;
        cin >> m;
        while(m--){
            int fin;
            cin >> fin;
            if(!visitados[fin] && dist[fin] >= 3 && dist[fin] != 2147483647)
                cout << dist[fin] << endl;
            
            else cout << '?' << endl;
        }
    }
    return 0;
}
