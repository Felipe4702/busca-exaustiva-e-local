#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>

using namespace std;

void busca_exaustiva_permutacoes(int n) {
    vector<int> cidades;
    for (int i = 1; i <= n; i++) {
        cidades.push_back(i);
    }

    clock_t inicio = clock();
    do {
        for (int i = 0; i < n; i++) cout << cidades[i] << " ";
        cout << "\n";
    } while (next_permutation(cidades.begin(), cidades.end()));
    
    clock_t fim = clock();
    cout << "Tempo de processamento: " << double(fim - inicio) / CLOCKS_PER_SEC << " segundos\n";
}

int main() {
    int n;
    cout << "Digite o numero de cidades: ";
    cin >> n;
    busca_exaustiva_permutacoes(n);
    return 0;
}
