#include <Ethernet.h>
#include <WString.h>

byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };
byte ip[] = { 192, 168, 2, 12};  //IP address of the Ethernet Shield

IPAddress server(10,0,0,138);
// String PostData = "someDatatoPost";
String PostData = "{'name':'joe'}";

if (client.connect(server, 80)) {
  client.println("POST /Api/AddParking/3 HTTP/1.1");
  client.println("Host: 10.0.0.138");
  client.println("User-Agent: Arduino/1.0");
  client.println("Connection: close");
  client.print("Content-Length: ");
  client.println(PostData.lengh());
  client.println();
  client.println(PostData);
}
