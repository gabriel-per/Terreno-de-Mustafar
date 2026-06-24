#include "terreno.h"
#include "imagem.h"
#include <cmath>
#include "sombreamento.h"

// void sombreamentoVizinhos(Terreno &terreno, Imagem &imagem, float fator) {

// }

void sombreamentoVizinhoTopLeft(Terreno &terreno, Imagem &imagem, float fator) {
    int dim = terreno.obterQuantidadeColunas();
    for (int i=0; i <dim*dim; i++) {
        Pixel cor = imagem.obterPixel(i);
        if (i > dim) {
            // float topLeftAltitude = ;
            // float altitude = ;
            if (terreno.obterAltitude(i-dim-1) > terreno.obterAltitude(i)) {
                imagem.definirPixel(i, cor.r*fator, cor.g*fator, cor.b*fator);
                continue;
            }
        } else {
            imagem.definirPixel(i, cor.r, cor.g, cor.b);
        }
    }
}

void sombreamentoVizinhos(Terreno &terreno, Imagem &imagem, float fator) {
    int dim = terreno.obterQuantidadeColunas();

    for (int y=0; y<dim; y++) {
        for (int x=0; x<dim; x++) {
            int dx[] = {-1, 1, 0, 0};
            int dy[] = {0, 0, -1, 1};
            bool allTaller = true;
            
            float altitude = terreno.obterAltitude(x, y);

            for (int d = 0; d < 4; d++) {
                int nx = x + dx[d], ny = y + dy[d];
                if (nx >= 0 && nx < dim && ny >= 0 && ny < dim) {
                    if (terreno.obterAltitude(nx, ny) <= altitude) {
                        allTaller = false;
                        break;
                    }
                }
            }
            if (allTaller) { 
                Pixel cor = imagem.obterPixel(x, y);
                imagem.definirPixel(x, y, cor.r*fator, cor.g*fator, cor.b*fator);

            }
        }
    }
}

void sombreamentoGradiente(Terreno &terreno, Imagem &imagem, float escala) {
    int dim = terreno.obterQuantidadeColunas();
    
    // Light direction: from top-left, coming DOWN (positive vertical component)
    float lightX = -1.0, lightY = 1.0, lightZ = -1.0;
    float len = sqrt(lightX*lightX + lightY*lightY + lightZ*lightZ);
    lightX /= len; lightY /= len; lightZ /= len;

    // Scale factor to amplify small height differences
    for (int y = 1; y < dim - 1; y++) {
        for (int x = 1; x < dim - 1; x++) {
            float hL = terreno.obterAltitude(x - 1, y);
            float hR = terreno.obterAltitude(x + 1, y);
            float hU = terreno.obterAltitude(x, y - 1);
            float hD = terreno.obterAltitude(x, y + 1);
            
            // Surface normal: scale the gradient to match vertical component
            float normalX = (hL - hR) * escala;
            float normalZ = (hU - hD) * escala;
            float normalY = 1.0;  // vertical (up) component
            
            float nLen = sqrt(normalX*normalX + normalY*normalY + normalZ*normalZ);
            normalX /= nLen; normalY /= nLen; normalZ /= nLen;
            
            // Diffuse lighting (dot product)
            float brightness = normalX * lightX + normalY * lightY + normalZ * lightZ;
            brightness = fmax(0.0, brightness);
            brightness = 0.3 + 0.7 * brightness; // ambient + diffuse
            
            Pixel cor = imagem.obterPixel(x, y);
            imagem.definirPixel(x, y, cor.r * brightness, cor.g * brightness, cor.b * brightness);
        }
    }
}