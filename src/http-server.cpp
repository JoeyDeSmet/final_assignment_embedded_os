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
      printf("Server got message\n");

      c_this->m_mail->free(message);

      // Send response here ....
      printf("server allocating memory\n");
      // Stuck here can't allocate memory 
      Packet* response = c_this->m_mail->try_alloc();
      while(response == nullptr){
        response = c_this->m_mail->try_alloc();
      }
      printf("server allocated memory\n");
      response->dest_ip = "10.0.0.2";
      // response->src_ip = src_ip;
      response->payload = c_this->payload;
      c_this->m_mail->put(response);
      printf("sended response\n");
      
    }
  }

}