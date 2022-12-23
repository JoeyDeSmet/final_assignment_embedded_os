#pragma once 

#include "packet.hpp"

#include "rtos.h"
#include "rtos/Mail.h"
#include "rtos/Thread.h"

namespace EmbeddedOS {

  class HTTPClient {

    public:
      HTTPClient(rtos::Mail<Packet, 1>* connection);

    private:
      static void client_loop(void* arg);

    private:
      rtos::Mail<Packet, 1>* m_mail;
      rtos::Thread m_thread;

  };

}
