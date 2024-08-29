


#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <map>
#include <string>

using namespace std;

int Numero_Aleatorio(int max) {
    return rand() % max;
}

int Quem_Comeca() {
    int escolha = rand() % 2;
    return (escolha == 0) ? 1 : -1;
}

int Ganhador(int Velha[9]) {
    int combinacoes[8][3] = {
        {0, 1, 2}, {3, 4, 5}, {6, 7, 8}, // Linhas
        {0, 3, 6}, {1, 4, 7}, {2, 5, 8}, // Colunas
        {0, 4, 8}, {2, 4, 6}             // Diagonais
    };

    for (int i = 0; i < 8; i++) {
        if (Velha[combinacoes[i][0]] == Velha[combinacoes[i][1]] && 
            Velha[combinacoes[i][1]] == Velha[combinacoes[i][2]] &&
            Velha[combinacoes[i][0]] != 0) {
            return Velha[combinacoes[i][0]];
        }
    }

    return 0;
}

void Imprime_Tabuleiro(int Velha[9]) {
    for (int i = 0; i < 9; i++) {
        cout << (Velha[i] == 0 ? ". " : (Velha[i] == 1 ? "X " : "O "));
        if ((i + 1) % 3 == 0) cout << endl;
    }
}

void Salva_Jogadas_Vencedoras(ofstream &arquivo, vector<int> &jogadas) {
    for (int pos : jogadas) {
        arquivo << pos;
    }
    arquivo << endl;
}

void Agrupar_Jogadas_Repetidas(const string &arquivoEntrada, const string &arquivoSaida) {
    ifstream entrada(arquivoEntrada);
    ofstream saida(arquivoSaida);
    map<string, int> jogadas_repetidas;

    if (!entrada) {
        cerr << "Erro ao abrir o arquivo de entrada!" << endl;
        return;
    }

    if (!saida) {
        cerr << "Erro ao abrir o arquivo de saída!" << endl;
        return;
    }

    string linha;
    while (getline(entrada, linha)) {
        jogadas_repetidas[linha]++;
    }

    for (const auto &par : jogadas_repetidas) {
        saida << par.first << " " << par.second << endl;
    }

    entrada.close();
    saida.close();
}

int main() {
    srand(time(0));

    int Velha[9] = {0};
    int cont = 0, Jogador = Quem_Comeca();
    int vencedor = 0;

    vector<int> jogadas_jogador1, jogadas_jogador2;

    string arquivoSeqVencedora = "C:/Users/samue/Documents/Optativa/Jogo_da_Velha/seq_vencedora.txt";
    string arquivoJogadasAgrupadas = "C:/Users/samue/Documents/Optativa/Jogo_da_Velha/jogadas_agrupadas.txt";

    // Abre o arquivo para salvar as jogadas vencedoras
    ofstream arquivo(arquivoSeqVencedora, ios::app);
    if (!arquivo) {
        cerr << "Erro ao abrir o arquivo para salvar as jogadas vencedoras!" << endl;
        return 1;
    }

    cout << "Quem comeca e: " << (Jogador == 1 ? "Jogador 1 (X)" : "Jogador 2 (O)") << endl;

    while (cont < 9 && vencedor == 0) {
        int aux = Numero_Aleatorio(9);
        if (Velha[aux] == 0) {
            Velha[aux] = Jogador;
            cont++;

            if (Jogador == 1) {
                jogadas_jogador1.push_back(aux);
            } else {
                jogadas_jogador2.push_back(aux);
            }

            Jogador = -Jogador;
            vencedor = Ganhador(Velha);
        }
    }

    Imprime_Tabuleiro(Velha);

    if (vencedor == 0) {
        cout << "Empate!" << endl;
    } else {
        cout << "O vencedor e o Jogador " << (vencedor == 1 ? "1 (X)" : "2 (O)") << endl;
        // Salva as jogadas vencedoras no arquivo
        if (vencedor == 1) {
            Salva_Jogadas_Vencedoras(arquivo, jogadas_jogador1);
        } else {
            Salva_Jogadas_Vencedoras(arquivo, jogadas_jogador2);
        }
    }

    // Fecha o arquivo de jogadas vencedoras
    arquivo.close();

    // Agrupa as jogadas vencedoras repetidas e salva em outro arquivo
    Agrupar_Jogadas_Repetidas(arquivoSeqVencedora, arquivoJogadasAgrupadas);

    cout << "Jogadas vencedoras agrupadas e contadas com sucesso." << endl;

    return 0;
}






