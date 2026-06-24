// sombreamento.h
#ifndef SOMBREAMENTO_H
#define SOMBREAMENTO_H

#include "terreno.h"
#include "imagem.h"

void sombreamentoVizinhoTopLeft(Terreno &terreno, Imagem &imagem, float fator);
void sombreamentoVizinhos(Terreno &terreno, Imagem &imagem, float fator);
void sombreamentoGradiente(Terreno &terreno, Imagem &imagem, float escala);

#endif
