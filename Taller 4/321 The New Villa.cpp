#include <bits/stdc++.h>

#define vvi vector<vector<int> >
#define vi vector<int>
#define vb vector<bool>
#define vE vector<Estado>
#define vpii vector<pair<int, int> >
#define pii pair<int, int>
#define pqE priority_queue<Estado>
#define endl '\n'

using namespace std;

class Estado{
    public:
        int peso;
        int ubi;
        vb estados_Luz;
        vpii inst;

        Estado(int peso, int ubi, vb luz, vpii inst){
            this->peso = peso;
            this->ubi = ubi;
            estados_Luz = luz;
            this->inst = inst;
        }

        bool operator==(const Estado &e){
            bool ver = true;
            for(int i = 0; i < this->estados_Luz.size() && ver; ++i){
                if(this->estados_Luz[i] != e.estados_Luz[i]) ver = false;
            }
            return this->ubi == e.ubi && ver;
        }

};

bool operator<(const Estado& e1, const Estado& e2){
    return e1.peso > e2.peso; 
} 

pair<bool, int> dikstra(vvi &grafop, vvi &grafol, vE &estados){
    pqE cola;
    cola.push(estados[0]);

    Estado fin(0, grafop.size() - 1, vb(grafop.size() - 1, false), vpii(0));
    fin.estados_Luz[grafol.size() - 1] = true;
    while(!cola.empty()){
        Estado e = cola.top(); cola.pop();
        if(e == fin){
            for(int i = 0; i < estados.size(); ++i){
                if(e == estados[i]) return make_pair(true, i);
            }
        }

        int k;
        for(int i = 0; i < estados.size(); ++i){
            if(e == estados[i]){
                k = i;
                break;
            }
        }

        if(e.peso == estados[k].peso){
            int u = estados[k].ubi;
            vb temp1 = estados[k].estados_Luz;
            vpii temp2 = estados[k].inst;
            for(int i = 0; i < grafol[u].size(); ++i){
                int v = grafol[u][i];
                if(v != u){
                    temp1[v] = !temp1[v];
                    if(temp1[v]) temp2.push_back(make_pair(1, v));

                    else temp2.push_back(make_pair(0, v));
                    Estado e1(e.peso + 1, u, temp1, temp2);
                    int j = 0;
                    for(int in = 0; in < estados.size(); ++in){
                        if(e1 == estados[in]){
                            j = in;
                            break;
                        }
                    }

                    if(!j){
                        estados.push_back(e1);
                        cola.push(e1);
                    }

                    else{
                        if(e1.peso < estados[j].peso){
                            estados[j].peso = e1.peso;
                            estados[j].inst = temp2;
                            cola.push(e1);
                        }
                    }

                    temp1[v] = !temp1[v];
                    temp2.pop_back();
                }
            }

            for(int i = 0; i < grafop[u].size(); ++i){
                int v = grafop[u][i];
                if(temp1[v]){
                    temp2.push_back(make_pair(2, v));
                    Estado e1(e.peso + 1, v, temp1, temp2);
                    int j = 0;
                    for(int in = 0; in < estados.size(); ++in){
                        if(e1 == estados[in]){
                            j = in;
                            break;
                        }
                    }

                    if(!j){
                        estados.push_back(e1);
                        cola.push(e1);
                    }

                    else{
                        if(e1.peso < estados[j].peso){
                            estados[j].peso = e1.peso;
                            estados[j].inst = temp2;
                            cola.push(e1);
                        }
                    }

                    temp2.pop_back();
                }
            }
        }
    }
    return make_pair(false, 0);
}


int main(){
    int r, d, s, casos = 0;
    while(cin >> r >> d >> s, r || d || s){
        vvi grafop(r + 1), grafol(r + 1);
        vE estados;
        for(int i = 0; i < d; ++i){
            int ini, fin;
            cin >> ini>> fin;
            grafop[ini].push_back(fin);
            grafop[fin].push_back(ini);
        }

        for(int i = 0; i < s; ++i){
            int ini, fin;
            cin >> ini>> fin;
            grafol[ini].push_back(fin);
        }
        
        estados.push_back(Estado(0, 1, vb(r + 1, false), vpii(0)));
        estados[0].estados_Luz[1] = true;
        pair<bool, int> par = dikstra(grafop, grafol, estados);

        cout << "Villa #" << ++casos << endl;
        if(par.first){
            cout << "The problem can be solved in " << estados[par.second].peso << " steps:" << endl;
            for(int i = 0; i < estados[par.second].inst.size(); ++i){
                if(estados[par.second].inst[i].first == 0)
                    cout << "- Switch off light in room " << estados[par.second].inst[i].second << '.' << endl;
                
                else if(estados[par.second].inst[i].first == 1)
                    cout << "- Switch on light in room " << estados[par.second].inst[i].second << '.' << endl;

                else
                    cout << "- Move to room " << estados[par.second].inst[i].second << '.' << endl;
            }
        }

        else cout << "The problem cannot be solved." << endl;
        
        cout << endl;
    }
    return 0;
}
