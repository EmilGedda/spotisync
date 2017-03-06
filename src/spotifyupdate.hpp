#pragma once
#include <string>
#include <json.hpp>
using nlohmann::json;
#include "track.hpp"

namespace spotisync {

struct GraphState {
  bool private_session;
  bool posting_disabled;
};

struct SpotifyContext { 

};

struct SpotifyUpdate {
  int version;
  std::string client_version;
  bool playing;
  bool shuffle;
  bool repeat;
  bool play_enabled;
  bool prev_enabled;
  bool next_enabled;
  Track track;
  SpotifyContext context;
  double playing_position;
  uint64_t server_time;
  double volume;
  bool online;
  GraphState open_graph_state;
  bool running;
};

void from_json(const json& j, GraphState& u);
void from_json(const json& j, SpotifyContext& u);
void from_json(const json& j, SpotifyUpdate& u);
}
