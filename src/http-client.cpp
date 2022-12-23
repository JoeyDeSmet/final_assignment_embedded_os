#include "./include/http-client.hpp"

namespace EmbeddedOS {

  HTTPClient::HTTPClient(rtos::Mail<Packet, 1>* connection) : m_mail(connection) {
    m_thread.start(mbed::callback(HTTPClient::client_loop, this));
  }

  void HTTPClient::client_loop(void* arg) {
    auto c_this = (HTTPClient *) arg;

    while (true) {
      //Add mail from main to change ips and payloads


      // Send requests here ....
      printf("Sending request from client\n");
      Packet* message = c_this->m_mail->try_alloc_for(rtos::Kernel::wait_for_u32_forever);

      message->dest_ip = "10.100.0.2";
      message->payload = "What server is this?";
      c_this->m_mail->put(message);
      printf("sended message to switch from client\n");
      // Receive responses ....
      Packet* response = c_this->m_mail->try_get_for(rtos::Kernel::wait_for_u32_forever);

      printf("[Client:%s] response form %s : %s\n", response->src_ip.c_str(), response->dest_ip.c_str(), response->payload.c_str());
      c_this->m_mail->free(response);

    }
  }

}
