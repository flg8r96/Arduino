#include <Dhcp.h>
#include <Dns.h>
#include <Ethernet.h>
#include <EthernetClient.h>
#include <EthernetServer.h>
#include <EthernetUdp.h>
#include <util.h>
#include <Time.h>

#include <SPI.h>

/*
  Blink
  Turns on an LED on for one second, then off for one second, repeatedly.
 
  This example code is in the public domain.
 */
 
#include <Ethernet.h>

#include <SPI.h>  
// one line changed
//byte mac[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED }; 90-A2-DA-00-EE-58
//byte ip[] = { 192, 168, 9, 177 };
//byte server[] = { 192, 168, 9, 6 }; // Mail server address  MODIFY THIS FOR THE TARGET DOMAIN's MAIL SERVER

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xEE, 0x58 }; //physical mac address
byte ip[] = { 192, 168, 1, 140 }; // ip in lan
byte gateway[] = { 192, 168, 1, 254 }; // internet access via router
byte subnet[] = { 255, 255, 255, 0 }; //subnet mask
byte smtp[] = { 192,168,9,6 };

EthernetClient client;
//EthernetServer server(25);
//Client client(server, 25);
//Client client;
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int led = 9;
int ms = 1000;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(led, OUTPUT);
  
  Ethernet.begin(mac, ip,gateway,subnet);
  Serial.begin(9600);  
delay(1000);
  
  Serial.println("connecting...");
  
 // EthernetClient client = server.available();
  
  if (client.connect(smtp,25)) {
    Serial.println("connected");
    client.println("EHLO kltan");
    client.println("AUTH LOGIN");                         //see "http://base64-encoder-online.waraxe.us/"
    client.println("a2x0YW5AcHBoLmNvbS5teQ==");           //Type kltan@pph.com.my and encode it
    client.println("MTIzNDU2");                                                      //This line is password
    client.println("MAIL FROM:<someone@hotmail.com>");  
    client.println("RCPT TO:<someone@gmail.com>");
    client.println("DATA");
    client.println("from:someone@hotmail.com");
    client.println("to:someone@gmail.com");
    client.println("SUBJECT: Testing subject to arduino ethernet shield");
    client.println();
    client.println("This is the line body.");
    client.println("This is another line of the body.");
    client.println(".");
    client.println(".");
    client.println("QUIT");
  } else {
    Serial.println("connection failed");
  }
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  delay(ms);               // wait for a second
  digitalWrite(led, LOW);    // turn the LED off by making the voltage LOW
  delay(ms);               // wait for a second
  
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
