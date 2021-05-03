#pragma once

#include "intersectionAlgorithm.hpp"
#include "vector.hpp"
#include "triangle.hpp"

class MollerTrumboreAlgorithm : public IntersectionAlgorithm {
    bool checkIntersection(Vector origin, Vector distination, Triangle triangle);
};