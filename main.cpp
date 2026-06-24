#include "terreno.h"
#include "sombreamento.h"
#include <string>
#include <iostream>
#include <cmath>

constexpr float RUGOSIDADE = 0.56f;
constexpr float FATOR_SOMBREAMENTO = 0.7f;

using namespace std;

struct Config {
    int expoente = 10;
    float rugosidade = 0.56f;
    float fatorSombra = 0.8f;
    float escalaSombra = 5.0f;
    string paleta = "data/paletas/palette6.txt";
    string saida = "data/imagens/output.ppm";
    int metodoSombra = 1; // 0 = vizinhos top left, 1 = vizinhos adjacentes, 2 = gradiente
};

void mostrarMenu(Config& cfg) {
    string metodos[] = {"Vizinho top left", "Vizinhos adjacentes", "Gradiente"};

    system("clear");
    cout << "=== Gerador de Terreno ===" << endl << endl;
    cout << "  1. Tamanho:       " << (1<<cfg.expoente)+1 << " (exp " << cfg.expoente << ")" << endl;
    cout << "  2. Rugosidade:    " << cfg.rugosidade << endl;
    cout << "  3. Paleta:        " << cfg.paleta << endl;
    cout << "  4. Fator sombra:  " << cfg.fatorSombra << endl;
    cout << "  5. Escala sombra: " << cfg.escalaSombra << endl;
    cout << "  6. Metodo sombra: " << metodos[cfg.metodoSombra] << endl;
    cout << "  7. Saida:         " << cfg.saida << endl << endl;
    cout << "  [1-7] Alterar  [G] Gerar  [Q] Sair: ";
}

char esperarEscolha() {
    string s; cin >> s;
    return toupper(s[0]);
}

void gerarTerreno(const Config& cfg) {
    srand(time(NULL));
    int dim = (1 << cfg.expoente) + 1;

    cout << "\nGerando terreno " << dim << "x" << dim << "..." << endl;

    Terreno terreno{dim};
    Paleta paleta{cfg.paleta};
    terreno.gerarMapa(cfg.rugosidade);
    Imagem imagem = terreno.obterImagem(paleta, cfg.fatorSombra);

    switch (cfg.metodoSombra) {
        case 0:
            sombreamentoVizinhoTopLeft(terreno, imagem, cfg.fatorSombra);
            break;
        case 1:
            sombreamentoVizinhos(terreno, imagem, cfg.fatorSombra);
            break;
        case 2:
            sombreamentoGradiente(terreno, imagem, cfg.escalaSombra);
            break;
    }

    imagem.salvarPPM(cfg.saida);
    cout << "Imagem salva em: " << cfg.saida << endl;
    cout << "Pressione Enter para continuar...";
    string dummy;
    cin.ignore();
    getline(cin, dummy);
}

int main() {
    char escolha;
    Config config;
    string inputStr;
    float inputFloat;
    int inputInt;

    do {
        mostrarMenu(config);
        escolha = esperarEscolha();

        switch (escolha) {
            case '1':
                cout << "Expoente (6-14): ";
                cin >> inputInt;
                if (inputInt >= 6 && inputInt <= 14) config.expoente = inputInt;
                break;
            case '2':
                cout << "Rugosidade (0.1-1.0): ";
                cin >> inputFloat;
                config.rugosidade = inputFloat;
                break;
            case '3':
                cout << "Caminho da paleta: ";
                cin >> config.paleta;
                break;
            case '4':
                cout << "Fator de sombreamento (0.0-1.0): ";
                cin >> inputFloat;
                config.fatorSombra = inputFloat;
                break;
            case '5':
                cout << "Escala de sombreamento (1.0-20.0): ";
                cin >> inputFloat;
                config.escalaSombra = inputFloat;
                break;
            case '6':
                cout << "Metodo (0=Vizinho NW, 1=Vizinhos, 2=Gradiente): ";
                cin >> inputInt;
                if (inputInt >= 0 && inputInt <= 2) config.metodoSombra = inputInt;
                break;
            case '7':
                cout << "Caminho de saida: ";
                cin >> config.saida;
                break;
            case 'G':
                gerarTerreno(config);
                break;
        }
    } while (escolha != 'Q');

    return 0;
}



// int main1() {
//     srand(time(NULL));
//     string caminhoPaleta = "data/palette6.txt";
//     string caminhoImagemSaida = "data/img.ppm";
//     int expoente = 10;

//     cout << "Informe o nome do arquivo com a paleta de cores: " << endl;
//     cin >> caminhoPaleta;
//     cout << "Informe o expoente para gerar a dimensão do mapa: " << endl;
//     cin >> expoente;
//     cout << "Informe o caminho do arquivo imagem de saída: " << endl;

//     cin >> caminhoImagemSaida;

//     // cout << caminhoPaleta << expoente << caminhoImagemSaida << endl;
//     // cout << (int)(pow(2, expoente)) << endl;


//     // Terreno terreno{513};
//     Terreno terreno{(int)(pow(2, expoente))+1};
//     Paleta paleta{caminhoPaleta};
//     terreno.gerarMapa(RUGOSIDADE);
//     Imagem imagem = terreno.obterImagem(paleta, FATOR_SOMBREAMENTO);

//     sombreamento(terreno, imagem);

//     imagem.salvarPPM(caminhoImagemSaida);
// }