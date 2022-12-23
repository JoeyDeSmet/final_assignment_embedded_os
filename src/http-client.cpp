#include "./include/http-client.hpp"

namespace EmbeddedOS {

  HTTPClient::HTTPClient(rtos::Mail<Packet, 1>* connection) : m_mail(connection) {
    m_thread.start(mbed::callback(HTTPClient::client_loop, this));
  }

  void HTTPClient::client_loop(void* arg) {
    auto c_this = (HTTPClient *) arg;

    while (true) {
      // Send requests here ....


      // Receive responses ....
    }
  }

}
