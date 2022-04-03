// some standard libraries that are helpful for reading/writing text files
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "Structures.h"
#include "helpstructCGAL.h"
#include <CGAL/convex_hull_3.h>
#include "json.hpp"


using json = nlohmann::json;

/*
  json["CityObjects"]["BuildingRoom"]["type"] = "BuildingRoom";
  json["CityObjects"]["BuildingRoom"]["attributes"] = nlohmann::json({});
  json["CityObjects"]["BuildingRoom"]["parents"] = json::array({"Building"});
  json["CityObjects"]["BuildingRoom"]["geometry"] = json::array();
  json["CityObjects"]["BuildingRoom"]["geometry"][0]["type"] = "Solid";
  json["CityObjects"]["BuildingRoom"]["geometry"][0]["lod"] = "2.2";

  json["CityObjects"]["BuildingRoom"]["geometry"][0]["boundaries"] = json::array({});

  json["vertices"] = json::array({});

 */



int main() {
  std::string file_in = "testduplex.obj"; // Name of the OBJ file

  // where to store final file as cityjson & adding the attributes
  json json;
  json["type"] = "CityJSON";
  json["version"] = "1.1";
  json["transform"] = json::object();
  json["transform"]["scale"] = json::array({1.0, 1.0, 1.0});
  json["transform"]["translate"] = json::array({0.0, 0.0, 0.0});
  json["CityObjects"] = json::object();

  // ## Read OBJ file ##
  std::ifstream stream_in;
  stream_in.open(file_in);
  // ## Vectors to store elements
  std::vector<Point> vertices; // empty point vector to store vertices of the OBJ file
  std::vector<Object> objects; // empty object vector to store the objects of the OBJ file
  std::cout << stream_in.is_open() << std::endl;
  if (stream_in.is_open()) { // read through the obj
    std::string line;
    while (getline(stream_in, line)) {
      std::istringstream iss(line);
      std::string word;
      iss >> word;
      // ## read the objects ##
      if (word == "g") {
        Object obj;
        while (iss >> word) obj.id = word; // add the objects name to use as an ID
        std::vector<Shell> sh; // create an empty vector for the shells
        obj.shells = sh; // add the empty vector
        objects.push_back(obj); // add the objects index
      }


      // ## read the shells ##
      if (word == "usemtl") {
        Shell sh;
        objects.back().shells.push_back(sh); // create the index for the shells
      }

      // ## read the vertices ##
      if (word == "v") {
        std::vector<float> coordinates; //empty vector to store coordinates
        while (iss >> word) coordinates.push_back(std::stof(word)); // stof: converts string to float
        Point p(coordinates[0], coordinates[1], coordinates[2]); // add the values of xyz to the point p
        if (coordinates.size() == 3) vertices.push_back(p); // check if there are 3 values and pushback
      }
      // ## read the faces ##
      if (word == "f") {
        std::vector<unsigned long> v; // empty vector to store faces
        while (iss >> word) v.push_back(std::stoi(word)-1); //stoi converts str to int // we also substract 1 bc obj starts at 1 indexing and C++ structures start at 0 indexing
        Face fc = {v}; //make the index for the faces
        objects.back().shells.back().faces.push_back(fc); // add the index to the objects
      }
    }
  }
  std::vector<Nef_polyhedron> polyhedra; // vector of a nef polyhedra to be stored
  std::vector<std::string> polyid; // vector of strings to store each polyhedra id
  for (Object obj : objects) { // navigate through the objects
    for (Shell sh : obj.shells) { // navigate through the shells
      Polyhedron polyhedron; // make an empty polyhedron variable
      std::vector<Point> verts; // Point vector for the vertices
      for (Face face: sh.faces) { // navigate through the faces
        Face locface; // variable to store the local index for the faces to be correlated with the global index for the faces
        for (auto const &id: face.vertices) { // take the values of each vertex...
          verts.push_back(vertices[id]);
        }
      }
      CGAL::convex_hull_3(verts.begin(), verts.end(), polyhedron); // generate CGAL convex hull
      if (polyhedron.is_closed()) { // checks if polyhedron is close
        Nef_polyhedron nef_polyhedron(polyhedron);
        polyhedra.push_back(nef_polyhedron);
        polyid.push_back(obj.id);
        std::cout << "----Closed Polyhedron" << std::endl;
      }
      else {
        std::cout << "Unclosed polyhedron" << std::endl;
      }
    }
  }
  std::cout<< "done" << std::endl;
  Nef_polyhedron bignef = polyhedra.front();
  for (int i=1; i < polyhedra.size(); i++) {
    bignef += polyhedra[i];
    std::cout << polyid[i] << std::endl;
  }

  // # writing the geometries to a CityJSON file.
  Nef_polyhedron::Volume_const_iterator current_volume;
  bool first = true;
  Shell_explorer se;
  CGAL_forall_volumes(current_volume, bignef) {
    if (first == true) { //Outer Building
      json["CityObjects"]["Building"]["type"] = "Building";
      json["CityObjects"]["Building"]["attributes"] = nlohmann::json({});
      json["CityObjects"]["Building"]["children"] = json::array({"BuildingRoom"});
      se.first = true;
      Nef_polyhedron::Shell_entry_const_iterator current_shell;
      CGAL_forall_shells_of(current_shell, current_volume) {
        Nef_polyhedron::SFace_const_handle sface_in_shell(current_shell);
        bignef.visit_shell_objects(sface_in_shell, se);
      }
      json["CityObjects"]["Building"]["geometry"] = json::array({{"type", "MultiSurface"}, {"lod", "2.2"}, {"Boundaries", se.faces}});
    }
    else{
      se.first = false;
      int counter = 0;
      Nef_polyhedron::Shell_entry_const_iterator current_shell;
      CGAL_forall_shells_of(current_shell, current_volume) {
        counter += 1;
      }
      if (counter == 1) { //Inner BuildingRooms
        CGAL_forall_shells_of(current_shell, current_volume) {
          Nef_polyhedron::SFace_const_handle sface_in_shell(current_shell);
          bignef.visit_shell_objects(sface_in_shell, se);
        }
      }

    }
    first = false;
  }

  std::cout << "done!" << std::endl;
  std::string json_string = json.dump(2);
  std::string outputname = "duplex.city.json";
  std::ofstream out_stream(outputname);
  out_stream << json_string;
  out_stream.close();
  return 0;
}