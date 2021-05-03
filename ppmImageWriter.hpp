#pragma once

#include "imageInfo.hpp"
#include "imageWriter.hpp"

#include <vector>
#include <string>

class PpmImageWriter : public ImageWriter {
public:
    void write(const ImageInfo imageInfo, const std::vector<bool> &pixels, const std::string output);
};