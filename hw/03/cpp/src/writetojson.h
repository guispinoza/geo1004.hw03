#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "json.hpp"

using json = nlohmann::json;

void write_to_json() {
  json json;
  json["type"] = "CityJSON";
  json["version"] = "1.1";
  json["transform"] = json::object();
  json["transform"]["scale"] = json::array({1.0, 1.0, 1.0});
  json["transform"]["translate"] = json::array({0.0, 0.0, 0.0});
  json["CityObjects"] = json::object();

  json["CityObjects"]["Duplex"]["type"] = "Building";
  json["CityObjects"]["Duplex"]["attributes"] = nlohmann::json({});
  json["CityObjects"]["Duplex"]["children"] = json::array({"Duplex-0"});
  json["CityObjects"]["Duplex"]["geometry"] = json::array({});

  json["CityObjects"]["Duplex-0"]["type"] = "BuildingPart";
  json["CityObjects"]["Duplex-0"]["attributes"] = nlohmann::json({});
  json["CityObjects"]["Duplex-0"]["parents"] = json::array({"Duplex"});
  json["CityObjects"]["Duplex-0"]["geometry"] = json::array();
  json["CityObjects"]["Duplex-0"]["geometry"][0]["type"] = "Solid";
  json["CityObjects"]["Duplex-0"]["geometry"][0]["lod"] = "2.2";

  json["CityObjects"]["Duplex-0"]["geometry"][0]["boundaries"] = json::array({});

  json["vertices"] = json::array({});

  std::string json_string = json.dump(2);
  std::string outputname = "/duplex.json";
  std::ofstream out_stream(OUTPUT_PATH + outputname);
  out_stream << json_string;
  out_stream.close();
}


