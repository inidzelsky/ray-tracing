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

// Scene readers
#include "sceneReader.hpp"
#include "objReader.hpp"

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
    // Read the scene
    SceneReader *sceneReader;
    sceneReader = new ObjReader();
    vector<Triangle> triangles = sceneReader->readScene("objects/cube.obj");
    
    // Set final image info
    ImageInfo imageInfo(1080, 720);

    // Define camera and screen position
    Vector camera_pos(0, 0, 10);
    Vector direction (0, 0, -1);
    Vector screen_pos = camera_pos - direction;

    // Define pixels buffer
    vector<bool> renderedPixels;

    // Render the scene
    render(imageInfo, camera_pos, screen_pos, triangles, renderedPixels);

    // Write pixels with the writer implementation
    ImageWriter *imageWriter;
    imageWriter = new PpmImageWriter();

    imageWriter->write(imageInfo, renderedPixels, "out.ppm");
}
