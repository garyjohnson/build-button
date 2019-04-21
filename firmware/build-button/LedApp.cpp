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

bool LedApp::update(unsigned long runTime, unsigned long updateDelta) {
  if(animation >= 0) {
    handleAnimation(runTime, updateDelta);
  } else {
    handleButtonHold(runTime, updateDelta);
  }

  return false;
}

void LedApp::setButtonPressDuration(unsigned long duration) {
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

void LedApp::handleAnimation(unsigned long runTime, unsigned long updateDelta) {
  animationDuration += updateDelta;

  if(animationDuration >= maxAnimationDuration) {
    endAnimation();
    return;
  }

  unsigned int blinkPhase = animationDuration / blinkDuration;
  bool on = blinkPhase % 2 == 0;

  unsigned long color = off;
  if(on) {
    color = highStages[animation];
  }
  pixels.fill(color);
  pixels.show();
}

void LedApp::handleButtonHold(unsigned long runTime, unsigned long updateDelta) {
  unsigned int maxPixels = (unsigned int)(((float)buttonPressDuration / (float)maxHold) * (NEOPIXEL_COUNT * 3));
  int maxPixel = maxPixels % NEOPIXEL_COUNT;
  int step = maxPixels / NEOPIXEL_COUNT;

  if(buttonPressDuration == 0) {
    pixels.fill(off);
    pixels.show();
    return;
  }

  if(step >= 3) {
    pixels.fill(highStages[2]);
    pixels.show();
    return;
  }

  // fill in the bright pixels
  for(int i = 0; i < maxPixels; i++) {
    int pixel = i % NEOPIXEL_COUNT;
    if(i < NEOPIXEL_COUNT) {
      currentHighColor = highStages[0];
    } else if(i < (NEOPIXEL_COUNT*2)) {
      currentHighColor = highStages[1];
    } else if(i < (NEOPIXEL_COUNT*3)) {
      currentHighColor = highStages[2];
    }
    pixels.setPixelColor(pixel, currentHighColor);
  }

  // fill in the background pixels
  if(step == 0) {
    currentLowColor = lowStages[0];
  } else if(step == 1) {
    currentLowColor = lowStages[1];
  } else if(step == 2) {
    currentLowColor = lowStages[2];
  }
  for(int i = maxPixel; i < NEOPIXEL_COUNT; i++) {
    pixels.setPixelColor(i, currentLowColor);
  }
  pixels.show();
}

void LedApp::endAnimation() {
  animation = -1;
  animationDuration = 0;
  pixels.fill(off);
  pixels.show();
}
