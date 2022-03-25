// some standard libraries that are helpfull for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Structures.h"
#include "helpstructCGAL.h"



<<<<<<< Updated upstream
int main(int argc, const char * argv[]) {
  std::string file_in = "input.obj";
  std::string file_out_obj = "output.obj";
=======
int main() {
  std::string file_in = "../../data/output2x3_guids.obj";
  std::string file_in_4 = "output4_guids";
  std::string file_out_nef = "output_nef";
>>>>>>> Stashed changes

  // ## Read OBJ file ##
  std::ifstream stream_in;
  stream_in.open(file_in);
  std::vector<Point> vertices;
<<<<<<< Updated upstream
  std::vector<Face> init_faces;

=======
  std::vector<Face> faces;
  std::vector<Shell> shells;
  std::vector<Object> objects;
  std::cout << stream_in.is_open() << std::endl;
>>>>>>> Stashed changes
  if (stream_in.is_open()) {
    std::string line;
    while (getline(stream_in, line)) {
      std::istringstream iss(line);
      std::string word;
      iss >> word;
      std::cout << word << std::endl;
      // ## read the objects ##
      if (word == "g") {
        while (iss >> word) object = Object(word); // stof: converts string to float
        objects.push_back(object);
      }


<<<<<<< Updated upstream
      //read the vertices of the file
      if (word == "v") {
        std::vector<float> coordinates;
        while (iss >> word) coordinates.push_back(std::stof(word)); // stof: converts string to float
        if (coordinates.size() == 3) vertices.emplace_back(coordinates[0], coordinates[1], coordinates[2]);
        else vertices.push_back(Vertex());
=======
      // ## read the shells ##
      if (word == "s") {
        while (iss >> word) float s = std::stof(word)); // stof: converts string to float
        objects.push_back(object);
      }

      // ## read the vertices ##
      if (word == "v") {
        std::vector<float> coordinates;
        while (iss >> word) coordinates.push_back(std::stof(word)); // stof: converts string to float
        Point p(coordinates[0], coordinates[1], coordinates[2]);
        if (coordinates.size() == 3) vertices.push_back(p);
>>>>>>> Stashed changes
      }

      // ## read the faces ##
      if (word == "f") {
        std::vector<int> index;
        while (iss >> word) index.push_back(std::stoi(word)-1); //stoi converts str to int // we also substract 1 bc obj starts at 1 indexing and C++ structures start at 0 indexing
<<<<<<< Updated upstream
        if (index.size() == 4) init_faces.emplace_back(Face{index[0], index[1], index[2], index[3]});
=======
        std::vector<unsigned long> v(index[0], index[1], index[2]);
        if (index.size() == 3) faces.emplace_back(Face(v));
>>>>>>> Stashed changes
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
