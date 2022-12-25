#include "./include/http-client.hpp"

namespace EmbeddedOS {

  HTTPClient::HTTPClient(rtos::Mail<Packet, 1>* connection, rtos::Mail<Packet, 10>* switch_mail, const std::string& ip) 
    : m_mail(connection), m_switch_mail(switch_mail), m_ip(ip) 
  {
    m_thread.start(mbed::callback(HTTPClient::client_loop, this));
  }
  
  rtos::Mail<Packet, 1>* HTTPClient::getMail(void){
    return &m_main_mail;
  }

  void HTTPClient::client_loop(void* arg) {
    auto c_this = (HTTPClient *) arg;

    while (true) {
      // Get info from main
      Packet * mainMessage = c_this->m_main_mail.try_get_for(rtos::Kernel::wait_for_u32_forever);
      // Send requests here ....
      Packet* message = c_this->m_switch_mail->try_calloc_for(rtos::Kernel::wait_for_u32_forever);
      
      message->src_ip = c_this->m_ip;
      message->dest_ip = "10.100.0.2";
      message->payload = "GET";
      
      c_this->m_switch_mail->put(message);
      c_this->m_main_mail.free(mainMessage);

      Packet* response = c_this->m_mail->try_get_for(rtos::Kernel::wait_for_u32_forever);
      printf("[Client:%s] response form %s : %s\n", c_this->m_ip.c_str(), response->src_ip.c_str(), response->payload.c_str());
      c_this->m_mail->free(response);

      ThisThread::sleep_for(1s);
    }
  }

}
