#pragma once

#include <vector>
#include <string>

#include "imageInfo.hpp"

class ImageWriter {
public:
    virtual void write(const ImageInfo imageInfo, const std::vector<bool> &pixels, const std::string output) = 0;
};