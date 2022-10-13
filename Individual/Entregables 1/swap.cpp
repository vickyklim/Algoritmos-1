#include <iostream>

using namespace std;

void swap (int &x, int &y){
    x = x + y;
    y = x - y; //y=x
    x = x - y;
}

int main() {
    /* No hace falta modificar el main */
    int a,b;
    //Leo a
    cin >> a >> b;
    
    swap(a,b);
    
    //Devuelvo despues del swap
    cout << a << " " << b;
    return 0;
}
