#include "Wbit.h"

ImageSaver saver;
HTTPClient http;
WiFiClient client;
WiFiClientSecure sClient;
DynamicJsonDocument doc(1116);

Wbit::Wbit(const char* token, const char* city, const char* country,
           const char* lang) {
  _token = token;
  _city = city;
  _country = country;
  _lang = lang;
}

void Wbit::init() {
  http.setFollowRedirects(true);
  http.setReuse(true);
  http.addHeader("Content-Type", "application/json");
  sClient.setInsecure();
}

String Wbit::getUrl() {
  return String(_uri) + "city=" + _city + "&country=" + _country +
         "&lang=" + _lang + "&key=" + _token;
}

String Wbit::getIconUrl() { return String(_uriIcon) + lastIcon + ".png"; }

// we can get data by http
void Wbit::syncGetRequest(bool loadIcon) {
  http.begin(client, HOST, 80, getUrl(), false);
  lastCode = http.GET();
  if (lastCode != 200) {
    Utils::DEBUG("error request: " + lastCode);
  } else {
    deserializeJson(doc, http.getString());
    JsonObject data = doc["data"][0];
    location = data["city_name"];
    temp = data["temp"];

    wind.speed = data["wind_spd"];
    wind.windDir = data["wind_cdir_full"];
    wind.windDirChar = data["wind_cdir"];

    const char* s1 = data["sunrise"];
    const char* s2 = data["sunset"];

    sun.sunrise = String(s1);
    sun.sunset = String(s2);

    getTime(sun.sunrise, 4);
    JsonObject weather = data["weather"];
    descr = weather["description"];
    lastIcon = weather["icon"];  // c04d
    if (loadIcon) {
      saveImage();
    }
    doc.clear();
  }
  http.end();
}

// we can get data only by https
// sClient.setInsecure for that
void Wbit::saveImage() {
  http.end();
  http.begin(sClient, HOST, 443, getIconUrl(), true);
  int code = http.GET();
  if (code == HTTP_CODE_OK || code == HTTP_CODE_MOVED_PERMANENTLY) {
    boolean imgSaved = saver.saveIcon(lastIcon, http);
    Utils::DEBUG("saving icon: " + Utils::boolStr(imgSaved));
  }
  http.end();
}

SunData Wbit::getSunData(int minTimeZone) {
  SunData resSun;
  resSun.sunrise = getTime(String(sun.sunrise), minTimeZone).c_str();
  resSun.sunset = getTime(String(sun.sunset), minTimeZone).c_str();
  return resSun;
}

String Wbit::getChars(int value) {
  String cValue = String(value);
  if (value < 10) {
    return '0' + cValue;
  } else {
    return cValue;
  }
}

String Wbit::getTime(String time, int minTimeZone) {
  int pos = time.indexOf(':');
  String h = time.substring(0, pos);
  String m = time.substring(pos + 1, time.length());
  int mins = (atoi(h.c_str()) * 60) + atoi(m.c_str()) + minTimeZone;
  int rM = mins % 60;
  int rH = mins / 60;
  return getChars(rH) + ":" + getChars(rM);
}