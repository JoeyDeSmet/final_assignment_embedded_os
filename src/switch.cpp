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
      // Check for message
      Packet* next_packet = c_this->m_incomming.try_get_for(rtos::Kernel::wait_for_u32_forever);

      auto itr = c_this->m_clients.find(next_packet->dest_ip);

      if (itr == c_this->m_clients.end()) {
        // Destination ip does not exists
        Packet* error_response = c_this->m_clients[next_packet->src_ip]->try_alloc_for(rtos::Kernel::wait_for_u32_forever);

        // Create error packet
        error_response->dest_ip = next_packet->src_ip;
        error_response->src_ip = "0.0.0.0";
        error_response->payload = "Destination Host unreachable";

        // Send error packet
        c_this->m_clients[next_packet->src_ip]->put(error_response);

        // Free packet and continue
        c_this->m_incomming.free(next_packet);
        continue;
      } 

      // Destination exists
      Packet* new_packet = itr->second->try_alloc_for(rtos::Kernel::wait_for_u32_forever);

      new_packet->src_ip = next_packet->src_ip;
      new_packet->dest_ip = next_packet->dest_ip;
      new_packet->payload = next_packet->payload;

      itr->second->put(new_packet);

      c_this->m_incomming.free(next_packet);
    }
  }

}
