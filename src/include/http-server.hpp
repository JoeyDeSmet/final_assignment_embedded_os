#pragma once
#define MBED_CONF_RTOS_PRESENT 1

#include "packet.hpp"
#include "rtos/Mail.h"
#include "rtos/Thread.h"


namespace EmbeddedOS {

  class HTTPServer{

    public:
      HTTPServer(rtos::Mail<Packet, 1>* connection, std::string payload);

    private:
      static void server_loop(void* arg);

    private:

      rtos::Mail<Packet, 1>* m_mail;
      rtos::Thread m_thread;
      std::string payload;



  };
}