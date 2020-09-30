#include <iostream>
#include <vector>

#define endl '\n'
#define vvi vector<vector<int> >
#define vi vector<int>

using namespace std;

vi eje_x = {0, 1, -1, 1, 0, -1};
vi eje_z = {-1, -1, 0, 0, 1, 1};

void dfs_aux(vvi &visitados, int i, int j, vi &temp, int &num){
    visitados[i][j] = num;
    if(i == 0) temp[2] = 1;

    if(j == 0){
        for(int k = 0; k < visitados.size(); ++k){
            int l = visitados[k].size() - 1;
            if(visitados[i][0] == visitados[k][l]) temp[0] = temp[1] = 1;
        }  
    }

    else if(j == visitados[i].size() - 1){
        for(int k = 0; k < visitados.size(); ++k){
            if(visitados[i][j] == visitados[k][0]) temp[0] = temp[1] = 1;
        }
    }

    for(int k = 0; k < 6; ++k){
        int ejex = i + eje_x[k], ejey = j + eje_z[k];
        if(ejex >= 0 && ejex < visitados.size()){
            if(ejey >= 0 && ejey < visitados[ejex].size()){
                if(!visitados[ejex][ejey]){
                    dfs_aux(visitados, ejex, ejey, temp, num);
                }
            }
        }
    }
}

bool dfs(vvi &visitados){
    int num = 0;
    for(int i = 0; i < visitados.size(); ++i){
        for(int j = 0; j < visitados[i].size(); ++j){
            vi temp(3, 0);
            if(!visitados[i][j]) dfs_aux(visitados, i, j, temp, ++num);
            
            if(temp[0] == temp[1] && temp[1] == temp[2] && temp[0] == 1) return true;
        }
    }
    return false;
}

int main(){
    int n, m;
    while(cin >> n >> m, n || m){
        vvi visitados(n + 1);
        for(int i = n; i >= 0; --i){ 
            vi temp(i + 1, - 1);
            visitados[n - i] = temp;
        }

        for(int i = 0; i < m; ++i){
            int x, y, z;
            cin >> x >> y >> z;
            visitados[z][x] = 0;
        }

        if(dfs(visitados)) cout << "Benny" << endl;

        else cout << "Willy" << endl;
    }
    return 0;
}
