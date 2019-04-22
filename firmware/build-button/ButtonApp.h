#ifndef BUTTONAPP_H
#define BUTTONAPP_H

#include <Arduino.h>

#define PIN_BUTTON   A1

typedef void (*releaseHandler)(uint32_t);

class ButtonApp {
  private:
    uint32_t timeKeyPressed = 0;
    releaseHandler onRelease = NULL;
  public:
    ButtonApp();
    ~ButtonApp();
    void setup();
    bool update(uint32_t runTime, uint32_t updateDelta);
    void setReleaseHandler(releaseHandler);
    uint32_t getHeldDuration();
};

#endif
