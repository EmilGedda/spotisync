#pragma once

#include "spotisync.grpc.pb.h"
#include "spotifyupdate.hpp"

using namespace spotisync;

class Spotify {

private:
  std::string csrf;

public:
  void play(SpotifyUpdate track); 
  void connect(); 
  Update wait_for_update(); 

};
