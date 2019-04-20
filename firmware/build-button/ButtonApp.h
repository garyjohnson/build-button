#ifndef BUTTONAPP_H
#define BUTTONAPP_H

#include <Arduino.h>

#define PIN_BUTTON   A1

typedef void (*releaseHandler)(unsigned long);

class ButtonApp {
  private:
    unsigned long timeKeyPressed = 0;
    releaseHandler onRelease = NULL;
  public:
    ButtonApp();
    ~ButtonApp();
    void setup();
    bool update(unsigned long runTime, unsigned long updateDelta);
    void setReleaseHandler(releaseHandler);
    unsigned long getHeldDuration();
};

#endif
