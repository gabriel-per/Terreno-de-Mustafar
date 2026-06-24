#ifndef TERRENO_H
#define TERRENO_H

#include <string>

float valorAleatorio();

class Terreno {
    int dim;
    float *matriz = nullptr;

    void mediaDiamante(int x, int y, int passo, float offset);
    void mediaSquare(int x, int y, int passo, float offset);
    void alocar();
    bool coordenadaValida(int x, int y);

public:
    Terreno(int d);
    ~Terreno();

    void gerarMapa(float fatorRugosidade);

    float obterAltitude(int x, int y);
    int obterQuantidadeLinhas();
    int obterQuantidadeColunas();

    bool salvarArquivo(const std::string& caminho);
    bool lerArquivo(const std::string& caminho);
};

#endif
