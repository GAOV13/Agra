#include <iostream>
#include <vector>
#include <sstream>
#include <queue>

#define vi vector<int>
#define vvi vector<vector<int> >
#define qi queue<int>
#define endl '\n'

using namespace std;

int stringANumero(string str){
    stringstream stream(str);
    int n;
    stream >> n;
    return n;
}

vi buscarPares(string str){
    vi dev;
    stringstream stream(str);
    string temp;
    int i = 0;
    while(getline(stream, temp, '-')){
        if(i == 0){ 
            ++i;
            continue;
        }

        stringstream stream1(temp);
        string temp1;
        while(getline(stream1, temp1, ',')){
            int n = stringANumero(temp1);
            dev.push_back(n);
        }
    }
    return dev;
}

void bfs(int nodo_ini, int nodo_fin, vi &visitado, vi &padre, vvi &grafo){
    qi cola;
    cola.push(nodo_ini);
    ++visitado[nodo_ini];
    padre[nodo_ini] = nodo_ini;
    while(!cola.empty()){
        int nodo = cola.front(); cola.pop();
        if(nodo == nodo_fin) break;

        for(int i = 0; i < grafo[nodo].size(); ++i){
            int aux = grafo[nodo][i];
            if(!visitado[aux]){
                ++visitado[aux];
                padre[aux] = nodo;
                cola.push(aux);
            }
        }
    }
}

int main(){
    int n;
    while(cin >> n){
        cout << "-----" << endl;
        vvi grafo(n + 1, vector<int>(0));
        for(int i = 1; i <= n; ++i){
            string str;
            cin >> str;
            vi temp = buscarPares(str);
            grafo[i] = temp;
        }

        int m;
        cin >> m;
        while(m--){
            vi visitado(n + 1, 0);
            vi padre(n + 1, -1);
            int nodo_ini, nodo_fin;
            cin >> nodo_ini >> nodo_fin;
            bfs(nodo_ini, nodo_fin, visitado, padre, grafo);
            if(visitado[nodo_fin] == 0) cout << "connection impossible" << endl;

            else{
                vi dev;
                int hijo = nodo_fin;
                dev.push_back(hijo);
                while(hijo != nodo_ini){
                    hijo = padre[hijo];
                    dev.push_back(hijo);
                }

                cout << dev[dev.size() - 1];
                for(int i = dev.size() - 2; i >= 0; --i) cout << " " << dev[i];

                cout << endl;
            }
        }
    }
    return 0;
}
