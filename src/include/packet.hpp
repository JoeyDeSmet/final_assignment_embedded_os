#pragma once

#include <string>

namespace EmbeddedOS {

  struct Packet {
    char src_ip[15] = { 0 };
    char dest_ip[15] = { 0 };
    char payload[50] = { 0 };
  };
}