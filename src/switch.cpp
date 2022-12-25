#include "./include/switch.hpp"

namespace EmbeddedOS {

  Switch::Switch() {}

  void Switch::start(void) {
    m_thread.start(mbed::callback(Switch::switch_loop, this));
  }

  rtos::Mail<Packet, 1>* Switch::connect(const std::string& client_ip) {
    auto created_connection = new Mail<Packet, 1>;
    m_clients[client_ip] = created_connection;

    return created_connection;
  }

  void Switch::switch_loop(void* arg) {
    auto c_this = (Switch*) arg;

    while (true) {

      for (auto& client_mail : c_this->m_clients) {
        auto ip_addr = client_mail.first;
        auto mail = client_mail.second;

        Packet* message = mail->try_get();
        if(message == nullptr) continue;
        // check destination ip
        printf("Switch got message\n");

        if(c_this->m_clients.find(message->dest_ip) == c_this->m_clients.end()){
          //gaurd -> send error respone and free messages
        }

        message->src_ip = ip_addr;
        auto server_mail = c_this->m_clients[message->dest_ip];

        server_mail->try_alloc_for(rtos::Kernel::wait_for_u32_forever);
        server_mail->put(message);

        mail->free(message);

        // //wait for response
        // auto response = server_mail->try_get_for(rtos::Kernel::wait_for_u32_forever);
        // auto responseToClient = mail->try_alloc_for(rtos::Kernel::wait_for_u32_forever);

        // if(response->payload != ""){
          
        //   responseToClient->src_ip = response->src_ip;
        //   responseToClient->dest_ip = response->dest_ip;
        //   responseToClient->payload = response->payload;
          
        // }
        // else{
        //   responseToClient->src_ip = ip_addr;
        //   responseToClient->dest_ip = message->dest_ip;
        //   responseToClient->payload = "Error 404: Not found";
        // }

        // mail->put(responseToClient);
        // server_mail->free(response);
        
      }

    }
  }

}
