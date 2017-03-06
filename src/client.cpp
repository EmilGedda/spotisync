#include <iostream>
#include <chrono>
#include <atomic>

#include <grpc/grpc.h>
#include <grpc++/channel.h>
#include <grpc++/client_context.h>
#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>

#include "spotisync.grpc.pb.h"
#include "client.hpp"
#include "spotify.hpp"
#include "spotifyupdate.hpp"

namespace spotisync {

using namespace grpc;

Client::Client(std::shared_ptr<Channel> chan)
    : stub(SyncServer::NewStub(chan)), chan(chan) { }

Status Client::connect()
{
  ClientContext ctx;
  auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(5);
  ctx.set_deadline(deadline);
  Heartbeat hb_send;
  Heartbeat hb_recieve;
  return stub->Ping(&ctx, hb_send, &hb_recieve);
}

void Client::follow(std::atomic<bool>& should_stop)
{
  ClientContext ctx;
  auto deadline = std::chrono::system_clock::now() + std::chrono::seconds(1);
  ctx.set_deadline(deadline);
  std::shared_ptr<ClientReaderWriter<Heartbeat, Update>> stream(
        stub->Follow(&ctx));

  Update update;
  Heartbeat heartbeat;

  while (!should_stop) {
    if (stream->Read(&update)) {
//      spotify.play(SpotifyUpdate(update));
      stream->Write(heartbeat);
    } else {
      should_stop = true;
    }
  }
  Status status = stream->Finish();
  if (!status.ok()) {
    std::cerr << "Error, stream returned error: " << status.error_code() << '\n';
  }
}

void Client::lead(std::atomic<bool>& should_stop)
{
}

}
