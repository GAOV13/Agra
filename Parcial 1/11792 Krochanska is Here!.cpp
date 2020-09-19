#include <bits/stdc++.h>

#define vvi vector<vector<int> >
#define vi vector<int>
#define si set<int>
#define qi queue<int>
#define endl '\n'

using namespace std;

int bfs(vvi &grafo, si &importantes, int ini){
    vi visitados(grafo.size(), -1);
    visitados[ini] += 1;
    int num = 0; 
    qi cola;
    cola.push(ini);
    while(!cola.empty()){
        int u = cola.front(); cola.pop();
        for(int i = 0; i < grafo[u].size(); ++i){
            int j = grafo[u][i];
            if(visitados[j] == -1){
                visitados[j] = visitados[u] + 1;
                int temp = visitados[j];
                cola.push(j);
                if(importantes.find(j) != importantes.end()) num += temp;
            }
        }
    }
    return num;
}

int main(){
    int n;
    cin >> n;
    while(n--){
        int nodo, linea;
        cin >> nodo >> linea;
        vvi grafo(nodo + 1);
        vi estaciones(nodo + 1);
        si importantes;
        int ini, fin;
        for(int i = 0; i < linea; ++i){
            cin >> ini;
            int temp;
            if(ini){
                temp = ++estaciones[ini];

                if(temp > 1) importantes.insert(ini);

                while(cin >> fin, fin != 0){
                    temp = ++estaciones[fin];
                    if(temp > 1) importantes.insert(fin);

                    grafo[ini].push_back(fin);
                    grafo[fin].push_back(ini);
                    ini = fin;
                }
            }
        }

        int num = bfs(grafo, importantes, *(importantes.begin()));
        int nod = *(importantes.begin());
        si::iterator itr, itr1 = importantes.begin();
        itr1++;
        for(itr = itr1; itr != importantes.end(); ++itr){
            int temp = bfs(grafo, importantes, *(itr));
            if(temp < num){
                num = temp; 
                nod = *(itr);
            }

            else if(temp == num){
                if(nod > *(itr)) nod = *itr;
            }
        }
        cout << "Krochanska is in: " << nod << endl;
    }
    return 0;
}
