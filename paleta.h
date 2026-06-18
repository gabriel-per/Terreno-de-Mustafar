#include <vector>
#include <fstream>
#include <string>
#include "pixel.h"

class Palette {
    std::vector<Pixel> _palette = {};

    public:
        Palette() = default;
        Palette(std::string file_path);

        std::vector<Pixel> get_palette() {
            return _palette;
        }

        void set_palette(std::vector<Pixel> new_palette) {
            _palette = new_palette;
        }

        void add_to_palette(Pixel pixel) {
            _palette.push_back(pixel);
        }

        int how_many_colors() {
            return _palette.size();
        }

        Pixel color_at_index(int index) {
            return _palette[index];
        }

};