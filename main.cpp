#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

#include "imageInfo.hpp"

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

void render(ImageInfo imageInfo, IntersectionAlgorithm *intersectionAlgorithm, Vector cameraPos, Vector screenPos, vector<Triangle> triangles, vector<bool> &renderedRixels) {
    double imageRatio = imageInfo.width / (double)imageInfo.height;
    double fov = 60;
    double scale = tan(fov / 180 * M_PI) * (screenPos - cameraPos).len();

    for (int i = 0; i < imageInfo.height; i++) {
        for (int j = 0; j < imageInfo.width; j++) {
            double posX = (2 * (j + 0.5) / (double)imageInfo.width - 1) * imageRatio * scale;
            double posY = (1 - 2 * (i + 0.5) / (double)imageInfo.height) * scale;

            Vector direction = Vector(posX, posY, screenPos.z).normalize();
            bool isIntersection = false;

            for (int o = 0; o < triangles.size(); o++) {
                Triangle triangle = triangles[o];
                isIntersection = intersectionAlgorithm->checkIntersection(cameraPos, direction, triangle);
                if (isIntersection) break;
            }

            renderedRixels.push_back(isIntersection ? 1 : 0);
        }
    }
}

int main() {
    // Read the scene
    SceneReader *sceneReader;
    sceneReader = new ObjReader();
    vector<Triangle> triangles = sceneReader->readScene("objects/cube.obj");
    
    // Set the image info
    ImageInfo imageInfo(1080, 720);

    // Define camera and screen position
    Vector cameraPos(0, 0, 10);
    Vector direction (0, 0, -1);
    Vector screenPos = cameraPos - direction;

    // Set the intersection algorithm
    IntersectionAlgorithm *intersectionAlgorithm;
    intersectionAlgorithm = new MollerTrumboreAlgorithm();

    // Define pixels buffer
    vector<bool> renderedPixels;

    // Render the scene
    render(imageInfo, intersectionAlgorithm, cameraPos, screenPos, triangles, renderedPixels);

    // Write pixels with the writer implementation
    ImageWriter *imageWriter;
    imageWriter = new PpmImageWriter();
    imageWriter->write(imageInfo, renderedPixels, "out.ppm");
}
