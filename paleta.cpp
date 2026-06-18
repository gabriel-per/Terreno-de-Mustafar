#include "paleta.h"

Palette::Palette(std::string file_path) {
    std::ifstream file(file_path);
    std::string text;
    Pixel pixel;

    while(getline (file, text)) {
        pixel.R = std::stoul(text.substr(1, 2), nullptr, 16);
        pixel.G = std::stoul(text.substr(3, 2), nullptr, 16);
        pixel.B = std::stoul(text.substr(5, 2), nullptr, 16);

        _palette.push_back(pixel);
    }

    file.close();
}
