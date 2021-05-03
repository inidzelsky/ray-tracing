#include "vector.hpp"
#include <math.h>

Vector::Vector(const double c): x(c), y(c), z(c) {};
Vector::Vector(const double x, const double y, const double z): x(x), y(y), z(z) {};

Vector Vector::normalize() {
    double length = this->len();
    return Vector(x / length, y / length, z / length);
}

double Vector::len() {
    return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

Vector Vector::operator * (Vector b) {
    double x = this->y * b.z - this->z * b.y;
    double y = this->z * b.x - this->x * b.z;
    double z = this->x * b.y - this->y * b.x;

    return Vector(x, y, z);
}

double Vector::operator + (Vector b) {
    return this->x * b.x + this->y * b.y + this->z * b.z;
}

Vector Vector::operator - (Vector b) {
    return Vector(this->x - b.x, this->y - b.y, this->z - b.z);
}