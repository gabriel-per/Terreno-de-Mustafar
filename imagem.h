#ifndef IMAGEM_H
#define IMAGEM_H

#include "pixel.h"
#include <string>

class Imagem {
    int largura;
    int altura;
    Pixel *matriz;

public:
    Imagem(int a=0, int l=0);
    ~Imagem();

    void alocar(int a, int l);
    Pixel& obterPixel(int x, int y);
    const Pixel& obterPixel(int x, int y) const;
    int obterAltura();
    int obterLargura();
    void definirPixel(int x, int y, unsigned char R, unsigned char G, unsigned char B);
    Pixel& operator()(int x, int y);
    const Pixel& operator()(int x, int y) const;
    bool lerPPM(const std::string& caminho);
};

#endif
