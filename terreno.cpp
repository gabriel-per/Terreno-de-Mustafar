#include <iostream>
#include <fstream>
#include "terreno.h"
#include "imagem.h"

using namespace std;

// TODO: 
// - DEFINE THE RANGE OF THE ALTITUDE RANDOM GENERATED INCREMENT
// - SET THE FOUR CORNER POINTS TO INITIALIZE WITH A RANDOM GENERATED NUMBER
// OBS.: THE CURRENT CODE BEHAVIOR IS TO CREATE A RANDOM NUMBER BETWEEN -1 AND 1, AND MULTIPLY IT BY THE ROUGHNESS VALUE. 
// THE ROUGHNESS VALUE STARTS WITH AN ARBITRARY VALUE PASSED AS PARAMETER.

float valorAleatorio() { return ((float)rand() / RAND_MAX - 0.5) * 2.0; }


Terreno::Terreno(int d) {
    dim = d;
    alocar();
}
Terreno::~Terreno() {
    delete[] matriz;
}
void Terreno::gerarMapa(float fatorRugosidade) {
    delete[] matriz;
    matriz = new float[dim*dim];

    int dimMinus = dim-1;

    // matriz[0] = 10;
    // matriz[dimMinus] = 5;
    // matriz[dim*dim-1] = 10;
    // matriz[dimMinus*dim] = 5;

    matriz[0] = valorAleatorio();
    matriz[dimMinus] = valorAleatorio();
    matriz[dim*dim-1] = valorAleatorio();
    matriz[dimMinus*dim] = valorAleatorio();

    int passo = dimMinus/2;
    float rugosidade = fatorRugosidade;
    while (passo >= 1) {
        // cout << passo << endl;

        for (int y=passo; y<dimMinus; y+=passo*2) {
            for (int x=passo; x<dimMinus; x+=passo*2) {
                // cout << x << " " << y << endl;
                float randomOffset = valorAleatorio() * rugosidade;
                mediaDiamante(x, y, passo, randomOffset);
            }
        }

        for (int yi=0; yi<=(dimMinus/passo); yi++) {
            int y = yi*passo;
            for (int x=(yi%2 ? 0 : passo); x<dim; x+=passo*2) {
                // cout << x << " " << y << " " << yi%2 << endl;

                float randomOffset = ((float)rand() / RAND_MAX - 0.5) * 2.0 * rugosidade;
                mediaSquare(x, y, passo, randomOffset);
            }
        }
        passo /= 2;
        rugosidade *= fatorRugosidade;
    }

    
}

float Terreno::obterAltitude(int x, int y) {return matriz[y*dim+x];}
float Terreno::obterAltitude(int i) {return matriz[i];}
int Terreno::obterQuantidadeLinhas() {return dim;}
int Terreno::obterQuantidadeColunas() {return dim;}

void Terreno::mediaDiamante(int x, int y, int passo, float offset) {
    float sum = 0;

    for (int xo=-passo; xo<=passo*2; xo+=passo*2) { // REVIEW CONDITION
        for (int yo=-passo; yo<=passo*2; yo+=passo*2) {
            sum += matriz[(y+yo)*dim+(x+xo)] ;
            // matriz[(y+yo)*dim+(x+xo)] 
        }            
    }

    matriz[(y)*dim+(x)] = sum/4. + offset;
}

void Terreno::mediaSquare(int x, int y, int passo, float offset) {
    float sum, count;
    sum = count = 0;


    for (int xo=-passo; xo<=passo; xo+=passo*2) {
        if (coordenadaValida(x+xo, y)){
            sum += matriz[(y)*dim+(x+xo)];
            count ++;
        }
    }

    for (int yo=-passo; yo<=passo; yo+=passo*2) {
        if (coordenadaValida(x, y+yo)){
            sum += matriz[(y+yo)*dim+x] ;
            count ++;
        }
    }      

    matriz[(y)*dim+(x)] = sum/count + offset;
}

void Terreno::alocar() {
    delete[] matriz;
    matriz = new float[dim*dim];
}

bool Terreno::coordenadaValida(int x, int y) {return x >= 0 and x < dim and y >= 0 and y < dim;}

bool Terreno::salvarArquivo(const string& caminho) {
    ofstream arquivo(caminho);
    if (!arquivo.is_open()) {
        cout << "Erro de abertura" << endl;
        return false;
    }
    arquivo << dim << " ";
    for (int y=0; y<dim; y++) {
        for (int x=0; x<dim; x++) {
            arquivo << matriz[y*dim+x] << " ";
            cout << matriz[y*dim+x] << " ";
        }
        arquivo << endl;
    }

    arquivo.close();
    return true;
}

bool Terreno::lerArquivo(const string& caminho) {
    ifstream arquivo(caminho);
    if (!arquivo.is_open()) {
        cout << "Erro de abertura" << endl;
        return false;
    }
    
    arquivo >> dim;

    cout << dim << endl;
    alocar();

    for (int y=0; y<dim; y++) {
        for (int x=0; x<dim; x++) {
            arquivo >> matriz[y*dim+x];
        }
    }

    arquivo.close();
    return true;
}

Imagem Terreno::obterImagem(Paleta paleta, float fatorSombreamento) {

    float minValor=matriz[0], maxValor=matriz[0], intervalo;
    for (int i=0; i<dim*dim; i++) {
        if (matriz[i] > maxValor) {maxValor = matriz[i];}
        if (matriz[i] < minValor) {minValor = matriz[i];}
    }
    intervalo = maxValor-minValor;

    Imagem imagem{dim, dim};

    int numeroDeCores = paleta.how_many_colors();
    for (int i=0; i<dim*dim; i++) {
        float normal = (matriz[i] - minValor)/(intervalo);
        int indice = normal * numeroDeCores;
        Pixel cor = paleta.color_at_index(min(indice, numeroDeCores-1));
        imagem.definirPixel(i, cor.r, cor.g, cor.b);
        // if (i > dim and matriz[i-dim-1] > matriz[i]) {
        //     imagem.definirPixel(i, cor.r*fatorSombreamento, cor.g*fatorSombreamento, cor.b*fatorSombreamento);
        // if (i > dim and matriz[i-dim-1] > matriz[i]) {
        //     imagem.definirPixel(i, cor.r*fatorSombreamento, cor.g*fatorSombreamento, cor.b*fatorSombreamento);
        // } else {
        //     imagem.definirPixel(i, cor.r, cor.g, cor.b);
        // }
    }

    return imagem;
}