#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <ctime>

using namespace std;

struct ItemMochila { int peso; int valor; };

bool carregar_mochila(const string& nome, vector<ItemMochila>& itens, int& cap) {
    ifstream arquivo(nome);
    if (!arquivo.is_open()) return false;
    int n;
    arquivo >> n >> cap;
    itens.clear();
    for (int i = 0; i < n; i++) {
        int v, w;
        arquivo >> v >> w;
        itens.push_back({w, v});
    }
    return true;
}

int avaliar_mochila(string solucao, vector<ItemMochila>& itens, int cap) {
    int peso = 0, valor = 0;
    for (size_t i = 0; i < solucao.length(); i++) {
        if (solucao[i] == '1') {
            peso += itens[i].peso;
            valor += itens[i].valor;
        }
    }
    return (peso > cap) ? -1 : valor;
}

int main() {
    string nome_arquivo;
    cout << "Nome do arquivo da mochila: ";
    cin >> nome_arquivo;

    vector<ItemMochila> itens;
    int cap;
    if (!carregar_mochila(nome_arquivo, itens, cap)) {
        cout << "Erro ao ler arquivo.\n";
        return 1;
    }

    int n = itens.size();
    string solucao_atual(n, '0');
    int melhor_valor = avaliar_mochila(solucao_atual, itens, cap);
    
    clock_t inicio = clock();
    for (int iter = 0; iter < 1000; iter++) {
        bool melhorou = false;
        for (int i = 0; i < n; i++) {
            string vizinho = solucao_atual;
            vizinho[i] = (vizinho[i] == '0') ? '1' : '0';
            int valor_viz = avaliar_mochila(vizinho, itens, cap);
            if (valor_viz > melhor_valor) {
                solucao_atual = vizinho;
                melhor_valor = valor_viz;
                melhorou = true;
                break;
            }
        }
        if (!melhorou) break;
    }
    clock_t fim = clock();

    cout << "Melhor solucao: " << solucao_atual << "\nValor: " << melhor_valor << "\n";
    cout << "Tempo: " << double(fim - inicio) / CLOCKS_PER_SEC << " s\n";
    return 0;
}
