#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <ctime>

using namespace std;

vector<int> extrairDadosLimpos(const string& nomeArquivo) {
    vector<int> dados;
    ifstream arquivo(nomeArquivo);
    string linha;
    if (!arquivo.is_open()) return dados; 
    while (getline(arquivo, linha)) {
        size_t pos = linha.find('#');
        if (pos != string::npos) linha = linha.substr(0, pos); 
        stringstream ss(linha);
        int valor;
        while (ss >> valor) dados.push_back(valor);
    }
    arquivo.close();
    return dados;
}

vector<vector<int>> carregarMatrizAdjacencia(const string& nomeArquivo) {
    vector<int> dados = extrairDadosLimpos(nomeArquivo);
    if (dados.empty() || dados.size() < 2) return {};
    int numVertices = dados[0], numArestas = dados[1];
    vector<vector<int>> matrizAdj(numVertices, vector<int>(numVertices, 0));
    int index = 2; 
    for (int i = 0; i < numArestas && (index + 2) < dados.size(); ++i) {
        matrizAdj[dados[index] - 1][dados[index + 1] - 1] = dados[index + 2];
        index += 3; 
    }
    return matrizAdj;
}

void construir_caminho(int n, vector<vector<int>>& matriz, vector<int>& caminho, vector<bool>& visitado) {
    if (caminho.size() == n) {
        for (int i = 0; i < n; i++) cout << caminho[i] + 1 << " ";
        cout << "\n";
        return; 
    }
    int ultima = caminho.empty() ? -1 : caminho.back();
    for (int i = 0; i < n; i++) {
        if (!visitado[i] && (ultima == -1 || matriz[ultima][i] > 0)) {
            visitado[i] = true;
            caminho.push_back(i);
            construir_caminho(n, matriz, caminho, visitado);
            caminho.pop_back();
            visitado[i] = false;
        }
    }
}

int main() {
    string arquivo = "in.txt";
    vector<vector<int>> matriz = carregarMatrizAdjacencia(arquivo);
    if (matriz.empty()) {
        cout << "Erro ao carregar grafo.\n";
        return 1;
    }
    
    int n = matriz.size();
    vector<int> caminho;
    vector<bool> visitado(n, false);
    
    clock_t inicio = clock();
    construir_caminho(n, matriz, caminho, visitado);
    clock_t fim = clock();
    
    cout << "Tempo: " << double(fim - inicio) / CLOCKS_PER_SEC << " segundos\n";
    return 0;
}
