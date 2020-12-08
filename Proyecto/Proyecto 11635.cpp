#include <bits/stdc++.h>

#define vvpii vector<vector<pair<int, int> > >
#define vpii vector<pair<int, int> >
#define vsi vector<set<int> >
#define si set<int>
#define vi vector<int>
#define pii pair<int, int>
#define pqpii priority_queue<pair<int, int> >
#define qi queue<int>
#define endl '\n'

using namespace std;

int bfs(vsi &grafo_sin_peso){
    qi cola;
    vi visitados(grafo_sin_peso.size(), -1);
    visitados[1] = 0;
    cola.push(1);
    while(!cola.empty()){
        int u = cola.front(); cola.pop();
        if(u == grafo_sin_peso.size() - 1) return visitados[u] - 1;

        for(si::iterator itr = grafo_sin_peso[u].begin(); itr != grafo_sin_peso[u].end(); ++itr){
            if(visitados[*itr] == -1){
                visitados[*itr] = visitados[u] + 1;
                cola.push(*itr);
            }
        }
    }

    return -1;
}

void dikstra(vvpii &grafo, vsi &grafo_sin_peso, vi &puedo_dormir, vi &peso, int inicio){
    pqpii cola;
    cola.push(make_pair(0, inicio));
    while(!cola.empty()){
        int dist = cola.top().first * -1, u = cola.top().second;
        cola.pop();
        if(peso[u] == dist){
            if((puedo_dormir[u] && u != inicio) || u == grafo.size() - 1){
                grafo_sin_peso[u].insert(inicio);
                grafo_sin_peso[inicio].insert(u);
            }
            
            for(int i = 0; i < grafo[u].size(); ++i){
                int v = grafo[u][i].first, temp = grafo[u][i].second;
                if(temp + dist < peso[v] && temp + dist <= 600){
                    peso[v] = temp + dist;
                    cola.push(make_pair(peso[v] * -1, v));
                }
            }
        }
    }
}

int busqueda(vvpii &grafo, vsi &grafo_sin_peso, vi &puedo_dormir){
    for(int i = 1; i < grafo.size() - 1; ++i){
        vi peso(grafo.size(), 2147483647);
        if(i == 1 || puedo_dormir[i]){
            peso[i] = 0;
            dikstra(grafo, grafo_sin_peso, puedo_dormir, peso, i);
        }
    }
    return bfs(grafo_sin_peso);
}

int main(){
    int ciudades, hoteles, caminos;
    while(cin >> ciudades, ciudades){
        vi puedo_dormir(ciudades + 1); 
        vvpii grafo(ciudades + 1);
        vsi grafo_sin_peso(ciudades + 1); 
        cin >> hoteles;
        for(int i = 0; i < hoteles; ++i){
            int key;
            cin >> key;
            puedo_dormir[key] = 1;
        }

        cin >> caminos; 
        for(int i = 0; i < caminos; ++i){
            int ini, fin, peso;
            cin >> ini >> fin >> peso;
            grafo[ini].push_back(make_pair(fin, peso));
            grafo[fin].push_back(make_pair(ini, peso));
        }

        cout << busqueda(grafo, grafo_sin_peso, puedo_dormir) << endl;
    }
    return 0;
}
