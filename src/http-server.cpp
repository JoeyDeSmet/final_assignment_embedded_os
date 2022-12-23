#include "http-server.hpp"


namespace EmbeddedOS{

  HTTPServer::HTTPServer(rtos::Mail<Packet, 1>* connection, std::string payload): m_mail(connection), payload(payload){
    m_thread.start(mbed::callback(HTTPServer::server_loop, this));
  }

  void HTTPServer::server_loop(void* arg) {
    auto c_this = (HTTPServer *) arg;

    while (true) {
      // Receive request ....
      auto message = c_this->m_mail->try_get_for(rtos::Kernel::wait_for_u32_forever);

      printf("Got request from switch on server\n");
      
      // Send response here ....
      auto response = c_this->m_mail->try_alloc_for(rtos::Kernel::wait_for_u32_forever);

      response->dest_ip = message->src_ip;
      response->src_ip = message->dest_ip;
      response->payload = c_this->payload;
      c_this->m_mail->free(message);
      c_this->m_mail->put(response);
      
      printf("Sended back response to switch\n");
    }
  }

}