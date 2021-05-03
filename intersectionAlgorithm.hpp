#pragma once

#include "vector.hpp"
#include "triangle.hpp"

class IntersectionAlgorithm {
public:
    virtual bool checkIntersection(Vector origin, Vector distination, Triangle triangle) = 0;
};