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
      auto next_packet = c_this->m_incomming.try_get_for(rtos::Kernel::wait_for_u32_forever);

      printf("destination ip: %s\n", &next_packet->dest_ip[0]);

      auto itr = c_this->m_clients.find(std::string{ &next_packet->dest_ip[0] });

      if (itr == c_this->m_clients.end()) {
        printf("Didn't found dest ip\n");
        // Destination ip does not exists
        auto error_response_message = c_this->m_clients[std::string{next_packet->src_ip}]->try_calloc_for(rtos::Kernel::wait_for_u32_forever);

        const char* error_ip = "0.0.0.0";
        const char* error_response = "Destination Host unreachable";

        printf("Creating error resp\n");
        // Create error packet
        memcpy(&error_response_message->dest_ip, &next_packet->src_ip, strlen(next_packet->dest_ip));
        memcpy(&error_response_message->src_ip, error_ip, strlen(error_ip));
        memcpy(&error_response_message->payload, error_response, strlen(error_response));

        // Send error packet
        c_this->m_clients[std::string{ std::string{ next_packet->src_ip } }]->put(error_response_message);

        // Free packet and continue
        c_this->m_incomming.free(next_packet);
        continue;
      } 

      printf("Found dest ip\n");
      // Destination exists
      Packet* new_packet = itr->second->try_calloc_for(rtos::Kernel::wait_for_u32_forever);

      memcpy(new_packet, next_packet, sizeof(Packet));

      itr->second->put(new_packet);

      c_this->m_incomming.free(next_packet);
    }
  }

}
