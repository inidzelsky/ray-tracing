#include "mollerTrumboreAlgorithm.hpp"

bool MollerTrumboreAlgorithm::checkIntersection(Vector origin, Vector distination, Triangle triangle) {
    const float EPSILON = 0.0000001;
    Vector vertex0 = triangle.a;
    Vector vertex1 = triangle.b;
    Vector vertex2 = triangle.c;
    Vector edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = distination * edge2;
    a = edge1 + h;

    if (a > -EPSILON && a < EPSILON)
        return false;

    f = 1.0 / a;
    s = origin - vertex0;
    u = f * (s + h);

    if (u < 0.0 || u > 1.0)
        return false;

    q = s * edge1;
    v = f * (distination + q);

    if (v < 0.0 || u + v > 1.0)
        return false;
        
    float t = f * (edge2 + q);
    return true;
};