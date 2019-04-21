#ifndef LEDAPP_H
#define LEDAPP_H

#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL A0
#define NEOPIXEL_COUNT 24

class LedApp {
  private:
    Adafruit_NeoPixel pixels;
    const unsigned long off = pixels.Color(0,0,0);

    const unsigned long lowStages[4] = { 
      pixels.Color(0,0,10),
      pixels.Color(0,0,255),
      pixels.Color(255,0,128),
      pixels.Color(255,0,0),
    };

    const unsigned long highStages[4] = { 
      pixels.Color(0,0,255),
      pixels.Color(255,0,128),
      pixels.Color(255,0,0),
      pixels.Color(255,0,0),
    };

    const unsigned long maxHold = 1000000;
    const unsigned long blinkDuration = 100000;
    const unsigned long maxAnimationDuration = 600000;

    unsigned long buttonPressDuration = 0;

    int animation = -1;
    unsigned long animationDuration = 0;

    void handleAnimation(unsigned long runTime, unsigned long updateDelta);
    void handleButtonHold(unsigned long runTime, unsigned long updateDelta);
    void endAnimation();
  public:
    LedApp();
    ~LedApp();
    void setup();
    bool update(unsigned long runTime, unsigned long updateDelta);
    void setButtonPressDuration(unsigned long duration);
    void startAnimationForStage(unsigned int stage);
};

#endif
