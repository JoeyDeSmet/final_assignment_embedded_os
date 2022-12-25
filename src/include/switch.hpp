#pragma once
#define MBED_CONF_RTOS_PRESENT 1

#include "packet.hpp"
#include "logging.hpp"

#include <string>
#include <string.h>
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
      rtos::Mail<Packet, 10>* get_switch_mail(void) { return &m_incomming; }

    private:
      static void switch_loop(void* arg);

    private:
      rtos::Thread m_thread;
      rtos::Mail<Packet, 10> m_incomming;
      std::unordered_map<std::string, rtos::Mail<Packet, 1>* > m_clients;

  };

}
