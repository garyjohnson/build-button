#include "LedApp.h"

LedApp::LedApp() {
}

LedApp::~LedApp() {
}

void LedApp::setup() {
  pixels = Adafruit_NeoPixel(NEOPIXEL_COUNT, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);
  pixels.begin();
  pixels.show();
}

bool LedApp::update(uint32_t runTime, uint32_t updateDelta) {
  if(animation >= 0) {
    handleAnimation(runTime, updateDelta);
  } else {
    handleButtonHold(runTime, updateDelta);
  }

  return false;
}

void LedApp::setButtonPressDuration(uint32_t duration) {
  if(buttonPressDuration == 0 && duration > 0) {
    endAnimation();
  }

  buttonPressDuration = duration;
}

void LedApp::startAnimationForStage(unsigned int stage) {
  if(stage >= 3) {
    return;
  }

  animation = stage;
}

void LedApp::handleAnimation(uint32_t runTime, uint32_t updateDelta) {
  animationDuration += updateDelta;

  if(animationDuration >= maxAnimationDuration) {
    endAnimation();
    return;
  }

  unsigned int blinkPhase = animationDuration / blinkDuration;
  bool on = blinkPhase % 2 == 0;
  if(on) {
    pixels.fill(highStages[animation]);
  } else {
    pixels.fill(off);
  }
  pixels.show();
}

void LedApp::handleButtonHold(uint32_t runTime, uint32_t updateDelta) {
  unsigned int maxPixels = (unsigned int)(((float)buttonPressDuration / (float)maxHold) * (NEOPIXEL_COUNT * 3));
  int maxPixel = maxPixels % NEOPIXEL_COUNT;
  int step = min(maxPixels / NEOPIXEL_COUNT, 3);

  if(buttonPressDuration == 0) {
    pixels.fill(off);
    pixels.show();
    return;
  }

  uint32_t currentLowColor = lowStages[step];
  pixels.fill(currentLowColor);

  uint32_t currentHighColor = highStages[step];
  for(int i = 0; i < maxPixel; i++) {
    int pixel = i % NEOPIXEL_COUNT;
    pixels.setPixelColor(pixel, currentHighColor);
  }

  pixels.show();
}

void LedApp::endAnimation() {
  animation = -1;
  animationDuration = 0;
  pixels.fill(off);
  pixels.show();
}
