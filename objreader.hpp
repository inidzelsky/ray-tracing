#pragma once
#include <string>
#include <stdio.h>
#include <vector>

class ObjReader {
    struct vertex {
        double x;
        double y;
        double z;
    };
    struct face{
        int v1,v2,v3;
    };
public:
    std::vector<vertex> vetexes;
    std::vector<face> faces;
    void readfile(const char* filename);
};


