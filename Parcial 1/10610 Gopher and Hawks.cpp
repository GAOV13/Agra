#include <iostream>
#include <vector>
#include <queue>
#include <cmath>
#include <sstream>

#define vH vector<Hole>
#define vi vector<int>
#define qH queue<Hole>
#define endl '\n'

using namespace std;

class Hole{
    public:
        int num;
        double x;
        double y;
    
        Hole(int n){
           num = n;
        }
};

double string_numero(string str){
    stringstream stream(str);
    double n;
    stream >> n;
    return n;
}

void lectura(string str, Hole &hueco){
    stringstream stream(str);
    double x, y;
    while(getline(stream, str, ' ')){
        stringstream stream1(str);
        x =  y;
        y = string_numero(str);
    }
    hueco.x = x;
    hueco.y = y;
}

void bfs(vH &huecos, vi &visitados, int vel, int m){
    Hole *hueco = &huecos[0];
    visitados[hueco->num] = 0;
    qH cola;
    cola.push(huecos[0]);
    while(!cola.empty()){
        hueco = &(huecos[cola.front().num]); cola.pop();
        if(hueco->num == huecos.size() - 1) break;

        for(int i = 0; i < huecos.size(); ++i){
            if(visitados[huecos[i].num] == -1){
                double dist = sqrt(pow(huecos[i].x - hueco->x, 2) + pow(huecos[i].y - hueco->y, 2));
                double k = 60;
                if(dist <= (double)(k*(double)vel)*(double)m){
                    visitados[huecos[i].num] = visitados[hueco->num] + 1;
                    cola.push(huecos[i]); 
                }
            }
        }
    }
}

int main(){
    int vel, min;
    cin >> vel >> min;
    while(vel || min){
        cin.ignore();
        int num = 0;
        vH huecos;
        string ini, fin;
        getline(cin, ini);
        Hole hueco(num++);
        lectura(ini, hueco);
        huecos.push_back(hueco);
        getline(cin, fin);
        getline(cin, ini);
        while(ini != ""){
            hueco.num = num++;
            lectura(ini, hueco);
            huecos.push_back(hueco);
            getline(cin, ini);
        }

        hueco.num = num++;
        lectura(fin, hueco);
        huecos.push_back(hueco);
        vi visitados(num, -1);
        bfs(huecos, visitados, vel, min);
        if(visitados[num - 1] == -1) cout << "No." << endl;

        else cout << "Yes, visiting " << visitados[num - 1] - 1<< " other holes." << endl;
        cin >> vel >> min;
    }
    return 0;
}
