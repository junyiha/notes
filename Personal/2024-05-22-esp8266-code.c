#include <Arduino.h>

// put function declarations here:

void InitLED()
{
  pinMode(LED_BUILTIN, OUTPUT);
}

void ControlLED()
{
  digitalWrite(LED_BUILTIN, HIGH);
  delay(1000);

  digitalWrite(LED_BUILTIN, LOW);
  delay(1000);
}

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char *ssid = "GH_wx_01";
const char *password = "Grand@honor666666!@#";

ESP8266WebServer esp8266_server;

void HandleRoot()
{
  esp8266_server.send(200, "text/plain", "hello from esp8266");
}

void HandleNotFound()
{
  esp8266_server.send(404, "text/plain", "404: not found");
}

void InitWiFi()
{
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to Wifi...");
  }
  Serial.printf("Connected to WiFi: %s \n", ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  esp8266_server.begin();
  esp8266_server.on("/", HandleRoot);
  esp8266_server.onNotFound(HandleNotFound);
  Serial.println("HTTP esp8266_server started");
}

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  InitLED();
  InitWiFi();
}

void loop() {
  // put your main code here, to run repeatedly:
  ControlLED();
  esp8266_server.handleClient();
}

// put function definitions here: