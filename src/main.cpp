
#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <WiFiClient.h>

#include <Wbit/Wbit.h>

ESP8266WiFiMulti WiFiMulti;
// https://api.weatherbit.io/v2.0/current?city=Cork&country=Ireland&lang=ru&key=*TOKEN*
Wbit ow("*TOKEN*", "Cork", "Ireland", "en");

void setup() {
  delay(1000);
  Serial.begin(115200);
  ow.init();

  for (uint8_t t = 6; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("ssid", "password");
  delay(3000);
}

void loop() {
  if (WiFiMulti.run() == WL_CONNECTED) {
    ow.syncGetRequest(true);
    Serial.print("temp: :");
    Serial.println(String(ow.temp));
    Serial.print("description:");
    Serial.println(String(ow.descr));
    Serial.print("location:");
    Serial.println(String(ow.location));
    SunData sun = ow.getSunData(240);
    Serial.print(String(sun.sunrise));
    Serial.print(" -> ");
    Serial.println(String(sun.sunset));
    WindData wind = ow.wind;
    Serial.print("wind speed:  ");
    Serial.print(String(wind.speed));
    Serial.println(" m/s"); 

  } else {
    Serial.println("Not connected...");
  }
  delay(20000);
}