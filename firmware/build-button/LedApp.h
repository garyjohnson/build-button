#ifndef LEDAPP_H
#define LEDAPP_H

#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL A0
#define NEOPIXEL_COUNT 24

class LedApp {
  private:
    Adafruit_NeoPixel pixels;
    unsigned long off;
    unsigned long lowStage1;
    unsigned long highStage1;
    unsigned long highStage2;
    unsigned long highStage3;
    unsigned long currentLowColor;
    unsigned long currentHighColor;
    unsigned long maxHold;
    unsigned long buttonPressDuration;
  public:
    LedApp();
    ~LedApp();
    void setup();
    bool update(unsigned long runTime, unsigned long updateDelta);
    void setButtonPressDuration(unsigned long duration);
};

#endif
