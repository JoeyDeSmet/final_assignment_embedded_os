#define MBED_CONF_RTOS_PRESENT 1

#include "mbed.h"
#include "rtos/Thread.h"

#include "include/logging.hpp"
#include "include/switch.hpp"
#include "include/http-server.hpp"
#include "include/http-client.hpp"

using namespace EmbeddedOS;

rtos::Mutex print_mtx;

const char* server0_ip = "10.100.0.2";
const char* server1_ip = "10.100.0.3";
const char* server2_ip = "10.100.0.4";

const char* client0_ip = "10.0.0.2";
const char* client1_ip = "10.0.0.3";
const char* client2_ip = "10.0.0.4";
const char* client3_ip = "10.0.0.5";

const char* available_servers[] = { server0_ip, server1_ip, server2_ip };

int main(void) {
  print("Start!\n");
  Switch nswitch;

  HTTPServer server0(nswitch.connect(server0_ip), nswitch.get_switch_mail(), "<html>Hello, from server0</html>", server0_ip);
  HTTPServer server1(nswitch.connect(server1_ip), nswitch.get_switch_mail(), "<html>Hola, desde el servidor1</html>", server1_ip);
  HTTPServer server2(nswitch.connect(server2_ip), nswitch.get_switch_mail(), "<html>Hei, palvelimelta2</html>", server2_ip);

  HTTPClient client0(nswitch.connect(client0_ip), nswitch.get_switch_mail(), client0_ip);
  HTTPClient client1(nswitch.connect(client1_ip), nswitch.get_switch_mail(), client1_ip);
  HTTPClient client2(nswitch.connect(client2_ip), nswitch.get_switch_mail(), client2_ip);
  HTTPClient client3(nswitch.connect(client3_ip), nswitch.get_switch_mail(), client3_ip);

  nswitch.start();

  while(true) { }
  
  return 0;
}
