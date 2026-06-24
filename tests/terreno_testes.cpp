#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../terreno.h"

TEST_CASE("Testa se o mapa salvo em arquivo corresponde ao gerado") {
    Terreno terrain(5);
    terrain.gerarMapa(0);
    terrain.salvarArquivo("data/terrenoteste");

    Terreno terrain1(5);
    terrain1.lerArquivo("data/terrenoteste");

    // Verifica se as dimensões são iguais
    CHECK(terrain1.obterQuantidadeLinhas() == terrain.obterQuantidadeLinhas());
    CHECK(terrain1.obterQuantidadeColunas() == terrain.obterQuantidadeColunas());

    // Verifica se cada altitude corresponde (com tolerância para precisão de float)
    for (int y = 0; y < terrain.obterQuantidadeLinhas(); y++) {
        for (int x = 0; x < terrain.obterQuantidadeColunas(); x++) {
            CHECK(terrain1.obterAltitude(x, y) == doctest::Approx(terrain.obterAltitude(x, y)).epsilon(0.01));
        }
    }
}

TEST_CASE("Testa se o mapa gerado tem dimensões corretas") {
    Terreno terrain(9);
    terrain.gerarMapa(0.5);

    CHECK(terrain.obterQuantidadeLinhas() == 9);
    CHECK(terrain.obterQuantidadeColunas() == 9);
}

TEST_CASE("Testa se as altitudes estão dentro do intervalo esperado") {
    Terreno terrain(5);
    terrain.gerarMapa(0.5);

    for (int y = 0; y < terrain.obterQuantidadeLinhas(); y++) {
        for (int x = 0; x < terrain.obterQuantidadeColunas(); x++) {
            float alt = terrain.obterAltitude(x, y);
            CHECK(alt >= -10.0f);
            CHECK(alt <= 10.0f);
        }
    }
}


