#pragma once
#define MBED_CONF_RTOS_PRESENT 1
#include "packet.hpp"

#include <string>
#include <unordered_map>

#include "rtos/Mail.h"
#include "rtos/Thread.h"

namespace EmbeddedOS {

  class Switch {

    public:
      Switch (void);

    public:
      void start(void);

    public:
      rtos::Mail<Packet, 1>* connect(const std::string& client_ip);

    private:
      static void switch_loop(void* arg);

    private:
      rtos::Thread m_thread;
      std::unordered_map<std::string, rtos::Mail<Packet, 1>* > m_clients;

  };

}
