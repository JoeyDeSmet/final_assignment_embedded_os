#define MBED_CONF_RTOS_PRESENT 1

#include "mbed.h"

#include "include/switch.hpp"
#include "include/http-client.hpp"
#include "http-server.hpp"

using namespace EmbeddedOS;

int main(void) {
  printf("Start!\n");
  Switch nswitch;

  HTTPServer server0(nswitch.connect("10.100.0.2"), "server0");
  // HTTPServer server1(nswitch.connect("10.100.0.3"), "server1");
  // HTTPServer server2(nswitch.connect("10.100.0.4"), "server2");
  // HTTPServer server3(nswitch.connect("10.100.0.5"), "server3");
  // HTTPServer server4(nswitch.connect("10.100.0.6"), "server4");
  
  HTTPClient client0(nswitch.connect("10.0.0.2"));
  // HTTPClient client1(nswitch.connect("10.0.0.3"));
  // HTTPClient client2(nswitch.connect("10.0.0.4"));
  // HTTPClient client3(nswitch.connect("10.0.0.5"));

  nswitch.start();

  auto mail = client0.getMail();

  Packet* message = mail->try_alloc_for(rtos::Kernel::wait_for_u32_forever);
  message->dest_ip = "10.100.0.2";
  message->payload = "Yo";
  mail->put(message);

  while(1){
    ThisThread::sleep_for(1s);
  }
  
  return 0;
}
