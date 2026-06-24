#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "../doctest.h"
#include "../paleta.h"
#include "../pixel.h"

TEST_CASE("Teste de leitura de arquivo para paleta") {
    Paleta paleta{"./palette.txt"};
    CHECK(paleta.color_at_index(1).r == 172);
    CHECK(paleta.color_at_index(1).g == 208);
    CHECK(paleta.color_at_index(1).b == 165);
    CHECK(paleta.how_many_colors() == 6);
    Pixel pixel;
    pixel.r = 128;
    pixel.g = 255;
    pixel.b = 0;
    paleta.add_to_palette(pixel);
    CHECK(paleta.color_at_index(6).r == 128);
    CHECK(paleta.how_many_colors() == 7);
}
