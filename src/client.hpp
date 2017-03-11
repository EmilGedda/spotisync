#pragma once

#include <atomic>
#include <grpc/grpc.h>
#include <grpc++/channel.h>

#include "spotisync.grpc.pb.h"
#include "spotify.hpp"

using namespace grpc;

namespace spotisync {

class Client {

  std::unique_ptr<SyncServer::Stub> stub;
  std::shared_ptr<Channel> chan;
  Spotify spotify;

public:
  explicit Client(std::shared_ptr<Channel> chan);

  Status connect();

  void follow(std::atomic<bool>& should_stop);
  void lead(std::atomic<bool>& should_stop);

};

}
