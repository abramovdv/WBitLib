#ifndef Wbit_h
#define Wbit_h

#include <ArduinoJson.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClientSecure.h>
#include "Arduino.h"
#include "ImageSaver.h"
#include "Utils.h"

#define HOST "api.weatherbit.io"

struct WindData {
  float speed;
  const char* windDir;
  const char* windDirChar;
};

struct SunData {
  String sunrise;
  String sunset;
};

// see https://arduinojson.org/v6/assistant/
class Wbit {
 public:
  int lastCode = 0;
  const char* lastIcon;
  const char* location;
  const char* descr;
  float temp;
  WindData wind;
  SunData sun;

  Wbit(const char* token, const char* city, const char* country,
       const char* lang);
  void syncGetRequest(bool loadIcon);
  void saveImage();
  void init();
  SunData getSunData(int minTimeZone);

 private:
  const char* _uri = "/v2.0/current?";
  const char* _uriIcon = "/static/img/icons/";
  const char* _token;
  const char* _city;
  const char* _country;
  const char* _lang;
  String getUrl();
  String getIconUrl();
  String getChars(int value);
  String getTime(String time, int minTimeZone);
};

#endif