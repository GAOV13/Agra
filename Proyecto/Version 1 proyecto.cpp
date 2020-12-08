#include <bits/stdc++.h>

#define vvp vector<vector<pair<int, int> > >
#define vp vector<pair<int, int> >
#define vi vector<int>
#define pii pair<int, int>
#define qE priority_queue<Estado>
#define mpE map<pair<int, int>, vector<Estado> >
#define endl '\n'

using namespace std;

class Estado{
    public:
        int ciudad;
        int dist;
        int sin_desc;
        int hoteles;
    
        Estado(int ciudad, int dist, int sind_desc, int hoteles){
            this->ciudad = ciudad;
            this->dist = dist;
            this->sin_desc = sind_desc;
            this->hoteles = hoteles;
        }
};

bool operator <(const Estado &e1, const Estado &e2){
    return e1.dist >= e2.dist;
}

int dikstra(vvp &grafo, vi &info, int h){
    qE cola;
    mpE mapa;
    int dev = -1;
    Estado e(1, 0, 0, 0);
    cola.push(e);
    mapa[make_pair(1, 0)].push_back(e);
    while(!cola.empty()){
        e = cola.top(); cola.pop();
        int id_ciudad = e.ciudad, id_hoteles = e.hoteles;
        int id_dist = e.dist, id_sinDesc = e.sin_desc;
        //printf("%d %d %d %d %d\n", id_ciudad, id_hoteles, id_dist, id_sinDesc, -1);
        if(id_ciudad == grafo.size() - 1 && (id_hoteles < dev || dev == -1)) dev = id_hoteles;

        if(mapa[make_pair(id_ciudad, id_hoteles)][0].dist == id_dist){
            if(id_sinDesc != 0 && id_hoteles + 1 <= h && info[id_ciudad] == 1){
                if(!mapa[make_pair(id_ciudad, id_hoteles + 1)].size()){
                    Estado e1(id_ciudad, id_dist, 0, id_hoteles + 1);
                    mapa[make_pair(id_ciudad, id_hoteles + 1)].push_back(e1);
                    //printf("%d %d %d %d %d\n", e1.ciudad, e1.hoteles, e1.dist, e1.sin_desc, -2);
                    cola.push(e1);
                }
                else{
                    Estado *e1 = &mapa[make_pair(id_ciudad, id_hoteles + 1)][0];
                    if(id_dist < (*e1).dist){
                        (*e1).dist = id_dist;
                        (*e1).sin_desc = 0;
                        Estado e2 = *e1;
                        //printf("%d %d %d %d %d\n", e2.ciudad, e2.hoteles, e2.dist, e2.sin_desc, -3);
                        cola.push(e2);
                    }
                }
            }

            for(int i = 0; i < grafo[id_ciudad].size(); ++i){
                int nueva_ciudad = grafo[id_ciudad][i].first;
                int temp = grafo[id_ciudad][i].second, temp_desc = id_sinDesc;
                temp_desc += temp;
                temp += id_dist;
                if(temp_desc <= 600){
                    if(!mapa[make_pair(nueva_ciudad, id_hoteles)].size()){
                        Estado e1(nueva_ciudad, temp, temp_desc, id_hoteles);
                        mapa[make_pair(nueva_ciudad, id_hoteles)].push_back(e1);
                        //printf("%d %d %d %d %d\n", e1.ciudad, e1.hoteles, e1.dist, e1.sin_desc, -4);
                        cola.push(e1);
                    }
                                        
                    else{
                        Estado *e1 = &mapa[make_pair(nueva_ciudad, id_hoteles)][0];
                        if(temp < (*e1).dist){
                            (*e1).dist = temp;
                            (*e1).sin_desc = temp_desc;
                            Estado e2 = *e1;
                            //printf("%d %d %d %d %d\n", e2.ciudad, e2.hoteles, e2.dist, e2.sin_desc, -5);
                            cola.push(e2);
                        }
                    }
                }
            }
        }
    }
    return dev;
}

int main(){
    int n, m, h, ci;
    int ini, fin;
    while(cin >> n, n){
        cin >> h;
        vvp grafo(n + 1);
        vi info(n + 1);
        for(int i = 0; i < h; ++i){
            cin >> ci;
            info[ci] = 1;
        }

        cin >> m;
        for(int i = 0; i < m; ++i){
            cin >> ini >> fin >> ci;
            grafo[ini].push_back(make_pair(fin, ci));
            grafo[fin].push_back(make_pair(ini, ci));
        }

        cout << dikstra(grafo, info, h) << endl;
    }
}