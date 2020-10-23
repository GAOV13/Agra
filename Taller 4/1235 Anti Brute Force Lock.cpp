#include <bits/stdc++.h>

#define endl '\n'
#define mii map<int, int>
#define vi vector<int>
#define pqpii priority_queue<pair<int, int> >
#define pii pair<int, int>

using namespace std;

int distancia(int num1, int num2){
    int d = 0;
    for(int i = 0; i < 4; ++i){
        int n1 = num1 % 10, n2 = num2 % 10;
        int d1 = max(n2, n1) - min(n2, n1), d2 = min(n2, n1) + 10 - max(n1, n2);
        d += min(d1, d2);
        num1 /= 10;
        num2 /= 10;
    }

    return d;
}

void dikstra(mii &pos, vi &listado, vi &dist, vi &visitados, int d, int num){
    pqpii cola;
    dist[pos[num]] = d;
    cola.push(make_pair(d * -1, num));
    while(!cola.empty()){
        pii par = cola.top(); cola.pop();
        int dis = par.first * -1, u = pos[par.second];
        if(dis == dist[u] && !visitados[u]){
            ++visitados[u];
            for(int i = 0; i < listado.size(); ++i){
                d = distancia(listado[u], listado[i]);
                if(!visitados[i] && d < dist[i]){
                    dist[i] = d;
                    cola.push(make_pair(d * -1, listado[i]));
                }
            }
        }
    }
}

int main(){
    int n;
    cin >> n;
    while(n--){
        mii pos;
        int tam;
        cin >> tam;
        vi listado(tam), dist(tam, 2147483647), visitados(tam, 0);
        for(int i = 0; i < tam; ++i){
            cin >> listado[i];
            pos[listado[i]] = i;
        }

        int dev = 2147483647;
        int num;
        for(int i = 0; i < tam; ++i){
            int d = distancia(0, listado[i]);
            if(d < dev){
                dev = d;
                num = listado[i];
            }
        }

        dikstra(pos, listado, dist, visitados, dev, num);
        dev = 0;
        for(int i = 0; i < tam; ++i) dev += dist[i];

        cout << dev << endl; 
    }
    return 0;
}