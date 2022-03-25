// some standard libraries that are helpful for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <unordered_map>
#include <algorithm>
#include "Structures.h"
#include "helpstructCGAL.h"
// #include "json.hpp" need to add the json.hpp file


int main(int argc, const char * argv[]) {
  std::string file_in = "output2x3_guids";
  std::string file_in_4 = "output4_guids";
  std::string file_out_nef = "output_nef";

  // ## Read OBJ file ##
  std::ifstream stream_in;
  stream_in.open(file_in);
  // ## Vectors to store elements
  std::vector<Point> vertices;
  std::vector<Face> faces;
  std::vector<Shell> shells;
  std::vector<Object> objects;


  //bool wtf = stream_in.is_open();
  if (stream_in.is_open()) {
    std::string line;
    while (getline(stream_in, line)) {
      std::istringstream iss(line);
      std::string word;
      iss >> word;

      //## read the vertices ##
      if (word == "v") {
        std::vector<float> coordinates;
        while (iss >> word) coordinates.push_back(std::stof(word)); // stof: converts string to float
        if (coordinates.size() == 3) vertices.emplace_back(coordinates[0], coordinates[1], coordinates[2]);
        else vertices.emplace_back();
      }

      // ## read the faces ##
      if (word == "f") {
        std::vector<int> index;
        while (iss >> word) index.push_back(std::stoi(word)-1); //stoi converts str to int // we also substract 1 bc obj starts at 1 indexing and C++ structures start at 0 indexing
        if (index.size() == 3) faces.emplace_back(Face{index[0], index[1], index[2], index[3]});
      }

      // ## read the objects ##
      if (word == "g") {

      }
    }
  }

  // # converting the BIM model to OBJ using IfcConvert;
  // # loading each object in the OBJ file(s) into a CGAL Nef polyhedron;
  // # processing the Nef polyhedra into a single big Nef polyhedron representing the space filled by the building’s floors, walls, windows and so on;
  // # extracting the geometries representing the building’s exterior surface and individual rooms;
  // ## FUNCTION FOR THE SHELLS ##

/*  Nef_polyhedron::Volume_const_iterator current_volume;
  CGAL_forall_volumes(current_volume, big_nef) {
    Nef_polyhedron::Shell_entry_const_iterator current_shell;
    CGAL_forall_shells_of(current_shell, current_volume) {
      Shell_explorer se;
      Nef_polyhedron::SFace_const_handle sface_in_shell(current_shell);
      big_nef.visit_shell_objects(sface_in_shell, se);
      ...
    }
  }*/

  // # writing the geometries to a CityJSON file.
  
  return 0;
}
