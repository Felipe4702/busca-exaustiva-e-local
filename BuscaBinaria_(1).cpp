#include <iostream> 
#include <bitset>
#include <string>
#include <cmath>
using namespace std;

int buscaexaustiva(int n){

    int qnt;
    qnt = pow(2,n);
    for(int i = 0; i < qnt; i++){

        string binariofull = bitset<32>(i).to_string();
        string stringbinario = binariofull.substr(32-n);
        cout << stringbinario << "\n";
    
        }

    return 0;
    }

int main(){

    cout << "Digite a o tamanho da string\n";
    int n; 
    cin >> n;
    buscaexaustiva(n);

    return 0;
}
