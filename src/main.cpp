#define MBED_CONF_RTOS_PRESENT 1

#include "mbed.h"

#include "include/switch.hpp"
#include "include/http-client.hpp"
#include "http-server.hpp"
#include "Thread.h"
#include <vector>

using namespace EmbeddedOS;

// static void startClients(std::vector<HTTPClient*> clinets, std::vector<std::string> serverIP){

//   for(int i = 0; i< 4; i++){
//     for(int k = 0; k < 3; k++){
//       auto clientMail = clients[i]->getMail(); 
//       auto message = clientMail->try_calloc_for(rtos::Kernel::wait_for_u32_forever);
      
//       message->dest_ip = serverIP[k];
//       message->payload = "GET";
      
//       clientMail->put(message);
//       ThisThread::sleep_for(1s);
//     }
//   }
// }

const char server0_ip[] = "10.100.0.2";

const char client0_ip[] = "10.0.0.2";

int main(void) {
  printf("Start!\n");
  Switch nswitch;

  HTTPServer server0(nswitch.connect(server0_ip), nswitch.get_switch_mail(), "<html>Hello from server0</html>", server0_ip);
  // HTTPServer server1(nswitch.connect("10.100.0.3"), nswitch.get_switch_mail(), "<html>Hello from server1</html>", "10.100.0.3");
  // HTTPServer server2(nswitch.connect("10.100.0.4"), nswitch.get_switch_mail(), "<html>Hello from server2</html>", "10.100.0.4");
  
  HTTPClient client0(nswitch.connect(client0_ip), nswitch.get_switch_mail(), client0_ip);
  // HTTPClient client1(nswitch.connect("10.0.0.3"), nswitch.get_switch_mail(), "10.0.0.3");
  // HTTPClient client2(nswitch.connect("10.0.0.4"), nswitch.get_switch_mail(), "10.0.0.4");
  // HTTPClient client3(nswitch.connect("10.0.0.5"), nswitch.get_switch_mail(), "10.0.0.5");

  // std::vector<HTTPClient*> clientsList = {&client0, &client1, &client2, &client3};
  // std::vector<std::string> serversIP = {"10.100.0.2","10.100.0.3","10.100.0.4"};

  nswitch.start();
  // Thread mainThread;
  // This inside whil loop ???
  // mainThread.start(callback(startClients, clientsList ));

  while(1){
    ThisThread::sleep_for(1s);
  }
  
  return 0;
}
