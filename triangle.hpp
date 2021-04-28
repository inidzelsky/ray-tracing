#pragma once
#include "vector.hpp"

class Triangle {
public:
    Vector a;
    Vector b;
    Vector c;

    Triangle(Vector a, Vector b, Vector c): a(a), b(b), c(c) {}
};