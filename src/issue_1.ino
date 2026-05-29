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
