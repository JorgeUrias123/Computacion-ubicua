#define BLYNK_TEMPLATE_ID "TMPL20ATi7Nqu"
#define BLYNK_TEMPLATE_NAME "Led"
#define BLYNK_AUTH_TOKEN "sEAuhTsGX9j1HMJ8IXmD7EafIQfSsW8I"
#define BLYNK_PRINT Serial
#include <WiFi.h>
#include <WiFiClient.h>
#include <BlynkSimpleEsp32.h>

char network[] = "ARRIS-67C2";
char pass[] = "Jorgeurias12";

const int relayPin = 23;  // El pin al que está conectado el relé

void setup()
{
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, network, pass);
  pinMode(relayPin, OUTPUT);
}

BLYNK_WRITE(V0)
{
  int pinValue = param.asInt();
  digitalWrite(relayPin, pinValue);
}

void loop()
{
  Blynk.run();
}