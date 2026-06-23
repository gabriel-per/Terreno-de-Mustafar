#include "imagem.h"
#include <iostream>
#include <fstream>
#define uc unsigned char

using namespace std;

Imagem::Imagem(int l, int a) {
    alocar(l, a);
}

Imagem::~Imagem() {
    delete[] matriz;
}

void Imagem::alocar(int l, int a) {
    altura = a;
    largura = l;
    delete[] matriz;
    matriz = new Pixel[a * l];
}

Pixel& Imagem::obterPixel(int x, int y) {
    return matriz[x + y * largura];
}

const Pixel& Imagem::obterPixel(int x, int y) const {
    return matriz[x + y * largura];
}

int Imagem::obterLargura() { return largura; }
int Imagem::obterAltura() { return altura; }

void Imagem::definirPixel(int x, int y, unsigned char R, unsigned char G, unsigned char B) {
    Pixel& pixel = matriz[x + y * largura];
    pixel.r = R;
    pixel.g = G;
    pixel.b = B;
}

Pixel& Imagem::operator()(int x, int y) {
    return obterPixel(x, y);
}

const Pixel& Imagem::operator()(int x, int y) const {
    return obterPixel(x, y);
}

bool Imagem::lerPPM(const string& caminho) {
    ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        cout << "Erro de abertura" << endl;
        return false;
    }

    string identificador;
    int largura, altura, maxVal;
    int r, g, b;

    arquivo >> identificador >> largura >> altura >> maxVal;
    alocar(largura, altura);

    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            arquivo >> r >> g >> b;
            cout << x << y << r << g << b << endl;
            definirPixel(x, y, (uc)r, (uc)g, (uc)b);
        }
    }

    arquivo.close();
    return true;
}

bool Imagem::salvarPPM(const string& caminho) {
    ofstream arquivo(caminho);
    if (!arquivo.is_open()) {
        cout << "Erro de abertura" << endl;
        return false;
    }

    arquivo << "P3" << endl << largura << " " << altura << endl << maxVal << endl;
    for (int y = 0; y < altura; y++) {
        for (int x = 0; x < largura; x++) {
            Pixel& pixel = obterPixel(x, y); 
            arquivo << (int)(pixel.r) << " " << (int)(pixel.g) << " " << (int)(pixel.b) << endl;
        }
        // arquivo << endl;
    }

    arquivo.close();
    return true;
}