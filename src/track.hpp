#pragma once
#include <string>
#include <json.hpp>

using nlohmann::json;

namespace spotisync {

struct Location {
  std::string og;
};

struct Resource {
  std::string name;
  std::string uri;
  Location location;
};

struct Track {
  Resource track_resource;
  Resource artist_resource;
  Resource album_resource;

  int length;
  std::string track_type;

};

void from_json(const json& j, Location& l);
void from_json(const json& j, Resource& l);
void from_json(const json& j, Track& l);
}
