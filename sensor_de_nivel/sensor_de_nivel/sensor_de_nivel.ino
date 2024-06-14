#define BLYNK_PRINT Serial
#define BLYNK_TEMPLATE_ID "TMPL26E8SUCS3"
#define BLYNK_TEMPLATE_NAME "Llenado de agua"
#define BLYNK_AUTH_TOKEN "4IdapO1-cBSPMbuk8ME56PSsGK9wbON5"
#include <WiFi.h>
#include <BlynkSimpleEsp32.h>
#include <Ultrasonic.h>

// Definición de pines
#define TRIG_PIN 4
#define ECHO_PIN 5
#define RELAY_PIN 18
#define LED_BUILTIN 2 // Pin del LED azul incorporado

// Variables de configuración
const long distanciaMaxima = 10; // Distancia en cm para detener la bomba
char ssid[] = "ARRIS-67C2"; // Reemplaza con tu SSID
char pass[] = "Jorgeurias12"; // Reemplaza con tu contraseña

Ultrasonic ultrasonic(TRIG_PIN, ECHO_PIN);

// Variable para evitar múltiples notificaciones
bool tanqueLleno = false;

void setup() {
  Serial.begin(115200);
  Blynk.begin(BLYNK_AUTH_TOKEN, ssid, pass);
  
  pinMode(RELAY_PIN, OUTPUT);
  pinMode(LED_BUILTIN, OUTPUT);
  
  digitalWrite(RELAY_PIN, LOW); // Inicialmente, la bomba está apagada
  digitalWrite(LED_BUILTIN, LOW); // Inicialmente, el LED está apagado
}

void loop() {
  Blynk.run();
  long distancia = ultrasonic.read();

  if (distancia <= distanciaMaxima) {
    digitalWrite(RELAY_PIN, LOW); // Apaga la bomba
    digitalWrite(LED_BUILTIN, LOW); // Apaga el LED
    if (!tanqueLleno) {
      Blynk.logEvent("notificacion"); 
      tanqueLleno = true; // Evita enviar múltiples notificaciones
    }
  } else {
    digitalWrite(RELAY_PIN, HIGH); // Enciende la bomba
    digitalWrite(LED_BUILTIN, HIGH); // Enciende el LED
    tanqueLleno = false; // Resetea la variable para la próxima vez
  }

  delay(1000); // Espera 1 segundo antes de la siguiente lectura
}
