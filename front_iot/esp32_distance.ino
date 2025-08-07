#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* ssid = "";
const char* pass = "";
const char* serverUrl = "http://192.168.137.154:8080/update-distance";
int trig = 5;
int echo = 18;

long temps;
float distance;

void initWiFi() {
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, pass);
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  Serial.println(WiFi.localIP());
}

void envoyerDistance(float distanceMesuree) {
  if (WiFi.status() == WL_CONNECTED) {
    HTTPClient http;

    http.begin(serverUrl);
    http.addHeader("Content-Type", "application/json");

    DynamicJsonDocument doc(256);
    doc["distance"] = distanceMesuree;

    String jsonData;
    serializeJson(doc, jsonData);

    int httpResponseCode = http.PUT(jsonData);

    Serial.print("Code réponse serveur : ");
    Serial.println(httpResponseCode);

    if (httpResponseCode > 0) {
      String response = http.getString();
      Serial.println("Réponse du serveur : ");
      Serial.println(response);
    } else {
      Serial.print("Erreur HTTP : ");
      Serial.println(http.errorToString(httpResponseCode));
    }

    http.end();
  } else {
    Serial.println("WiFi déconnecté !");
  }
}

void setup()
{
  pinMode(trig, OUTPUT);
  pinMode(echo, INPUT);
  Serial.begin(115200);
  initWiFi();
  Serial.print("RRSI: ");
  Serial.println(WiFi.RSSI());
 
}

void loop()
{
  digitalWrite(trig, LOW);
  delayMicroseconds(2);
  digitalWrite(trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(trig, LOW);

  temps = pulseIn(echo, HIGH);

  distance = temps * 0.034 / 2;

  Serial.print("Distance en cm : ");
  Serial.println(distance);
  envoyerDistance(distance);
  delay(1000); 
}