# ESP8266 MQTT CLIENT RGB
Firmware for Wemos NodeMcu v3 to control rgb neopixel ring over MQTT.

### Instructions
Create a file called *credentials.h* add inside 
```
#ifndef _CREDENTIALS_H
#define _CREDENTIALS_H

const char * ssid = "your_ssid";
const char * password = "your_password";
const char * mqtt_server = "your_mqtt_broker";

#endif
```

### Features
- [ ] Start in Access Point mode to configure your WiFi credentials.
- [x] Connect to MQTT broker.
- [x] Receive defined colors through MQTT and set it to RGB ring.
- [ ] Receive RGB parameters colors through and set it to RGB ring.
- [ ] Add temperature sensor to control RGB color. (Map temperature to RGB).
- [ ] Get datetime from ntp server.
- [ ] Add on by timer.  

## Libraries
- [Adafruit Neopixels](https://github.com/adafruit/Adafruit_NeoPixel)
- [PubSubClient mqtt](https://pubsubclient.knolleary.net/)
## References
- [Wire up and setup Arduino IDE to support ESP8266.](https://dzone.com/articles/programming-the-esp8266-with-the-arduino-ide-in-3)
- [Create and configure mosquitto broker and client.](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-the-mosquitto-mqtt-messaging-broker-on-debian-8)
- [Add and code rgb pixels in esp8266.](https://www.hackster.io/thearduinoguy/esp8266-neopixel-ring-clock-a9cc74)