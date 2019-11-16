#include "ImageSaver.h"

ImageSaver::ImageSaver() {}

// you need call http.begin(url); before it
boolean ImageSaver::saveIcon(const char *newCaption, HTTPClient &http) {
  String oldCaption = getIconCaption();
  DEBUG_MSG(oldCaption + " =? " + newCaption);
  if (oldCaption != newCaption) {
    saveIconCaption(newCaption);
    return saveIconFile(http);
  }
  return false;
}

String ImageSaver::getIconCaption() {
  if (SPIFFS.begin()) {
    File confs = SPIFFS.open(FILE, "r");
    if (confs) {
      String line = confs.readStringUntil('\n');
      confs.close();
      return line;
    }
  }
  return "";
}

boolean ImageSaver::saveIconFile(HTTPClient &http) {
  int result = 0;
  int code = http.GET();
  if (code > 0) {
    File f = SPIFFS.open(FILE_IMG, "w");
    if (f) {
      result = http.writeToStream(&f);
      f.close();
    }
  }
  http.end();
  return result > 0;
}

boolean ImageSaver::saveIconCaption(const char *caption) {
  if (SPIFFS.begin()) {
    SPIFFS.remove(FILE);
    File confs = SPIFFS.open(FILE, "w");
    if (confs) {
      confs.print(caption);
      confs.println("\n");
      confs.close();
      return true;
    }
  }
  return false;
}