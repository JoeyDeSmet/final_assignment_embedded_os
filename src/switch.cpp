#include "./include/switch.hpp"

namespace EmbeddedOS {

  Switch::Switch() {}

  void Switch::start(void) {
    m_thread.start(mbed::callback(Switch::switch_loop, this));
  }

  rtos::Mail<Packet, 1>* Switch::connect(const char* client_ip) {
    auto created_connection = new Mail<Packet, 1>;
    m_clients[client_ip] = created_connection;

    return created_connection;
  }

  void Switch::switch_loop(void* arg) {
    auto c_this = (Switch*) arg;

    while (true) {
      // Check for message
      Packet* next_packet = c_this->m_incomming.try_get_for(rtos::Kernel::wait_for_u32_forever);

      auto itr = c_this->m_clients.find(next_packet->dest_ip);

      if (itr == c_this->m_clients.end()) {
        // Destination ip does not exists
        Packet* error_response = c_this->m_clients[next_packet->src_ip]->try_calloc_for(rtos::Kernel::wait_for_u32_forever);

        const char error_ip[] = "0.0.0.0";
        const char error_response[] = "Destination Host unreachable";

        // Create error packet
        memcpy(&error_response->dest_ip, &next_packet->src_ip, strlen(&next_packet->src_ip));
        memcpy(&error_response->src_ip, &error_ip, strlen(&error_ip));
        memcpy(&error_response->payload, &error_response, strlen(&error_response));

        // Send error packet
        c_this->m_clients[next_packet->src_ip]->put(error_response);

        // Free packet and continue
        c_this->m_incomming.free(next_packet);
        continue;
      } 

      // Destination exists
      Packet* new_packet = itr->second->try_calloc_for(rtos::Kernel::wait_for_u32_forever);

      memcpy(new_packet, new_packet, sizeof(Packet));

      itr->second->put(new_packet);

      c_this->m_incomming.free(next_packet);
    }
  }

}
