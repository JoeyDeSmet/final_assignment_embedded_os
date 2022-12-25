#pragma once 
#define MBED_CONF_RTOS_PRESENT 1

#include "packet.hpp"

#include "rtos.h"
#include "rtos/Mail.h"
#include "rtos/Thread.h"
#include "mbed.h"
namespace EmbeddedOS {

  class HTTPClient {

    public:
      HTTPClient(rtos::Mail<Packet, 1>* connection);

      rtos::Mail<Packet, 1>* getMail(void);

    private:
      static void client_loop(void* arg);

    private:
      rtos::Mail<Packet, 1>* m_mail;
      rtos::Mail<Packet, 1> m_mainMail;
      rtos::Thread m_thread;

  };

}
