#include <vector>
#include <iostream>

using namespace std;

bool estaOrdenada(vector <int> v){
    for (int i=0; i< v.size()-1; i++){
        if (v[i] > v[i+1]){
            return false;
        }
    } return true;
}

void swap (int &x, int &y){
    x = x + y;
    y = x - y; //y=x
    x = x - y;
}



void ordenar1(vector<int> &v) {
    if (not estaOrdenada(v)) {
        for (int i = 0; i < v.size(); i++) {
            for (int j = i+1; j < v.size(); j++) {
                if (v[i] > v[j]) {
                    swap(v[i], v[j]);
                }
            }
        }
    }
}

int main() {
    /* No hace falta modificar el main */
    
    // Leo las entradas
    int n; //Longitud del vector
    cin >> n;
    int i = 0;
    int x;
    vector<int> v;// En v leo el vector
    while (i<n){
        cin >> x;
        v.push_back(x);
        i++;
    }

    // Hago el ordenamiento
    ordenar1(v);
    
    // Imprimo el vector resultado
    i = 0;
    while (i < v.size()){
        cout << v[i] << " ";
        i++;
    }
    
    return 0;
}
