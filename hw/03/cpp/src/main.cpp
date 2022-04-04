/*
+------------------------------------------------------------------------------+
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|  _____________ ______  ___  ____   ___  ___  ___  ___    __         ___  ___ |
| / ___/ __/ __ <  / _ \/ _ \/ / /  |_  |/ _ \|_  ||_  |  / / _    __/ _ \\__ ||
|/ (_ / _// /_/ / / // / // /_  _/ / __// // / __// __/_ / _ \ |/|/ / // /|__ ||
|\___/___/\____/_/\___/\___/ /_/(_)____/\___/____/____(_)_//_/__,__/\___/ /__ /|
|                                                                              |
|                                                                              |
|                                    __________                                |
|                                   ///////////\                               |
|                                  ///////////  \                              |
|                                  |    _    |  |                              |
|                                  |[] | | []|[]|                              |
|                                  |   | |   |  |                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
|                                                                              |
+------------------------------------------------------------------------------+
+------------------------------------------------------------------------------+
|                                                                              |
|                             Eleni Theodoridou (5626544)                      |
|                          Guilherme Spinoza Andreo (5383994)                  |
|                               Fabian Visser (5433916)                        |
|                                                                              |
+------------------------------------------------------------------------------+
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "Structures.h"
#include "helpstructCGAL.h"
#include <CGAL/convex_hull_3.h>
#include "json.hpp"
<<<<<<< Updated upstream


using json = nlohmann::json;

void write_to_json() {
  json json;
  json["type"] = "CityJSON";
  json["version"] = "1.1";
  json["transform"] = json::object();
  json["transform"]["scale"] = json::array({1.0, 1.0, 1.0});
  json["transform"]["translate"] = json::array({0.0, 0.0, 0.0});
  json["CityObjects"] = json::object();

  json["CityObjects"]["Building"]["type"] = "Building";
  json["CityObjects"]["Building"]["attributes"] = nlohmann::json({});
  json["CityObjects"]["Building"]["children"] = json::array({"BuildingRoom"});
  json["CityObjects"]["Building"]["geometry"] = json::array({});

  json["CityObjects"]["BuildingRoom"]["type"] = "BuildingRoom";
  json["CityObjects"]["BuildingRoom"]["attributes"] = nlohmann::json({});
  json["CityObjects"]["BuildingRoom"]["parents"] = json::array({"Building"});
  json["CityObjects"]["BuildingRoom"]["geometry"] = json::array();
  json["CityObjects"]["BuildingRoom"]["geometry"][0]["type"] = "Solid";
  json["CityObjects"]["BuildingRoom"]["geometry"][0]["lod"] = "2.2";

  json["CityObjects"]["BuildingRoom"]["geometry"][0]["boundaries"] = json::array({});

  json["vertices"] = json::array({});

  std::string json_string = json.dump(2);
  std::string outputname = "/duplex.city.json";
  std::ofstream out_stream(OUTPUT_PATH + outputname);
  out_stream << json_string;
  out_stream.close();
}

int main() {
  std::string file_in = "testduplex.obj";
  std::string file_in_4 = "output4_guids";
  std::string file_out_nef = "output_nef";
=======
using json = nlohmann::json;

int main() {
    // where to store final file as cityjson & adding the attributes
    json json;
    json["type"] = "CityJSON";
    json["version"] = "1.1";
    json["transform"] = json::object();
    json["transform"]["scale"] = json::array({1.0, 1.0, 1.0});
    json["transform"]["translate"] = json::array({0.0, 0.0, 0.0});
    json["CityObjects"] = json::object();

    std::string file_in = "KIThouse.obj";
    std::string file_out = "output.city.json";

    // ## Read OBJ file ##
    std::ifstream stream_in;
    stream_in.open(file_in);
    // ## Vectors to store elements
    std::vector<Point> vertices;
    std::vector<Object> objects;
    std::cout << stream_in.is_open() << std::endl;
    if (stream_in.is_open()) {
        std::string line;
        while (getline(stream_in, line)) {
            std::istringstream iss(line);
            std::string word;
            iss >> word;
            // ## read the objects ##
            if (word == "g") {
                Object obj;
                while (iss >> word) obj.id = word; // stof: converts string to float
                std::vector<Shell> sh;
                obj.shells = sh;
                objects.push_back(obj);
            }
>>>>>>> Stashed changes


            // ## read the shells ##
            if (word == "usemtl") {
                Shell sh;
                objects.back().shells.push_back(sh);
            }

<<<<<<< Updated upstream
      // ## read the shells ##
      if (word == "usemtl") {
        Shell sh;
        objects.back().shells.push_back(sh);
      }

      // ## read the vertices ##
      if (word == "v") {
        std::vector<float> coordinates;
        while (iss >> word) coordinates.push_back(std::stof(word)); // stof: converts string to float
        Point p(coordinates[0], coordinates[1], coordinates[2]);
        // for (Point ver: vertices) {
        //   if (ver.x() == coordinates[0] && ver.y() == coordinates[1] && ver.z() == coordinates[2]) {
        //     std::cout << ver << std::endl;
        //   }
        // }
        if (coordinates.size() == 3) vertices.push_back(p);
      }
      // ## read the faces ##
      if (word == "f") {
        std::vector<unsigned long> v;
        while (iss >> word) v.push_back(std::stoi(word)-1); //stoi converts str to int // we also substract 1 bc obj starts at 1 indexing and C++ structures start at 0 indexing
        Face fc = {v};
        objects.back().shells.back().faces.push_back(fc);
      }
    }
  }
  std::vector<Nef_polyhedron> polyhedra;
  std::vector<std::string> polyid;
  for (Object obj : objects) {
    for (Shell sh : obj.shells) {
      Polyhedron polyhedron;
      std::vector<Point> verts;
      for (Face face: sh.faces) {
        Face locface;
        for (auto const &id: face.vertices) {
          verts.push_back(vertices[id]);
        }
      }
      CGAL::convex_hull_3(verts.begin(), verts.end(), polyhedron);
      if (polyhedron.is_closed()) {
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
  std::cout << "polyhedra time" << std::endl;
  Polyhedron P;
  std::ofstream out("bignef.off");
  bignef.convert_to_polyhedron(P);
  out << P;

  // # writing the geometries to a CityJSON file.
  Nef_polyhedron::Volume_const_iterator current_volume;
  bool first = true;
  Shell_explorer se;
  CGAL_forall_volumes(current_volume, bignef) {
    if (first == true) { //Outer Building
      se.first = true;
      Nef_polyhedron::Shell_entry_const_iterator current_shell;
      CGAL_forall_shells_of(current_shell, current_volume) {
        Nef_polyhedron::SFace_const_handle sface_in_shell(current_shell);
        bignef.visit_shell_objects(sface_in_shell, se);
      }
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
      first = false;
    }
  }

  std::cout << "done!" << std::endl;
  return 0;
}
=======
            // ## read the vertices ##
            if (word == "v") {
                std::vector<float> coordinates;
                while (iss >> word) coordinates.push_back(std::stof(word)); // stof: converts string to float
                Point p(coordinates[0], coordinates[1], coordinates[2]);
                // for (Point ver: vertices) {
                //   if (ver.x() == coordinates[0] && ver.y() == coordinates[1] && ver.z() == coordinates[2]) {
                //     std::cout << ver << std::endl;
                //   }
                // }
                if (coordinates.size() == 3) vertices.push_back(p);
            }
            // ## read the faces ##
            if (word == "f") {
                std::vector<unsigned long> v;
                while (iss >> word) v.push_back(std::stoi(word)-1); //stoi converts str to int // we also substract 1 bc obj starts at 1 indexing and C++ structures start at 0 indexing
                Face fc = {v};
                objects.back().shells.back().faces.push_back(fc);
            }
        }
    }

    std::vector<Nef_polyhedron> polyhedra;
    std::vector<std::string> polyid;
    for (Object obj : objects) {
        for (Shell sh : obj.shells) {
            Polyhedron polyhedron;
            std::vector<Point> verts; // create a polyhedron and a vector to store its vertices, to feed it to the convex hull function
            for (Face face: sh.faces) {
                for (auto const &id: face.vertices) {
                    verts.push_back(vertices[id]);
                }
            }
            CGAL::convex_hull_3(verts.begin(), verts.end(), polyhedron); //to create the convex hull for each shell
            if (polyhedron.is_closed()) { //nef polyhedra are only created by closed polyhedra
                Nef_polyhedron nef_polyhedron(polyhedron);
                polyhedra.push_back(nef_polyhedron);
                polyid.push_back(obj.id);
            }
            else {
                std::cout << "Unclosed polyhedron" << std::endl;
            }
        }
    }

    Nef_polyhedron bignef = polyhedra.front(); //initiallize the big nef polyhedron with the first polyhedron
    for (int i=1; i < polyhedra.size(); i++) {
        bignef += polyhedra[i]; //using union to combine all the shell polyhedra, outer and inner
    }

// # writing the geometries to a CityJSON file.
    Nef_polyhedron::Volume_const_iterator current_volume;
    bool first = true;
    Shell_explorer se;
    int roomcounter = 0;
    std::vector<std::string> children;
    CGAL_forall_volumes(current_volume, bignef) {
        se.faces.clear(); //clearing the face for each volume, to get the individual rooms
        if (first == true) { //Outer Building
            json["CityObjects"]["Building"]["type"] = "Building";
            json["CityObjects"]["Building"]["attributes"] = nlohmann::json({});
            //json["CityObjects"]["Building"]["children"] = json::array({"BuildingRoom"});
            se.first = true; //we set it to first, to be to the outer shell
            Nef_polyhedron::Shell_entry_const_iterator current_shell;
            CGAL_forall_shells_of(current_shell, current_volume) { //shell exploration
                Nef_polyhedron::SFace_const_handle sface_in_shell(current_shell);
                bignef.visit_shell_objects(sface_in_shell, se);
            }
            json["CityObjects"]["Building"]["geometry"][0] = {{"type", "MultiSurface"}, {"lod", "2.2"}, {"boundaries", se.faces}};
            json["CityObjects"]["Building"]["geometry"][0]["semantics"] = {{"surfaces", json::array()},{"values", json::array()}};
            json["CityObjects"]["Building"]["geometry"][0]["semantics"]["surfaces"] = json::array({{{"type", "RoofSurface"}},{{"type", "WallSurface"}},{{"type", "FloorSurface"}}});
            json["CityObjects"]["Building"]["geometry"][0]["semantics"]["values"] = se.surfsem; //adding the semantics of the outer surface
        }
        else{
            se.first = false; //set it to false, we are in the inner shells
            int counter = 0;
            Nef_polyhedron::Shell_entry_const_iterator current_shell;
            CGAL_forall_shells_of(current_shell, current_volume) {
                counter += 1;
            }
            if (counter == 1) { //Inner BuildingRooms
                if (roomcounter != 4) { //room 4 is the space between the roof and the floors, so it can be excluded
                    std::string br = "BuildingRoom" + std::to_string(roomcounter);
                    children.push_back(br);
                    roomcounter++;
                    json["CityObjects"][br]["type"] = "BuildingRoom";
                    json["CityObjects"][br]["attributes"] = nlohmann::json({});
                    json["CityObjects"][br]["parents"] = {"Building"};
                    CGAL_forall_shells_of(current_shell, current_volume) {
                        Nef_polyhedron::SFace_const_handle sface_in_shell(current_shell);
                        bignef.visit_shell_objects(sface_in_shell, se);
                        json["CityObjects"][br]["geometry"][0] = {{"type", "MultiSurface"}, {"lod", "2.2"}, {"boundaries", se.faces}};
                    }
                }
            }
        }
        first = false; //We have done the exterior shell, we can now continue to the interior shells
    }

    //writing the vertices
    std::vector<std::vector<double>> dverts;
    for (Point v : se.vertices) {
        std::vector<double> dv = {CGAL::to_double(v.x()), CGAL::to_double(v.y()), CGAL::to_double(v.z())};
        dverts.push_back(dv);
    }
    json["CityObjects"]["Building"]["children"] = children; //Link BuildingRooms to Building
    json["vertices"] = dverts;
    std::string json_string = json.dump(2);
    std::ofstream out_stream(file_out);
    out_stream << json_string;
    out_stream.close();

    std::cout << "done!" << std::endl;
    return 0;
}
>>>>>>> Stashed changes
