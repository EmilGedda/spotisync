#include "spotifyupdate.hpp"
#include "track.hpp"
#include <json.hpp>

using nlohmann::json;

namespace spotisync {

void from_json(const json& j, SpotifyUpdate& u)
{
  u.version = j["version"].get<int>();
  u.client_version = j["client_version"].get<std::string>();
  u.playing = j["playing"].get<bool>();
  u.shuffle = j["shuffle"].get<bool>();
  u.repeat = j["repeat"].get<bool>();
  u.play_enabled = j["play_enabled"].get<bool>();
  u.prev_enabled = j["prev_enabled"].get<bool>();
  u.next_enabled = j["next_enabled"].get<bool>();
  u.track = j["track"].get<Track>();
  u.context = j["context"].get<SpotifyContext>();
  u.playing_position = j["playing_position"].get<double>();
  u.server_time = j["server_time"].get<uint64_t>();
  u.volume = j["volume"].get<double>();
  u.online = j["online"].get<bool>();
  u.open_graph_state = j["open_graph_state"].get<GraphState>();
  u.running = j["running"].get<bool>();
}

void from_json(const json& j, GraphState& g)
{
  g.private_session = j["private_session"].get<bool>();
  g.posting_disabled = j["posting_disabled"].get<bool>();
}

void from_json(const json& j, SpotifyContext& c)
{
  // Not implemented by Spotify yet.
}

}

