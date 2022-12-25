#include "http-server.hpp"


namespace EmbeddedOS{

  HTTPServer::HTTPServer(rtos::Mail<Packet, 1>* connection, rtos::Mail<Packet, 10>* switch_mail, const char* payload, const char* ip)
    : m_ip(ip), m_payload(payload), m_mail(connection), m_switch_mail(switch_mail) 
  {
    m_thread.start(mbed::callback(HTTPServer::server_loop, this));
  }

  void HTTPServer::server_loop(void* arg) {
    auto c_this = (HTTPServer *) arg;

    while (true) {
      // Get message from my own mail
      auto message = c_this->m_mail->try_get_for(rtos::Kernel::wait_for_u32_forever);
      
      // Create a response message
      Packet* response = c_this->m_switch_mail->try_calloc_for(rtos::Kernel::wait_for_u32_forever);      

      memcpy(&response->src_ip, c_this->m_ip, strlen(c_this->m_ip));
      memcpy(&response->dest_ip, message->src_ip, strlen(message->src_ip));
      memcpy(&response->payload, c_this->m_payload, strlen(c_this->m_payload));

      // Send message to switch
      c_this->m_switch_mail->put(response);

      // Free received message
      c_this->m_mail->free(message);
    }
  }

}