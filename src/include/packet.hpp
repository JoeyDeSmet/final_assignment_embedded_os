#pragma once

#include <string>

namespace EmbeddedOS {

  struct Packet {
    char src_ip[15];
    char dest_ip[15];
    char payload[50];
  };
}