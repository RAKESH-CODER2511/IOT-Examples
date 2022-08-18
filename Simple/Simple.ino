//creating an rest variable from aREST framework
#include <SPI.h>
#include <Ethernet.h>
//#include <avr/wdt.h>
#include <aREST.h>
aREST restVar = aREST();
byte macAdd[] = { 0xDE, 0xAD, 0xBE, 0xEF, 0xFE, 0xED };  
//the IP address for the shield:
byte ip[] = { 192, 168, 0, 115 };  

// telnet defaults to port 23
EthernetServer server = EthernetServer(23);

void setup() {
  // put your setup code here, to run once:
  pinMode(LED_BUILTIN, OUTPUT);
  
  Serial.begin(115200);

  restVar.function("led", ledFunction);
   Serial.println("Try DHCP...");
  if (Ethernet.begin(macAdd) == 0) {
    Serial.println("DHCP FAIL...Static IP");
    Ethernet.begin(macAdd , ip) ;
  }
  //starting server
  server.begin();
  Serial.println("Server IP: ");
  Serial.println(Ethernet.localIP());

  Serial.println("SETUP IS COMPLETE");
  
}

void loop() {
  // put your main code here, to run repeatedly:
  EthernetClient client = server.available();
  restVar.handle(client);
  wdt_reset();
}


//udf
int ledFunction(String value)
{
  if(value == "off"){
     digitalWrite(LED_BUILTIN, LOW);
     Serial.println("Turning off LED");
  }else if (value == "on"){
     digitalWrite(LED_BUILTIN, HIGH);
     Serial.println("Turning on LED");
  }

}
