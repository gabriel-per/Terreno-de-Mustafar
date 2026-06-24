#ifndef IMAGEM_H
#define IMAGEM_H

#include "pixel.h"
#include <string>

class Imagem {
    int largura;
    int altura;
    Pixel *matriz = nullptr;
    int maxVal = 255;

public:
    Imagem(int a=0, int l=0);
    ~Imagem();

    void alocar(int a, int l);
    Pixel& obterPixel(int x, int y);
    Pixel& obterPixel(int i);
    const Pixel& obterPixel(int x, int y) const;
    int obterAltura();
    int obterLargura();
    void definirPixel(int x, int y, unsigned char R, unsigned char G, unsigned char B);
    void definirPixel(int i, unsigned char R, unsigned char G, unsigned char B);
    Pixel& operator()(int x, int y);
    const Pixel& operator()(int x, int y) const;
    bool lerPPM(const std::string& caminho);
    bool salvarPPM(const std::string& caminho);
};

#endif
