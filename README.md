# Final Assignment Embedded OS

This repository is an Assingnment for the Embedded OS course.

## Assingnment

Create an exercise that uses all concepts learned in this course. Other student have to be able to make this in less than 2 hours.

## Exercise

Implement a simple IP network with multiple HTTP servers, clients, and a switch using Mbed OS and threads. 

The clients should be able to send HTTP requests to the servers and receive HTTP responses, and the servers should be able to receive HTTP requests from the clients and send HTTP responses. 

The switch should be able to route packets between the clients and servers.

<hr/>

**Note**: You may have to change a but of the classes when you encounter memory issues, use char* instead of std::string, ... etc

1. Write a struct representing a IP packet. The struct sould contain the source and destination ip address and a payload.

2. Complete the folling Switch class so that it check if a message is on a client mail, and than forward the packet to the right client or server.

```cpp
#include <unordered_map>

class Switch {

  public:
    void start(void) {
      m_thread.start(callback(Switch::switch_loop, this));
    }

  public:
    Mail<Packet>* connect(const std::string& client_ip) {
      auto created_connection = new Mail<Packet, 1>;
      m_clients[client_ip] = created_connection;

      return created_connection;
    }

  private:
    void switch_loop(void* arg) {
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

  private:
    rtos::thread m_thread;
    std::unordered_map<std::string, Mail<Packet> *> m_clients; // Mapping of ip to mail (key : value)

};
```

3. Complete this HTTPClient class. The client loop should send HTTP request to a server using the m_mail Mail. After that it should wait for a response and print the response to the terminal.

```cpp
class HTTPClient {

  public:
    HTTPClient(Mail<Packet>* connection) : m_mail(connection) {
      m_thread.start(callback(HTTPClient::client_loop, this));
    }

  private:
    void client_loop(void* arg) {
      auto c_this = (HTTPClient*) arg;

      while (true) {
        // Send requests here ....


        // Receive responses ....
      }
    }

  private:
    Mail<Packet>* m_mail;
    rtos::Thread m_thread;

};
```

4. Write a class for the HTTPServer, that receives some packets and than send a respond back.

5. In the main function you sould create some HTPP client a switch and some HTTP servers.
