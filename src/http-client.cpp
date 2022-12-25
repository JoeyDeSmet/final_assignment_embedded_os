#include "./include/http-client.hpp"

extern const char* available_servers[3];

namespace EmbeddedOS {

  HTTPClient::HTTPClient(rtos::Mail<Packet, 1>* connection, rtos::Mail<Packet, 10>* switch_mail, const char* ip) 
    : m_ip(ip), m_mail(connection), m_switch_mail(switch_mail)
  { 
    m_thread.start(mbed::callback(HTTPClient::client_loop, this));
  }
  
  rtos::Mail<Packet, 1>* HTTPClient::getMail(void){
    return &m_main_mail;
  }

  void HTTPClient::client_loop(void* arg) {
    auto c_this = (HTTPClient *) arg;

    while (true) {
      Packet* message = c_this->m_switch_mail->try_calloc_for(rtos::Kernel::wait_for_u32_forever);
      
      const char* payload = "GET";
      const char* random_server = available_servers[int (rand() % 3)];
      
      printf("[Client:%s] sending request to %s\n", c_this->m_ip, random_server);

      memcpy(message->src_ip, c_this->m_ip, strlen(c_this->m_ip));
      memcpy(message->dest_ip, random_server, strlen(random_server));
      memcpy(message->payload, payload, strlen(payload));
      
      c_this->m_switch_mail->put(message);

      Packet* response = c_this->m_mail->try_get_for(rtos::Kernel::wait_for_u32_forever);
      
      printf("[Client:%s] response form %s:\n %s\n", c_this->m_ip, response->src_ip, response->payload);
      
      c_this->m_mail->free(response);

      ThisThread::sleep_for(1s);
    }
  }

}
