#include <iostream>
#include <vector>

using namespace std;

bool esCreciente(vector <int> v){
    bool res = false;
    if (v.size()<=1){
        res = true;
    } else {
        int i = 0;
        if (v[0] <= v[1]){
            while (i < (v.size()-1)){
                if (v[i] <= v[i+1]){
                    res = true;
                    i++;
                } else {
                    return false;
                }
            }
        }
    } return res;
}

bool esDecreciente(vector <int> v){
    bool res = false;
    if (v.size()<=1){
        res = true;
    } else {
        int i = 0;
        if (v[0] >= v[1]){
            while (i < (v.size()-1)){
                if (v[i] >= v[i+1]){
                    res = true;
                    i++;
                } else {
                    return false;
                }
            }
        }
    } return res;
}

bool estaOrdenado(vector<int> v) {
    return (esCreciente(v) or esDecreciente(v));
}
    
int main() {
    /* No hace falta modificar el main */
    // Leo las entradas
    int n; 
    cin >> n;
    int i = 0;
    int x;
    vector<int> v;// En v leo el vector
    while (i<n){
        cin >> x;
        v.push_back(x);
        i++;
    }
    
    // Evaluo si el vector v esta ordenado
    bool res = estaOrdenado(v);
    
    // Imprimo la salida
    cout << (res?"True":"False");
    
    return 0;
}
