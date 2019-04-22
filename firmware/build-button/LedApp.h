#ifndef LEDAPP_H
#define LEDAPP_H

#include <Adafruit_NeoPixel.h>

#define PIN_NEOPIXEL A0
#define NEOPIXEL_COUNT 24

class LedApp {
  private:
    Adafruit_NeoPixel pixels;
    const uint32_t off = pixels.Color(0,0,0);

    const uint32_t lowStages[4] = { 
      pixels.Color(0,0,10),
      pixels.Color(0,0,255),
      pixels.Color(255,0,128),
      pixels.Color(255,0,0),
    };

    const uint32_t highStages[4] = { 
      pixels.Color(0,0,255),
      pixels.Color(255,0,128),
      pixels.Color(255,0,0),
      pixels.Color(255,0,0),
    };

    const uint32_t maxHold = 1000000;
    const uint32_t blinkDuration = 100000;
    const uint32_t maxAnimationDuration = 600000;

    int animation = -1;
    uint32_t animationDuration = 0;
    uint32_t buttonPressDuration = 0;

    void handleAnimation(uint32_t runTime, uint32_t updateDelta);
    void handleButtonHold(uint32_t runTime, uint32_t updateDelta);
    void endAnimation();
  public:
    LedApp();
    ~LedApp();
    void setup();
    bool update(uint32_t runTime, uint32_t updateDelta);
    void setButtonPressDuration(uint32_t duration);
    void startAnimationForStage(unsigned int stage);
};

#endif
