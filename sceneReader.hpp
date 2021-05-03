#pragma once

#include <vector>

#include "triangle.hpp"

class SceneReader {
public:
    virtual std::vector<Triangle> readScene(const char* filename) = 0;
};