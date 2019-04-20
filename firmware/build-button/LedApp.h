#ifndef LEDAPP_H
#define LEDAPP_H

#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL A0
#define NEOPIXEL_COUNT 24

class LedApp {
  private:
    Adafruit_NeoPixel pixels;
    unsigned long off = pixels.Color(0,0,0);
    unsigned long lowStage1 = pixels.Color(0,0,10);
    unsigned long highStage1 = pixels.Color(0,0,255);
    unsigned long highStage2 = pixels.Color(255,0,128);
    unsigned long highStage3 = pixels.Color(255,0,0);

    unsigned long currentLowColor = 0;
    unsigned long currentHighColor = 0;
    unsigned long maxHold = 1000000;
    unsigned long buttonPressDuration = 0;
  public:
    LedApp();
    ~LedApp();
    void setup();
    bool update(unsigned long runTime, unsigned long updateDelta);
    void setButtonPressDuration(unsigned long duration);
};

#endif
