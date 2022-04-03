#include <iostream>
#include <fstream>
#include <string>
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
  std::string outputname = "/duplex.json";
  std::ofstream out_stream(OUTPUT_PATH + outputname);
  out_stream << json_string;
  out_stream.close();
}


