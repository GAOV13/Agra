#include <bits/stdc++.h>

#define vvi vector<vector<int> >
#define vvd vector<vector<double> >
#define vi vector<int>
#define vd vector<double>
#define pdi pair<double, int>
#define endl '\n'

using namespace std;

double dikstra(vvi &grafo, vvd &pesoA, vvd &pesoB, vd &peso, double por, int n){
    priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>> > cola;
    double zero = 0;
    double menos_uno = -1;
    double uno = 1;
    peso[0] = zero;
    cola.push(make_pair(zero, 0));
    while(!cola.empty()){
        pdi par = cola.top(); cola.pop();
        double pes = par.first; 
        int u = par.second;
        if(u == n - 1) return pes;

        if(peso[u] == pes){
            for(int i = 0; i < grafo[u].size(); ++i){
                int v = grafo[u][i];
                double temp;
                if(pesoA[u][v] == menos_uno) temp = pesoB[u][v];

                else if(pesoB[u][v] == menos_uno) temp = pesoA[u][v];
            
                else{
                    double por2 = uno - por;
                    temp = (pesoA[u][v] * por) + (por2 * pesoB[u][v]);
                }
                
                if(peso[u] + temp < peso[v]){
                    peso[v] = peso[u] + temp;
                    cola.push(make_pair(peso[v], v));
                }  
            }
        }
    }
    return peso[n - 1];
}

int main(){
    int n, ma, mb, k;
    double menos_uno = -1;
    while(cin >> n >> ma >> mb >> k, n != -1){
        vvi grafo(n);
        vvd pesoA(n, vd(n, menos_uno)), pesoB(n, vd(n, menos_uno));
        for(int i = 0; i < ma; ++i){
            int ini, fin;
            double cost;
            cin >> ini >> fin;
            cin >> cost;
            grafo[ini].push_back(fin);
            grafo[fin].push_back(ini);
            pesoA[ini][fin] = cost;
            pesoA[fin][ini] = cost;
        }

        for(int i = 0; i < mb; ++i){
            int ini, fin;
            double cost;
            cin >> ini >> fin;
            cin >> cost;
            grafo[ini].push_back(fin);
            grafo[fin].push_back(ini);
            pesoB[ini][fin] = cost;
            pesoB[fin][ini] = cost;
        }

        for(int i = 0; i < k; ++i){
            double tam = 2147483647;
            vd peso(n, tam);
            double por;
            cin >> por;
            cout << (int)dikstra(grafo, pesoA, pesoB, peso, por, n) << endl;
        }
    }
    return 0;
}
