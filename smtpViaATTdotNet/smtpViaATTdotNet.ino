
#include <SPI.h>
#include <Ethernet.h>

byte mac[] = { 0x90, 0xA2, 0xDA, 0x00, 0xEE, 0x58 }; //physical mac address
IPAddress ip( 192, 168, 1, 140 );    
IPAddress gateway( 192, 168, 1, 254 );
IPAddress subnet( 255, 255, 255, 0 );

// gmail.com email server
IPAddress server( 67, 195, 15, 5 );
//IPAddress server( 192, 168, 1, 130 );

EthernetClient client;

void setup()
{
  Serial.begin(9600);
  pinMode(4,OUTPUT);
  digitalWrite(4,HIGH);
  Ethernet.begin(mac, ip, gateway, gateway, subnet); 
  delay(2000);
  Serial.println("Ready. Press 'e' to send");
}

void loop()
{
  byte inChar;
  inChar = Serial.read();
  if(inChar == 'e')
  {
      if(sendEmail()) Serial.println("Email sent");
      else Serial.println("Email failed");
  }
}

byte sendEmail()
{
  byte thisByte = 0;
  byte respCode;
  
  if (client.connect(server,25)) {
    Serial.println("connected");
  } else {
    Serial.println("connection failed");
    return 0;
  }

  if(!eRcv()) return 0;
  
  client.write("ehlo mattperkins.net \r\n");
  Serial.println("sending public ip");
  if(!eRcv()) return 0;
  
  client.write("auth login \r\n");
  Serial.println("starting auth");
  if(!eRcv()) return 0;
  
  client.write("ZmxnOHJAYXR0Lm5ldA==\r\n");
  Serial.println("username entered");
  if(!eRcv()) return 0;
  
  client.write("Y2hpY2tlbjE=\r\n");
  Serial.println("password entered");
  if(!eRcv()) return 0;

// change this
  client.write("MAIL From:<flg8r@att.net>\r\n");
  Serial.println("MAIL From:<flg8r@att.net>");
  if(!eRcv()) return 0;
  
// change this  
  client.write("RCPT To:<flg8r96@gmail.com>\r\n");
    Serial.println("RCPT To:<flg8r96@gmail.com>");
    if(!eRcv()) return 0;
  client.write("RCPT To:<4076197326@txt.att.net>\r\n");
    Serial.println("sending to brian's phone");
    if(!eRcv()) return 0;
  client.write("RCPT To:<6196999155@vtext.com>\r\n");
    Serial.println("sending to matt's phone");
    if(!eRcv()) return 0;

  client.write("DATA\r\n");
  Serial.println("DATA");
  if(!eRcv()) return 0;
  
  client.write("SUBJECT: Bucklenany, Inc. - CRITICAL message from you Nanny!\r\n");
  Serial.println("SUBJECT: Bucklenany, Inc. - CRITICAL message from you Nanny!");
  client.write("\r\n");
  client.write("\r\n");
  client.write("CRITICAL EVENT - Temperature exceeds the safe threshold!\r\n");    
  client.write("Tempaerature = 103'F\r\n");
  client.write("Location = not known\r\n");
  Serial.println("message sent");
  
  client.write(".\r\n");
  if(!eRcv()) return 0;
  
 // client.write("\r\n");
  client.write("QUIT\r\n");
  if(!eRcv()) return 0;

  client.stop();
  Serial.println("disconnected");
  return 1;
}

byte eRcv()
{
  byte respCode;
  byte thisByte;
  
  while(!client.available()) delay(1);

  respCode = client.peek();

  while(client.available())
  {  
    thisByte = client.read();    
    Serial.write(thisByte);
  }

  if(respCode >= '4')
  {
    efail();
    return 0;  
  }
  
  return 1;
}

void efail()
{
  byte thisByte = 0;

  client.write("QUIT\r\n");

  while(!client.available()) delay(1);

  while(client.available())
  {  
    thisByte = client.read();    
    Serial.write(thisByte);
  }

  client.stop();
  Serial.println("disconnected");
}
