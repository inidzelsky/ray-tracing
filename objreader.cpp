#include <string>
#include "objreader.hpp"
#include <fstream>
#include <string>
#include <iostream>
#include <vector>

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
           faces.push_back(f);
       }
   }
}
