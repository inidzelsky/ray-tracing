#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class Vector {
public:
    double x = 0;
    double y = 0;
    double z = 0;

    Vector() {}

    Vector(double c) {
        x = y = z = c;
    }

    Vector(double x, double y, double z): x(x), y(y), z(z) {}

    Vector normalize() {
        double length = sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
        return Vector(x / length, y / length, z / length);
    }
};

class Triangle{
public:
    Vector a;
    Vector b;
    Vector c;

    Triangle(Vector a, Vector b, Vector c): a(a), b(b), c(c) {}
};

Vector vector_cross_product(Vector a, Vector b) {
    double x = a.y * b.z - a.z * b.y;
    double y = a.z * b.x - a.x * b.z;
    double z = a.x * b.y - a.y * b.x;

    return Vector(x, y, z);
}

double vector_dot_product(Vector a, Vector b) {
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

Vector vector_subtract(Vector a, Vector b) {
    return Vector(a.x - b.x, a.y - b.y, a.z - b.z);
}

double moller_triangle_intersect(Vector origin, Vector destination, Vector t1, Vector t2, Vector t3) {
    Vector t1t2 = vector_subtract(t1, t2);
    Vector t1t3 = vector_subtract(t1, t3);
    Vector p_vec = vector_cross_product(destination, t1t3);
    double det = vector_dot_product(t1t2, p_vec);

    if (det < 0.00001) return 0;

    float inv_det = 1 / det;
    Vector t_vec = vector_subtract(origin, t1);
    double u = vector_dot_product(t_vec, p_vec) * inv_det;

    if (u < 0 || u > 1) return 0;

    Vector q_vec = vector_cross_product(t_vec, t1t2);
    double v = vector_dot_product(destination, q_vec) * inv_det;

    if (v < 0 || u + v > 1) return 0;

    double t = vector_dot_product(t1t3, q_vec) * inv_det;
    return t;
}

void render(int width, int height, Vector camera_pos, Triangle triangles[], vector<int> &rendered_pixels) {
   double image_ratio = width / (double)height;
   double scale = tan(90 * M_PI / 360);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double pos_x = (2 * (j + 0.5) / (double)width - 1) * image_ratio * scale;
            double pos_y = (1 - 2 * (i + 0.5) / (double)height) * scale;

            Vector direction = Vector(pos_x, pos_y, -1).normalize();

            for (int o = 0; o < 11; o++) {
                Triangle triangle = triangles[o];
                double t = moller_triangle_intersect(camera_pos, direction, triangle.a, triangle.b, triangle.c);
                rendered_pixels.push_back(t ? 1 : 0);
            }
        }
    }
}

int main() {
    // Figure definition
    Triangle triangles[] = {
            Triangle(Vector(-0.5, -0.5, 0.5), Vector(0.5, -0.5, 0.5), Vector(-0.5, 0.5, 0.5)),
            Triangle(Vector(-0.5, 0.5, 0.5), Vector(0.5, -0.5, 0.5), Vector(0.5, 0.5, 0.5)),
            Triangle(Vector(-0.5, 0.5, 0.5), Vector(0.5, 0.5, 0.5), Vector(-0.5, 0.5, -0.5)),
            Triangle(Vector(-0.5, 0.5, -0.5), Vector(0.5, 0.5, 0.5), Vector(0.5, 0.5, -0.5)),
            Triangle(Vector(-0.5, 0.5, -0.5), Vector(0.5, 0.5, -0.5), Vector(-0.5, -0.5, -0.5)),
            Triangle(Vector(-0.5, -0.5, -0.5), Vector(0.5, 0.5, -0.5), Vector(0.5, -0.5, -0.5)),
            Triangle(Vector(-0.5, -0.5, -0.5), Vector(0.5, -0.5, -0.5), Vector(-0.5, -0.5, 0.5)),
            Triangle(Vector(-0.5, -0.5, 0.5), Vector(0.5, -0.5, -0.5), Vector(0.5, -0.5, 0.5)),
            Triangle(Vector(0.5, -0.5, 0.5), Vector(0.5, -0.5, -0.5), Vector(0.5, 0.5, 0.5)),
            Triangle(Vector(0.5, 0.5, 0.5), Vector(0.5, -0.5, -0.5), Vector(0.5, 0.5, -0.5)),
            Triangle(Vector(-0.5, -0.5, -0.5), Vector(-0.5, -0.5, 0.5), Vector(-0.5, 0.5, -0.5)),
            Triangle(Vector(-0.5, 0.5, -0.5), Vector(-0.5, -0.5, 0.5), Vector(-0.5, 0.5, 0.5))
    };

    // Initial values
    int width = 1080;
    int height = 720;

    // Define camera position
    Vector camera_pos(0, 0, 0);

    // Rendered pixels buffer
    vector<int> rendered_pixels;

    render(width, height, camera_pos, triangles, rendered_pixels);

    ofstream out("out.ppm");
    if (!out) return EXIT_FAILURE;

    out << "P3\n";
    out << "1080 720 255\n";

    for (int i = 0; i < rendered_pixels.size(); i++) {
        int r = rendered_pixels[i] ? 125 : 0;
        int g = r;
        int b = r;

        out << r << " " << g << " " << b << "\n";
    }
}
