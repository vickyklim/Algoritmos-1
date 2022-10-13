#include <iostream>
#include <string>

using namespace std;

bool subsecuencia(string s, string t) {
    bool res = true;
    int iterante = 0;
    while (iterante < s.size()) {
        for (int i = 0; i < t.size(); i++) {
            if (t[i] == s[iterante]) {
                iterante++;
            }
        }
        if (iterante<s.size()){
            res= false;
            iterante = s.size();
        }
    }
    return res;
}

int main()
{
    /* No hace falta modificar el main */
    // Leo la entrada
    string s, t;
    cin >> s >> t;
    
    bool res = subsecuencia(s, t);
    cout << (res ? "true" : "false");
    return 0;
}

