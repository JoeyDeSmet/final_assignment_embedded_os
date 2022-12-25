#pragma once 
#define MBED_CONF_RTOS_PRESENT 1

#include "packet.hpp"
#include "logging.hpp"

#include "mbed.h"
#include "rtos.h"
#include "rtos/Mail.h"
#include "rtos/Thread.h"

#include <string.h>

namespace EmbeddedOS {

  class HTTPClient {

    public:
      HTTPClient(rtos::Mail<Packet, 1>* connection, rtos::Mail<Packet, 10>* switch_mail, const char* ip);

      rtos::Mail<Packet, 1> * getMail(void);
    private:
      static void client_loop(void* arg);

    private:
      const char* m_ip;
      
      rtos::Thread m_thread;
      rtos::Mail<Packet, 1>* m_mail;
      rtos::Mail<Packet, 10>* m_switch_mail;
      rtos::Mail<Packet, 1> m_main_mail;

  };

}
