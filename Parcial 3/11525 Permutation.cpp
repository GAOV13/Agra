#include <bits/stdc++.h>

#define vi vector<int>
#define endl '\n'

using namespace std;

//Mejorar usando arboles de fenwick

int main(){
    int n;
    cin >> n;
    while(n--){
        int m;
        cin >> m;
        vi info(m);
        for(int i = 0; i < m; ++i) info[i] = i + 1;

        for(int i = 0; i < m; ++i){
            int si;
            cin >> si;
            if(i > 0) cout << ' ';

            cout << info[si];
            info.erase(info.begin() + si);
        }
        cout << endl;
    }
    return 0;
}
