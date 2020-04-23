# Espanta Cuco
Firmware para Wemos NodeMcu v3 para controlar RGB neopixel ring usando WiFI vía MQTT. Aplicación para lampara de velador.

### Instructiones
Crear un archivo llamado *credentials.h* y agregar dentro:
```
#ifndef _CREDENTIALS_H
#define _CREDENTIALS_H

const char * ssid = "your_ssid";
const char * password = "your_password";
const char * mqtt_server = "your_mqtt_broker";

#endif
```

### Características
- [ ] Start in Access Point mode to configure your WiFi credentials.
- [x] Connect to MQTT broker.
- [x] Receive defined colors through MQTT and set it to RGB ring.
- [x] Receive RGB parameters colors through and set it to RGB ring.


## Librerías
- [Adafruit Neopixels](https://github.com/adafruit/Adafruit_NeoPixel)
- [PubSubClient mqtt](https://pubsubclient.knolleary.net/)
## Referencias
- [Wire up and setup Arduino IDE to support ESP8266.](https://dzone.com/articles/programming-the-esp8266-with-the-arduino-ide-in-3)
- [Create and configure mosquitto broker and client.](https://www.digitalocean.com/community/tutorials/how-to-install-and-secure-the-mosquitto-mqtt-messaging-broker-on-debian-8)
- [Add and code rgb pixels in esp8266.](https://www.hackster.io/thearduinoguy/esp8266-neopixel-ring-clock-a9cc74)