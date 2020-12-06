#include <bits/stdc++.h>

#define vvi vector<vector<int> >
#define vi vector<int>
#define endl '\n'

using namespace std;

void dfs(vvi &grafo, vi &padre, int u, int dist, int &peso, int &inicio){
    for(int i = 0; i < grafo[u].size(); ++i){
        int v = grafo[u][i];
        if(padre[u] != v){
            padre[v] = u;
            dfs(grafo, padre, v, dist + 1, peso, inicio);
        }
    }

    if(dist > peso){
        peso = dist;
        inicio = u;
    }
}

tuple<int, int, vi> diametro(vvi &grafo, int i){
    vi padre(grafo.size());
    int peso = 0, inicio = i;
    dfs(grafo, padre, i, 0, peso, inicio);
    fill(padre.begin(), padre.end(), 0);
    peso = 0;
    dfs(grafo, padre, inicio, 0, peso, inicio);
    return make_tuple(peso, inicio, padre);
}

int centro(vi &padre, int diam, int inicio){
    int radio = (diam + 1)/2;
    vi temp;
    while(inicio != 0){
        temp.push_back(inicio);
        inicio = padre[inicio];
    }

    return temp[radio];
}

void info(vvi &grafo){
    int diam, ini;
    int c1, c2;
    int unir1, temp, unir2;
    int dev_diam = 2147483647, dev_desc1, dev_desc2, dev_unir1, dev_unir2;
    vi padre, camino;    
    tie(diam, ini, padre) = diametro(grafo, 1);
    temp = ini;
    while(temp){
        camino.push_back(temp);
        temp = padre[temp];
    }

    for(int i = 0; i < camino.size() - 1; ++i){
        c1 = camino[i];
        c2 = camino[i + 1];
        grafo[c1].erase(find(grafo[c1].begin(), grafo[c1].end(), c2));
        grafo[c2].erase(find(grafo[c2].begin(), grafo[c2].end(), c1));
        tie(diam, ini, padre) = diametro(grafo, c1);
        unir1 = centro(padre, diam, ini);
        tie(diam, ini, padre) = diametro(grafo, c2);
        unir2 = centro(padre, diam, ini);
        grafo[unir1].push_back(unir2);
        grafo[unir2].push_back(unir1);
        tie(diam, ini, padre) = diametro(grafo, 1);
        if(diam < dev_diam){
            dev_diam = diam;
            dev_desc1 = min(c1, c2);
            dev_desc2 = max(c1, c2);
            dev_unir1 = min(unir1, unir2);
            dev_unir2 = max(unir1, unir2);
        }

        grafo[unir1].pop_back();
        grafo[unir2].pop_back();
        grafo[c1].push_back(c2);
        grafo[c2].push_back(c1);
    }
    
    cout << dev_diam << endl;
    cout << dev_desc1 << " " << dev_desc2 << endl;
    cout << dev_unir1 << " " << dev_unir2 << endl;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        int m;
        cin >> m;
        vvi grafo(m + 1);
        for(int i = 0; i < m - 1; ++i){
            int ini, fin;
            cin >> ini >> fin;
            grafo[ini].push_back(fin);
            grafo[fin].push_back(ini);
        }
        info(grafo);
    }
    return 0;
}
