#define MBED_CONF_RTOS_PRESENT 1

#include "mbed.h"

#include "include/switch.hpp"
#include "include/http-client.hpp"
#include "http-server.hpp"

using namespace EmbeddedOS;

int main(void) {
  printf("Start!\n");
  Switch nswitch;

  HTTPServer server0(nswitch.connect("10.100.0.2"), nswitch.get_switch_mail(), "<html>Hello from server0</html>", "10.100.0.2");
  HTTPServer server1(nswitch.connect("10.100.0.3"), nswitch.get_switch_mail(), "<html>Hello from server1</html>", "10.100.0.3");
  HTTPServer server2(nswitch.connect("10.100.0.4"), nswitch.get_switch_mail(), "<html>Hello from server2</html>", "10.100.0.4");
  
  HTTPClient client0(nswitch.connect("10.0.0.2"), nswitch.get_switch_mail(), "10.0.0.2");
  HTTPClient client1(nswitch.connect("10.0.0.3"), nswitch.get_switch_mail(), "10.0.0.3");
  HTTPClient client2(nswitch.connect("10.0.0.4"), nswitch.get_switch_mail(), "10.0.0.4");
  HTTPClient client3(nswitch.connect("10.0.0.5"), nswitch.get_switch_mail(), "10.0.0.5");


  nswitch.start();

  while(1){
    ThisThread::sleep_for(1s);
  }
  
  return 0;
}
