#define MBED_CONF_RTOS_PRESENT 1

#include "mbed.h"

#include "include/switch.hpp"
#include "include/http-client.hpp"
#include "http-server.hpp"

using namespace EmbeddedOS;

int main(void) {
  printf("Start!\n");
  Switch nswitch;

  HTTPServer server0(nswitch.connect("10.100.0.2"), nswitch.get_switch_mail(), "<html>Hello</html>", "10.100.0.2");
  
  HTTPClient client0(nswitch.connect("10.0.0.2"), nswitch.get_switch_mail(), "10.0.0.2");

  nswitch.start();

  while(1){
    ThisThread::sleep_for(1s);
  }
  
  return 0;
}
