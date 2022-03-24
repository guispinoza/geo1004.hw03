// some standard libraries that are helpfull for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Structures.h"
#include "helpstructCGAL.h"



int main(int argc, const char * argv[]) {
  std::string file_in = "input.obj";
  std::string file_out_obj = "output.obj";

  // ## Read OBJ file ##
  std::ifstream stream_in;
  stream_in.open(file_in);
  std::vector<Point> vertices;
  std::vector<Face> init_faces;

  if (stream_in.is_open()) {
    std::string line;
    while (getline(stream_in, line)) {
      std::istringstream iss(line);
      std::string word;
      iss >> word;

      //read the vertices of the file
      if (word == "v") {
        std::vector<float> coordinates;
        while (iss >> word) coordinates.push_back(std::stof(word)); // stof: converts string to float
        if (coordinates.size() == 3) vertices.emplace_back(coordinates[0], coordinates[1], coordinates[2]);
        else vertices.push_back(Vertex());
      }

      // ## read the faces ##
      if (word == "f") {
        std::vector<int> index;
        while (iss >> word) index.push_back(std::stoi(word)-1); //stoi converts str to int // we also substract 1 bc obj starts at 1 indexing and C++ structures start at 0 indexing
        if (index.size() == 4) init_faces.emplace_back(Face{index[0], index[1], index[2], index[3]});
      }
    }
  }

  // # converting the BIM model to OBJ using IfcConvert;
  // # loading each object in the OBJ file(s) into a CGAL Nef polyhedron;
  // # processing the Nef polyhedra into a single big Nef polyhedron representing the space filled by the building’s floors, walls, windows and so on;
  // # extracting the geometries representing the building’s exterior surface and individual rooms;
  // # writing the geometries to a CityJSON file.
  
  return 0;
}
