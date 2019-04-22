#include "ButtonApp.h"

ButtonApp::ButtonApp() {
}

ButtonApp::~ButtonApp() {
}

void ButtonApp::setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);
}

bool ButtonApp::update(uint32_t runTime, uint32_t updateDelta) {
  if (digitalRead(PIN_BUTTON) == 1) {
    timeKeyPressed += updateDelta;
    return true;
  } else if(timeKeyPressed > 0) {
    if(onRelease != NULL) {
      onRelease(timeKeyPressed);
    }
    timeKeyPressed = 0;
    return true;
  }
  return false;
}

void ButtonApp::setReleaseHandler(releaseHandler handler) {
  onRelease = handler;
}

uint32_t ButtonApp::getHeldDuration() {
  return timeKeyPressed;
}
