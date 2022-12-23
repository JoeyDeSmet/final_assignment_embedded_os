#pragma once

#include <string>

namespace EmbeddedOS {

  struct Packet {
    std::string src_ip;
    std::string dest_ip;
    std::string payload;
  };

}