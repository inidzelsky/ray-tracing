#pragma once

#include <string>
#include <stdio.h>
#include <vector>

#include "sceneReader.hpp"
#include "triangle.hpp"

class ObjReader : public SceneReader{
public:
 std::vector<Triangle> readScene(const char *filename);

private:
    struct vertex {
        double x;
        double y;
        double z;
    };

    struct face{
        int v1,v2,v3;
    };

    std::vector<vertex> vertexes;
    std::vector<face> faces;
    void readfile(const char* filename);
};


