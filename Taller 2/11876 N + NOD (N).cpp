#include <iostream>
#include <vector>

#define vi vector<int>
#define endl '\n'

using namespace std;

int upperS(vi &lista, int num, int low, int hi){
    int mid = (low + hi) >> 1; 
    if(low == mid) return hi;
    
    if(lista[mid] <= num) return upperS(lista, num, mid, hi);

    else return upperS(lista, num, low, mid);
}

int lowerS(vi &lista, int num, int low, int hi){
    int mid = (low + hi) >> 1;
    if(mid == low){ 
        if(lista[mid] == num) return mid; 

        else return mid + 1;
    }
    
    if(lista[mid] < num) return lowerS(lista, num, mid, hi);

    else return lowerS(lista, num, low, mid);
}

int nod(int n){
	int suma = 0;
	for (int i = 1; i <= n / i; i++) {
		if(n % i == 0){
			if(n/i == i) suma++;
			
			else suma += 2;
		}
	}
	return suma;
}

int main(){
	int n, min, max, k, casos = 0;
	vi lista;
	int itrf, itre;
	lista.push_back(1);
	cin >> n;
	while(n--){
		cin >> min >> max;
		while(lista[lista.size() - 1] <= 1000000 && lista[lista.size() - 1] <= max){
			k = nod(lista[lista.size() - 1]);
			k += lista[lista.size() - 1];
			lista.push_back(k);
		}

		itrf = lowerS(lista, min, 0, lista.size());
		itre = upperS(lista, max, 0, lista.size());
		k = itre - itrf;
		cout << "Case " << ++casos << ": " << k << endl;
	}

	cout << lista[lista.size() - 1] << endl;
	return 0;
}
