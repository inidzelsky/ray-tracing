#include <string>
#include <fstream>
#include <string>
#include <iostream>

#include "objreader.hpp"
#include "triangle.hpp"

void ObjReader::readfile(const char *filename) {
   std::string s;
   std::ifstream fin(filename);
    
   if(!fin) return;
    
   while(fin>>s)
   {
       if (s[0] == 'v' && s.size() == 1){
           vertex v;
           fin>>v.x>>v.y>>v.z;
           this->vertexes.push_back(v);
       }
       if (s[0] == 'f' && s.size() == 1){
           face f;
           std::string s1;
           std::string s2;
           std::string s3;
           fin>>s1>>s2>>s3;
           f.v1 = (int)s1[0]-48;
           f.v2 = (int)s2[0]-48;
           f.v3 = (int)s3[0]-48;
           this->faces.push_back(f);
       }
   }
}

std::vector<Triangle> ObjReader::readScene(const char *filename) {
    // Read the .obj file
    this->readfile(filename);

    // Fill triangles vector
    std::vector<Triangle> triangles;

    for (int i = 0; i < this->faces.size(); i++) {
        int v1 = this->faces[i].v1 - 1;
        int v2 = this->faces[i].v2 - 1;
        int v3 = this->faces[i].v3 - 1;
        Vector V1 = Vector(this->vertexes[v1].x, this->vertexes[v1].y, this->vertexes[v1].z);
        Vector V2 = Vector(this->vertexes[v2].x, this->vertexes[v2].y, this->vertexes[v2].z);
        Vector V3 = Vector(this->vertexes[v3].x, this->vertexes[v3].y, this->vertexes[v3].z);
        triangles.push_back(Triangle(V1, V2, V3));
    }

    return triangles;
}
