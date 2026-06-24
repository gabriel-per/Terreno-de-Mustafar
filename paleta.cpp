#include "paleta.h"
#include <iostream>

Paleta::Paleta(std::string file_path) {
    std::ifstream file(file_path);
    std::string text;
    Pixel pixel;

    if (!file.is_open()) {
        std::cout << "Erro de abertura" << std::endl;
        return;
    }

    while(getline (file, text)) {
        pixel.r = std::stoul(text.substr(1, 2), nullptr, 16);
        pixel.g = std::stoul(text.substr(3, 2), nullptr, 16);
        pixel.b = std::stoul(text.substr(5, 2), nullptr, 16);

        _paleta.push_back(pixel);
    }

    file.close();
}
