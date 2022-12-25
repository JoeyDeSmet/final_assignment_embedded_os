#include "./include/http-client.hpp"

namespace EmbeddedOS {

  HTTPClient::HTTPClient(rtos::Mail<Packet, 1>* connection) : m_mail(connection) {
    m_thread.start(mbed::callback(HTTPClient::client_loop, this));
  }

  rtos::Mail<Packet, 1>* HTTPClient::getMail(void){
    return &m_mainMail;
  }

  void HTTPClient::client_loop(void* arg) {
    auto c_this = (HTTPClient *) arg;

    while (true) {
      //Add mail from main to change ips and payloads
      auto mainMessage = c_this->m_mainMail.try_get_for(rtos::Kernel::wait_for_u32_forever);
      
      // Send requests here ....
      Packet* message = c_this->m_mail->try_alloc_for(rtos::Kernel::wait_for_u32_forever);

      message->dest_ip = mainMessage->dest_ip;
      message->payload = mainMessage->payload;
      c_this->m_mail->put(message);

      ThisThread::sleep_for(1s);
      // Receive responses ....
      Packet* response = c_this->m_mail->try_get_for(rtos::Kernel::wait_for_u32_forever);

      printf("[Client:%s] response form %s : %s\n", response->dest_ip.c_str(), response->src_ip.c_str(), response->payload.c_str());
      c_this->m_mail->free(response);
      c_this->m_mainMail.free(mainMessage);

    }
  }

}
