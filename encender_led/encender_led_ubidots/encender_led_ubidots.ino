#include <WiFi.h>
#include "UbidotsEsp32Mqtt.h"

const char* UBIDOTS_TOKEN = "BBUS-aqdfrpTUBCKoSEfF1hDT1kbpbcSQ7C";  // Ubidots TOKEN
const char* WIFI_SSID = "ARRIS-67C2";       // Wi-Fi SSID
const char* WIFI_PASS = "Jorgeurias12";     // Wi-Fi
const char* DEVICE_LABEL = "esp32";         // Nombre del device
const char* VARIABLE_LABEL = "led_state";   // Nombre de la variable

const int ledPin = 23; // Pin donde está conectado el LED

Ubidots ubidots(UBIDOTS_TOKEN);

void callback(char* topic, byte* payload, unsigned int length) {
  Serial.print("Mensaje recibido [");
  Serial.print(topic);
  Serial.print("]: ");
  String message;
  for (unsigned int i = 0; i < length; i++) {
    message += (char)payload[i];
  }
  Serial.println(message);

  // Convertir el mensaje recibido a un entero
  int ledState = message.toInt();

  // Encender o apagar el LED basado en el valor recibido
  if (ledState == 1) {
    digitalWrite(ledPin, HIGH); // Encender LED
  } else {
    digitalWrite(ledPin, LOW); // Apagar LED
  }
}

void setup() {
  Serial.begin(115200);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, LOW); // Asegurarse de que el LED esté apagado al inicio

  ubidots.setDebug(true);
  ubidots.connectToWifi(WIFI_SSID, WIFI_PASS);
  ubidots.setCallback(callback);
  ubidots.setup();
  ubidots.reconnect();
  ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL);
}

void loop() {
  if (!ubidots.connected()) {
    ubidots.reconnect();
    ubidots.subscribeLastValue(DEVICE_LABEL, VARIABLE_LABEL);
  }
  ubidots.loop();
}
