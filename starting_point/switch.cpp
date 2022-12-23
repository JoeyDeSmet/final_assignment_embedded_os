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
        
        // Add code here

        // Access client mail based on ip_address:
        // Mail<Packet>* destination_mail = m_clients["10.0.0.1"];

      }

    }
  }

}
