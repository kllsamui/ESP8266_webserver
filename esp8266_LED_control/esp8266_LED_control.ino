#include <ESP8266WiFi.h>
 
const char* ssid = "kll-wlan";
const char* password = "WELOVEKOH-SAMUI";
 
int ledPin = 13; // GPIO13
WiFiServer server(80);
 
void setup() {
  Serial.begin(115200);
  delay(10);
  Serial.println();
  Serial.println("___________");
  Serial.println("KLL ESP8266");
  Serial.println("___________");
 
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW);
 
  // Connect to WiFi network
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
 
  // Start the server
  server.begin();
  Serial.println("Server started");
 
  // Print the IP address
  Serial.print("Use this URL to connect: ");
  Serial.print("http://");
  Serial.print(WiFi.localIP());
  Serial.println("/");
 
}
 
void loop() {
  // Check if a client has connected
  WiFiClient client = server.available();
  if (!client) {
    return;
  }
 
  // Wait until the client sends some data
  Serial.println("new client");
  while(!client.available()){
    delay(1);
  }
 
  // Read the first line of the request
  String request = client.readStringUntil('\r');
  Serial.println(request);
  client.flush();
 
  // Match the request
 
  int value = LOW;
  if (request.indexOf("/LED=ON") != -1)  {
    digitalWrite(ledPin, HIGH);
    value = HIGH;
  }
  if (request.indexOf("/LED=OFF") != -1)  {
    digitalWrite(ledPin, LOW);
    value = LOW;
  }
 
// Set ledPin according to the request
//digitalWrite(ledPin, value);
 
  // Return the response
  client.println("HTTP/1.1 200 OK");
  client.println("Content-Type: text/html");
  client.println(""); //  do not forget this one
  client.println("<!DOCTYPE HTML>");
  client.println("<html>");
  client.print("i am a ESP8266 running as webserver / WIFI remote IO / for 3.5USD only");
  client.print("<br />");
  client.print(" <img src=\"http://kll.engineering-news.org/kllfusion01/downloads/ESP8266_myPINOUT.jpg\" alt=\"ESP8266\" > ");
  client.print("<br />");
  client.print("Led pin ( D7 aka GPIO13 ) is now: ");
 
  if(value == HIGH) {
    client.print("On");
    client.println("<a href=\"/LED=OFF\"\"><button>Turn Off </button></a><br />");  
  } else {
    client.print("Off");
    client.println("<a href=\"/LED=ON\"\"><button>Turn On </button></a>");
  }
  client.println("<br><br>");
  client.println("</html>");
 
  delay(1);
  Serial.println("Client disonnected");
  Serial.println("");
 
}
 
