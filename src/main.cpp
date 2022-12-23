#define MBED_CONF_RTOS_PRESENT 1

#include "mbed.h"

#include "include/switch.hpp"
#include "include/http-client.hpp"

using namespace EmbeddedOS;

int main(void) {
  Switch nswitch;
  
  HTTPClient client0(nswitch.connect("10.0.0.2"));
  HTTPClient client1(nswitch.connect("10.0.0.3"));
  HTTPClient client2(nswitch.connect("10.0.0.4"));
  HTTPClient client3(nswitch.connect("10.0.0.5"));
  
  // TODO: Add httpServers

  nswitch.start();

  return 0;
}
