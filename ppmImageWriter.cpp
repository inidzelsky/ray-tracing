#include "ppmImageWriter.hpp"

#include <iostream>
#include <fstream>
#include <vector>
#include <string>

void PpmImageWriter::write(const ImageInfo imageInfo, const std::vector<bool> &pixels, const std::string output) {
    std::ofstream out(output);
    // if (!out) return EXIT_FAILURE;

    // Write PPM header
    out << "P3\n";

    // Write image info
    out << imageInfo.width << " " << imageInfo.height << " 255\n";

    // Write pixels
    for (int i = 0; i < pixels.size(); i++) {
        unsigned int r = pixels[i] ? 255 : 0;
        unsigned int g = 0;
        unsigned int b = 0;

        out << r << " " << g << " " << b << " \n";
    }
};