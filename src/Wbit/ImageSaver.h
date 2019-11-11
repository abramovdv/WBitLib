#ifndef ImageSaver_h
#define ImageSaver_h

#include "Arduino.h"
#include "ESP8266HTTPClient.h"
#include "FS.h"
#include "Utils.h"

#define FILE "/img_name"
#define FILE_IMG "/icon.png"

class ImageSaver {
 public:
  ImageSaver();
  boolean saveIcon(const char* newCaption, HTTPClient& http);

 private:
  String getIconCaption();
  boolean saveIconCaption(const char* caption);
  boolean saveIconFile(HTTPClient& http);
};

#endif