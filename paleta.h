#include <vector>
#include <fstream>
#include <string>
#include "pixel.h"

class Paleta {
    std::vector<Pixel> _paleta = {};

    public:
        Paleta() = default;
        Paleta(std::string file_path);

        std::vector<Pixel> get_palette() {
            return _paleta;
        }

        void set_palette(std::vector<Pixel> new_palette) {
            _paleta = new_palette;
        }

        void add_to_palette(Pixel pixel) {
            _paleta.push_back(pixel);
        }

        int how_many_colors() {
            return _paleta.size();
        }

        Pixel color_at_index(int index) {
            return _paleta[index];
        }

};