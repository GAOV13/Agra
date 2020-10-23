#include <bits/stdc++.h>

#define vi vector<int>
#define vvi vector<vector<int> >
#define qi queue<int>
#define endl '\n'

using namespace std;

bool bellman_ford(vvi &grafo, vi &peso, vi &ciclo, vi &dist, int n){
    bool ver = true;
    vi conteo(n + 1), enCola(n + 1);
    qi cola;
    cola.push(1);
    dist[1] = 100;
    while(!cola.empty()){
        int u = cola.front(); cola.pop();
        enCola[u] = 0;
        for(int i = 0; i < grafo[u].size(); ++i){
            int v = grafo[u][i];
            if(dist[u] + peso[v] > dist[v] && conteo[v] <= n){
                dist[v] = dist[u] + peso[v];
                if(!enCola[v]){
                    cola.push(v);
                    ++conteo[v];
                    enCola[v] = 1;
                    if(conteo[v] > n){
                        ciclo.push_back(v);
                        ver = false;
                    } 
                }
            }
        }
    }
    return ver;
}

void dfs(vvi &grafo, vi &visitados, int u){
    ++visitados[u];
    for(int i = 0; i < grafo[u].size(); ++i){
        int v = grafo[u][i];
        if(!visitados[v]) dfs(grafo, visitados, v);
    }
}

int main(){
    int n;
    while(cin >> n){
        if(n == -1) break;
        
        vvi grafo(n + 1);
        vi peso(n + 1), visitados(n + 1), dist(n + 1), ciclo;
        for(int i = 1; i <= n; ++i){
            cin >> peso[i];
            int m;
            cin >> m;
            for(int j = 0; j < m; ++j){
                int k;
                cin >> k;
                if(k <= n) grafo[i].push_back(k);
            }
        }

        bool ver = true;
        if(bellman_ford(grafo, peso, ciclo, dist, n)){
            if(!dist[n]) ver = false;
        }

        else if(!dist[n]){
            for(int i = 0; i < ciclo.size(); ++i){
                if(!visitados[ciclo[i]]) dfs(grafo, visitados, ciclo[i]);
            }

            if(!visitados[n]) ver = false;
        }

        if(ver) cout << "winnable" << endl;
        
        else cout << "hopeless" << endl;
    }
    return 0;
}