#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "vector.hpp"
#include "triangle.hpp"
#include "objreader.hpp"

using namespace std;

bool moller_trumbore_intersect(Vector rayOrigin, Vector rayVector, Triangle inTriangle)
{
    const float EPSILON = 0.0000001;
    Vector vertex0 = inTriangle.a;
    Vector vertex1 = inTriangle.b;
    Vector vertex2 = inTriangle.c;
    Vector edge1, edge2, h, s, q;
    float a, f, u, v;
    edge1 = vertex1 - vertex0;
    edge2 = vertex2 - vertex0;
    h = rayVector * edge2;
    a = edge1 + h;
    if (a > -EPSILON && a < EPSILON)
        return false;    // This ray is parallel to this triangle.
    f = 1.0 / a;
    s = rayOrigin - vertex0;
    u = f * (s + h);
    if (u < 0.0 || u > 1.0)
        return false;
    q = s * edge1;
    v = f * (rayVector + q);
    if (v < 0.0 || u + v > 1.0)
        return false;
    // At this stage we can compute t to find out where the intersection point is on the line.
    float t = f * (edge2 + q);
    return true;
}

void render(int width, int height, Vector camera_pos, Vector screen_pos, vector<Triangle> triangles, vector<int> &rendered_pixels) {
   double image_ratio = width / (double)height;
   double fov = 60;
   double scale = tan(fov / 180 * M_PI) * (screen_pos - camera_pos).len();

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            double pos_x = (2 * (j + 0.5) / (double)width - 1) * image_ratio * scale;
            double pos_y = (1 - 2 * (i + 0.5) / (double)height) * scale;

            Vector direction = Vector(pos_x, pos_y, screen_pos.z).normalize();
            bool is_intersection = false;

            for (int o = 0; o < triangles.size(); o++) {
                Triangle triangle = triangles[o];
                is_intersection = moller_trumbore_intersect(camera_pos, direction, triangle);
                if (is_intersection) break;
            }

            rendered_pixels.push_back(is_intersection ? 1 : 0);
        }
    }
}

int main() {
    // Figure definition
    ObjReader m;
    m.readfile("objects/cube.obj");
    
    vector<Triangle> triangles;
    for (int i = 0; i < m.faces.size(); i++) {
        int v1 = m.faces[i].v1 - 1;
        int v2 = m.faces[i].v2 - 1;
        int v3 = m.faces[i].v3 - 1;
        Vector V1 = Vector(m.vetexes[v1].x, m.vetexes[v1].y, m.vetexes[v1].z);
        Vector V2 = Vector(m.vetexes[v2].x, m.vetexes[v2].y, m.vetexes[v2].z);
        Vector V3 = Vector(m.vetexes[v3].x, m.vetexes[v3].y, m.vetexes[v3].z);
        triangles.push_back(Triangle(V1, V2, V3));
    }
    
    // Initial values
    int width = 1080;
    int height = 720;

    // Define camera and screen position
    Vector camera_pos(0, 0, 10);
    Vector direction (0, 0, -1);
    Vector screen_pos = camera_pos - direction;

    // Rendered pixels buffer
    vector<int> rendered_pixels;

    render(width, height, camera_pos, screen_pos, triangles, rendered_pixels);

    ofstream out("out.ppm");
    if (!out) return EXIT_FAILURE;

    out << "P3\n";
    out << "1080 720 255\n";

    cout << rendered_pixels.size() << endl;

    for (int i = 0; i < rendered_pixels.size(); i++) {
        int r = rendered_pixels[i] ? 255 : 0;
        int g = 0;
        int b = 0;

        out << r << " " << g << " " << b << "\n";
    }
}
