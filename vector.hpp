#pragma once

class Vector {
public:
    double x;
    double y;
    double z;

    Vector() {};
    Vector(double);
    Vector(double, double, double);

    Vector normalize();
    double len();

    Vector operator * (Vector);
    double operator + (Vector);
    Vector operator - (Vector);
};