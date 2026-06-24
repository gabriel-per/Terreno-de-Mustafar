#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../terreno.h"

TEST_CASE("Testa geracao de imagem a partir de arquivo de altitudes e paleta") {
    // Ler o mapa de altitudes do arquivo (9x9 com valores 0-30)
    Terreno terreno{9};
    bool lido = terreno.lerArquivo("data/terrenos/test_terrain.txt");
    CHECK(lido == true);
    CHECK(terreno.obterQuantidadeLinhas() == 9);
    CHECK(terreno.obterQuantidadeColunas() == 9);
    
    // Criar paleta a partir do arquivo (3 cores: azul, verde, vermelho)
    Paleta paleta{"data/paletas/test_palette.txt"};
    CHECK(paleta.how_many_colors() == 3);
    
    // Gerar imagem sem sombreamento (fator = 1.0)
    Imagem imagem = terreno.obterImagem(paleta, 1.0f);
    CHECK(imagem.obterLargura() == 9);
    CHECK(imagem.obterAltura() == 9);
    
    // Verificar que pixels com altitude 0 tem cor azul (primeira cor da paleta)
    Pixel corMin = imagem.obterPixel(0, 0); // altitude 0
    CHECK(corMin.r == doctest::Approx(0).epsilon(5));
    CHECK(corMin.g == doctest::Approx(0).epsilon(5));
    CHECK(corMin.b == doctest::Approx(255).epsilon(5));
    
    // Verificar que pixels com altitude 30 tem cor vermelha (ultima cor da paleta)
    Pixel corMax = imagem.obterPixel(6, 0); // altitude 30
    CHECK(corMax.r == doctest::Approx(255).epsilon(5));
    CHECK(corMax.g == doctest::Approx(0).epsilon(5));
    CHECK(corMax.b == doctest::Approx(0).epsilon(5));
    
    // Salvar resultado
    imagem.salvarPPM("data/imagens/test_saida.ppm");
}

TEST_CASE("Testa valores de altitude no arquivo de teste") {
    Terreno terreno{9};
    terreno.lerArquivo("data/terrenos/test_terrain.txt");
    
    // Verificar alguns valores especificos
    CHECK(terreno.obterAltitude(0, 0) == doctest::Approx(0).epsilon(0.01));
    CHECK(terreno.obterAltitude(6, 0) == doctest::Approx(30).epsilon(0.01));
    CHECK(terreno.obterAltitude(4, 2) == doctest::Approx(30).epsilon(0.01));
}
