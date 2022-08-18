#include <ESP8266WiFi.h>
#include <aREST.h>

// Create aREST instance
aREST rest = aREST();

WiFiServer server(80);

// WiFi parameters
const char* ssid = "Your_ssid";
const char* password = "Your_password";


//#define LISTEN_PORT 80



//udf
int testFunction(String value){
  Serial.println("Received rest request");
}



void setup() {
  // put your setup code here, to run once:
   
  Serial.begin(115200);
  rest.function("test",testFunction);

  // Give name & ID to the device (ID should be 6 characters long)
  rest.set_id("1");
  rest.set_name("esp8266");

   // Connect to WiFi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(700);
    Serial.print(".");
    Serial.print(WiFi.status());
  }
  Serial.println("");
  Serial.println("WiFi connected");

  // Start the server
  server.begin();
  Serial.println("Server started");

  // Print the IP address
  Serial.println(WiFi.localIP());

}

void loop() {
  // put your main code here, to run repeatedly:
   // Handle REST calls
  WiFiClient clt = server.available();
  if(clt){
    while(!clt.available()){
      delay(5);
    }
    rest.handle(clt);
  }
  
}
