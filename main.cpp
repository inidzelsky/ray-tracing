#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "imageInfo.hpp"
#include "objreader.hpp"

// Geometry
#include "vector.hpp"
#include "triangle.hpp"

// Intersection algorithms
#include "intersectionAlgorithm.hpp"
#include "mollerTrumboreAlgorithm.hpp"

// Image writers
#include "imageWriter.hpp"
#include "ppmImageWriter.hpp"

using namespace std;

void render(ImageInfo imageInfo, Vector camera_pos, Vector screen_pos, vector<Triangle> triangles, vector<bool> &rendered_pixels) {
    IntersectionAlgorithm *intersectionAlgorithm;
    intersectionAlgorithm = new MollerTrumboreAlgorithm();
    double image_ratio = imageInfo.width / (double)imageInfo.height;
    double fov = 60;
    double scale = tan(fov / 180 * M_PI) * (screen_pos - camera_pos).len();

    for (int i = 0; i < imageInfo.height; i++) {
        for (int j = 0; j < imageInfo.width; j++) {
            double pos_x = (2 * (j + 0.5) / (double)imageInfo.width - 1) * image_ratio * scale;
            double pos_y = (1 - 2 * (i + 0.5) / (double)imageInfo.height) * scale;

            Vector direction = Vector(pos_x, pos_y, screen_pos.z).normalize();
            bool is_intersection = false;

            for (int o = 0; o < triangles.size(); o++) {
                Triangle triangle = triangles[o];
                is_intersection = intersectionAlgorithm->checkIntersection(camera_pos, direction, triangle);
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
        Vector V1 = Vector(m.vertexes[v1].x, m.vertexes[v1].y, m.vertexes[v1].z);
        Vector V2 = Vector(m.vertexes[v2].x, m.vertexes[v2].y, m.vertexes[v2].z);
        Vector V3 = Vector(m.vertexes[v3].x, m.vertexes[v3].y, m.vertexes[v3].z);
        triangles.push_back(Triangle(V1, V2, V3));
    }
    
    ImageInfo imageInfo(1080, 720);

    // Define camera and screen position
    Vector camera_pos(0, 0, 10);
    Vector direction (0, 0, -1);
    Vector screen_pos = camera_pos - direction;

    // Rendered pixels buffer
    vector<bool> renderedPixels;

    render(imageInfo, camera_pos, screen_pos, triangles, renderedPixels);

    ImageWriter *imageWriter;
    imageWriter = new PpmImageWriter();

    imageWriter->write(imageInfo, renderedPixels, "out.ppm");
}
