#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>
#include <Time.h>

#include <SPI.h>
#include <Ethernet.h>

#include <SPI.h>  

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xEE, 0x58 }; //physical mac address
byte ip[] = { 192, 168, 1, 140 }; // ip in lan
byte gateway[] = { 192, 168, 1, 254 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
//byte smtp[] = { 67, 195, 15, 5 };    // outbound.att.net (telnet outbound.att.net 25)
IPAddress smtp( 67, 195, 15, 5 );

//byte smtp[] = { 192, 168, 1, 130 };

EthernetClient client;
//EthernetServer server(25);
//Client client(server, 25);
//Client client;

int oneSDelay = 5000;

// the setup routine runs once when you press reset:
void setup() {  
  Serial.begin(9600);    
  Serial.println(smtp);
 // pinMode(4,OUTPUT);
  //digitalWrite(4,HIGH);
  // initialize the digital pin as an output.
  //pinMode(led, OUTPUT);
  
  Ethernet.begin(mac, ip, gateway, subnet);

  delay(oneSDelay);
  
  Serial.println("connecting...");
  delay(oneSDelay);
  
 // EthernetClient client = server.available();
  

}

// the loop routine runs over and over again forever:
void loop() {
//  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
//  delay(ms);               // wait for a second
//  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
//  delay(ms);               // wait for a second

  if (client.connect(smtp,25)){
    Serial.println("connected");
    client.println("EHLO");
    Serial.println("EHLO");
    client.println("AUTH LOGIN");                         //see "http://base64-encoder-online.waraxe.us/"
        Serial.println("AUTH LOGIN");
    client.println("ZmxnOHJAYXR0Lm5ldA==");               //flg8r@att.net flg-ZmxnOHI5NkBnbWFpbC5jb20=
        Serial.println("flg8r@att.net");
    client.println("Y2hpY2tlbjE=");                       //keywest1
        Serial.println("keywest1");
    client.println("MAIL FROM:<flg8r@att.net>");
        Serial.println("MAIL FROM:<flg8r@att.net>");  
    client.println("RCPT TO:<flg8r96@gmail.com>");
        Serial.println("RCPT TO:<flg8r96@gmail.com>");
    client.println("RCPT TO:<6196999155@vtext.com>");
      Serial.println("RCPT TO:<6196999155@vtext.com>");
    client.println("DATA");
    client.println("SUBJECT: Bucklenany, Inc. - CRITICAL message from you Nanny!");
    client.println();
    client.println();
    client.println("CRITICAL EVENT - Temperature exceeds the safe threshold!");    
    client.println("Tempaerature = 103'F");
    client.println("Location = not known");
    client.println(".");
    client.println();
    client.println("QUIT");
  } else {
    Serial.println("connection failed");
  }
  
  if (client.available()) {
    char c = client.read();
    Serial.print(c);
  }
  ;;
    if (!client.connected()) {
    Serial.println();
    Serial.println("disconnecting.");
    client.stop();
    for( ;; )
     ;
   }
}
