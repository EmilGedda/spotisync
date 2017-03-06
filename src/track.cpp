#include "track.hpp"

#include <json.hpp>
#include <string>

using nlohmann::json;

namespace spotisync { 

void from_json(const json& j, Location& l)
{
  l.og = j["og"].get<std::string>();
}

void from_json(const json& j, Resource& r)
{
  r.name = j["name"].get<std::string>();
  r.uri = j["uri"].get<std::string>();
  r.location = j["location"].get<Location>();
}

void from_json(const json& j, Track& t) {
  t.track_resource = j["track_resource"].get<Resource>();
  t.artist_resource = j["artist_resource"].get<Resource>();
  t.album_resource = j["album_resource"].get<Resource>();
  t.length = j["length"].get<int>();
  t.track_type = j["track_type"].get<std::string>();
}

}
