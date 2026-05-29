#include <WiFi.h>
#include <WebServer.h>
#include <Wire.h>
#include <Adafruit_CCS811.h>

const char* ssid = "POCO F7";
const char* password = "12345qwe";

Adafruit_CCS811 ccs;

WebServer server(80);

int eco2 = 0;
int tvoc = 0;
String calidad = "Sin datos";

String paginaHTML() {

  String html = R"rawliteral(
  <!DOCTYPE html>
  <html>
  <head>
    <meta charset="UTF-8">
    <meta http-equiv="refresh" content="2">
    <title>Calidad del Aire</title>

    <style>
      body{
        font-family: Arial;
        background:#111;
        color:white;
        text-align:center;
        padding-top:40px;
      }

      .card{
        background:#1e1e1e;
        width:350px;
        margin:auto;
        padding:30px;
        border-radius:20px;
        box-shadow:0 0 20px rgba(0,255,150,0.3);
      }

      h1{
        color:#00ff99;
      }

      .dato{
        font-size:28px;
        margin:20px;
      }

      .estado{
        font-size:32px;
        font-weight:bold;
        color:#00ffaa;
      }
    </style>
  </head>

  <body>

    <div class="card">
      <h1>🌍 Calidad del Aire</h1>

      <div class="dato">
        eCO2: )rawliteral";

  html += eco2;

  html += R"rawliteral( ppm
      </div>

      <div class="dato">
        TVOC: )rawliteral";

  html += tvoc;

  html += R"rawliteral( ppb
      </div>

      <div class="estado">
        )rawliteral";

  html += calidad;

  html += R"rawliteral(
      </div>

    </div>

  </body>
  </html>
  )rawliteral";

  return html;
}

void handleRoot() {
  server.send(200, "text/html", paginaHTML());
}

void setup() {

  Serial.begin(115200);

  Wire.begin(21, 22);

  Serial.println("Iniciando CCS811...");

  if (!ccs.begin()) {
    Serial.println("❌ Error iniciando CCS811");
    while (1);
  }

  ccs.setDriveMode(CCS811_DRIVE_MODE_1SEC);

  delay(2000);

  Serial.println("✅ Sensor listo");

  WiFi.begin(ssid, password);

  Serial.print("Conectando al WiFi");

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("✅ WiFi conectado");
  Serial.print("IP del ESP32: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);

  server.begin();

  Serial.println("✅ Servidor web iniciado");
}
