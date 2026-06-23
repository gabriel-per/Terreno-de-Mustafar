#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"
#include "paleta.h"
#include "pixel.h"

TEST_CASE("Teste de leitura de arquivo para paleta") {
    Palette paleta{"./palette.txt"};
    CHECK(paleta.color_at_index(1).R == 172);
    CHECK(paleta.color_at_index(1).G == 208);
    CHECK(paleta.color_at_index(1).B == 165);
    CHECK(paleta.how_many_colors() == 6);
    Pixel pixel;
    pixel.R = 128;
    pixel.G = 255;
    pixel.B = 0;
    paleta.add_to_palette(pixel);
    CHECK(paleta.color_at_index(6).R == 128);
    CHECK(paleta.how_many_colors() == 7);
}
