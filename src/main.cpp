#include <iostream>
#include <atomic>
#include <thread>
#include <string>

#include <grpc++/create_channel.h>
#include <grpc++/security/credentials.h>
#include "client.hpp"

#define IP "localhost:54321"

int main()
{
  Client client(grpc::CreateChannel(IP, grpc::InsecureChannelCredentials())); 
  auto err = 0;//client.connect().error_code();

  if(err == 14) { // TODO: fix
    std::cout << "Server refused connection!\n";
    return 1;
  } else if (err == 4) {
    std::cout << "Unable to connect to server!\n";
    return 1;
  }

  std::cout << "1. Create a room\n"
            << "2. Join a room\n";
  std::string option;
  while (true) {
    std::cout << "Enter option: ";
    if(!(std::cin >> option))
      return 1;
    if (option == "1" || option == "2")
      break;
  }
  std::atomic<bool> stop;
      client.follow(stop);
  std::thread worker([&]() {
    if (option == "1") {
    } else {
    //  client.lead();
    }
  });

  std::string cmd;
  while(!stop && std::cin >> cmd && cmd != "q");
  stop = true;
  worker.join();
  main();
}
