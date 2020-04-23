#include <ESP8266WiFi.h>
#include <PubSubClient.h>
#include <Adafruit_NeoPixel.h>
#include <SPI.h>
#include "credentials.h"

//neopixel
#define PIN 4 //D2
#define NUMPIXELS 16
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

WiFiClient espClient;
PubSubClient client(espClient);
long lastMsg = 0;
char msg[50];
int value = 0;

//TODO: move rgb animation to library
void showColor(uint8_t r, uint8_t g, uint8_t b)
{
   for(int i=0;i<NUMPIXELS;i++){
    if(i%2==0){
      pixels.setPixelColor(i, pixels.Color(r,g,b));
    //pixels.fill(pixels.Color(r,g,b),0,1); //partial
      pixels.show();
    }else{
       pixels.setPixelColor(i, pixels.Color(0,0,0));
       pixels.show();
    }
  }
}

void showRed(void)
{
   showColor(255,0,0);
}

void showGreen(void)
{
   showColor(0,255,0);
}

void showBlue(void)
{
   showColor(0,0,255);
}

void showWhite(void)
{
   showColor(255,255,255);
}

void turnOff(void)
{
   showColor(0,0,0);
}

void setup() {
  pinMode(BUILTIN_LED, OUTPUT);     // Initialize the BUILTIN_LED pin as an output
  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
  client.setCallback(callback);

  pixels.begin();
  pixels.setBrightness(50);
  showRed();
}
 
void setup_wifi() {
  Serial.print("MAC:");
  Serial.println(WiFi.macAddress()); // print MAC 
  
  //TODO: start in AP mode to set WiFi parameters
 
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}
 
void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print(payload[i]);
    Serial.print(" ");
  }
  Serial.println();

  // Convert char to String object 
  String mqttMsg = String((char*)payload);
  Serial.print("#");
  Serial.print(mqttMsg);
  Serial.print("\n");

  //Compare message to get RGB color 
  if( memcmp( (char *)payload, "rgb(", 4)==0){
    Serial.print("RGB received\n");
    int endStr = mqttMsg.indexOf(")");
    String subStr = mqttMsg.substring(4,endStr);
    Serial.print("#");
    Serial.print(subStr);
    Serial.print("\n");

    int endRed = subStr.indexOf(",");
    String redStr = subStr.substring(0,endRed);

    int endGreen = subStr.indexOf(",",endRed+1);
    String greenStr = subStr.substring(endRed+1,endGreen);

    int endBlue = subStr.indexOf(",",endGreen+1);
    String blueStr = subStr.substring(endGreen+1,endBlue);

    Serial.print("->");
    Serial.print(redStr);
    Serial.print("\n->");
    Serial.print(greenStr);
    Serial.print("\n->");
    Serial.print(blueStr);
    
    for(int i=0;i<NUMPIXELS;i++){
      pixels.setPixelColor(i, pixels.Color(redStr.toInt(),greenStr.toInt(),blueStr.toInt()));
      pixels.show();
    }
  }

 
  // Switch on the LED if an 1 was received as first character
  else if ((char)payload[0] == 'r') {
    showRed();
  }else  if ((char)payload[0] == 'g') {
    showGreen();
  }else  if ((char)payload[0] == 'b') {
    showBlue();
  }else  if ((char)payload[0] == 'w') {
    showWhite();
  }else  if ((char)payload[0] == 'o') {
    turnOff();
  }else {
    digitalWrite(BUILTIN_LED, HIGH);  // Turn the LED off by making the voltage HIGH
  }
 
}
 
void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("ESP8266Client")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("outTopic", "hello world 1");
      // ... and resubscribe
      client.subscribe("light");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(10000);
    }
  }
}
 
void loop() {
 
  if (!client.connected()) {
    reconnect();
  }
  client.loop();
 
  long now = millis();
  if (now - lastMsg > 60000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "stat #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("outTopic", msg);
  }
}
