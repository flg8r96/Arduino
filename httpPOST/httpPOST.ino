IPAddress server(10,0,0,138);
String PostData = "someDatatoPost";

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
