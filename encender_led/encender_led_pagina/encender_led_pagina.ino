#include <WiFi.h>
#include <WebServer.h>

// Configuración de la red WiFi
const char* ssid = "ARRIS-67C2";
const char* password = "Jorgeurias12";

// Configuración del servidor web en el puerto 80
WebServer server(80);

// Pin donde está conectado el LED
const int ledPin = 23;

// Variable para almacenar el estado del LED
bool ledState = LOW;

void setup() {
  Serial.begin(9600);
  pinMode(ledPin, OUTPUT);
  digitalWrite(ledPin, ledState);

  // Conexión a la red WiFi
  Serial.println("Conectando a WiFi...");
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Dirección IP: ");
  Serial.println(WiFi.localIP());

  // Definir rutas para manejar peticiones HTTP
  server.on("/", handleRoot);
  server.on("/toggle", handleToggle);
  
  server.begin();
  Serial.println("Servidor HTTP iniciado");
}

void loop() {
  server.handleClient();
}

void handleRoot() {
  String html = "<html><head>";
  html += "<style>";
  html += "body { font-family: Arial, sans-serif; text-align: center; margin-top: 50px; }";
  html += "h1 { color: #333; }";
  html += "button { padding: 15px 30px; font-size: 20px; color: white; background-color: #4CAF50; border: none; border-radius: 5px; cursor: pointer; margin: 10px; }";
  html += "button:hover { background-color: #45a049; }";
  html += "</style>";
  html += "</head><body>";
  html += "<h1>Control del Foco</h1>";
  if (ledState == HIGH) {
    html += "<p><a href=\"/toggle\"><button>Apagar Foco</button></a></p>";
  } else {
    html += "<p><a href=\"/toggle\"><button>Encender Foco</button></a></p>";
  }
  html += "</body></html>";
  server.send(200, "text/html", html);
}

void handleToggle() {
  ledState = !ledState;  // Cambiar el estado del LED
  digitalWrite(ledPin, ledState);
  server.sendHeader("Location", "/");
  server.send(303);
}
