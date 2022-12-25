#pragma once
#define MBED_CONF_RTOS_PRESENT 1

#include "packet.hpp"
#include "rtos/Mail.h"
#include "rtos/Thread.h"
#include "mbed.h"

namespace EmbeddedOS {

  class HTTPServer{

    public:
      HTTPServer(rtos::Mail<Packet, 1>* connection, rtos::Mail<Packet, 10>* switch_mail, const char* payload, const char* ip);

    private:
      static void server_loop(void* arg);

    private:
      const char* m_ip;
      const char* m_payload;

    private:
      rtos::Thread m_thread;
      rtos::Mail<Packet, 1>* m_mail;
      rtos::Mail<Packet, 10>* m_switch_mail;

  };
}