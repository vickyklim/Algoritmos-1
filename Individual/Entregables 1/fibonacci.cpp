#include <iostream>

using namespace std;

// Funcion de fibonacci que calcula n-esimo termino
int fibonacci(int n){
    int n1=0, n2=1, fibo = n, i;
    for (i=1; i<n; ++i){
        fibo = 0;
        fibo = n1+n2;
        n1=n2;
        n2=fibo;
    }
    return fibo;
}

int main() 
{
    int n;
    cin >> n;
    cout << fibonacci(n) << endl;    
    return 0;
}