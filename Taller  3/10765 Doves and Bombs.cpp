#include <iostream>
#include <set>
#include <vector>
#include <queue>
#include <cmath>
#include <iterator>

#define vvi vector<vector<int> >
#define vi vector<int>
#define pqpii priority_queue<pair<int, int> >
#define pii pair<int, int>
#define si set<int>
#define endl '\n'

using namespace std;

si dev;

void tarjanPaAux(vvi &grafo, vi &visitados, vi &padre, vi &low, int u, int &t){
    visitados[u] = low[u] = ++t;
    int conec = 0;
    for(int i = 0; i < grafo[u].size(); ++i){
        int w = grafo[u][i];
        if(!visitados[w]){
            padre[w] = u;
            conec++;
            tarjanPaAux(grafo, visitados, padre, low, w, t);
            low[u] = min(low[u], low[w]);
            if(padre[u] != -1 && low[w] >= visitados[u]) dev.insert(u);
        }

        else if(w != padre[u]) low[u] = min(low[u], visitados[w]);
    }

    if(padre[u] == -1 && conec > 1) dev.insert(u);
}

void tarjanPa(vvi &grafo){
    int tam = grafo.size(), t = 0;
    vi visitados(tam), padre(tam, -1), low(tam);
    for(int i = 0; i < tam; ++i){
        if(!visitados[i])
            tarjanPaAux(grafo, visitados, padre, low, i, t);
    } 
}

void dfs_aux(vvi &grafo, vi &visitados, int u){
    for(int i = 0; i < grafo[u].size(); ++i){
        int j = grafo[u][i];
        if(!visitados[j]++)
            dfs_aux(grafo, visitados, j);
    }
}

int dfs(vvi &grafo, int u){
    vi visitados(grafo.size());
    visitados[u] = 1;
    int comp = 0;
    for(int i = 0; i < visitados.size(); ++i){
        if(!visitados[i]++){
            ++comp;
            dfs_aux(grafo, visitados, i);
        }
    }
    return comp;
}

int main(){
    int n, m;
    while(cin >> n >> m, n && m){
        vvi grafo(n);
        vi conec(n, 1);
        int ini, fin;
        while(cin >> ini >> fin, ini != -1 && fin != - 1){
            grafo[ini].push_back(fin);
            grafo[fin].push_back(ini);
        }

        dev.clear();
        tarjanPa(grafo);
        pqpii cola;
        for(si::iterator itr = dev.begin(); itr != dev.end(); ++itr){
            int cant = dfs(grafo, *itr);
            conec[*itr] = cant;
            pii par = make_pair(cant, *(itr) * -1);
            cola.push(par);
        }


        for(int i = 0; i < m; ++i){
            if(!cola.empty()){
                pii par = cola.top(); cola.pop();
                cout << par.second * -1 << ' ' << par.first << endl;
            }

            else{
                for(int j = 0; j < n; ++j){
                    if(conec[j] == 1){
                        cout << j << ' ' << 1 << endl;
                        if(++i == m) break;
                    }
                }
                break;
            }
        }
        cout << endl;
    }
    return 0;
}
