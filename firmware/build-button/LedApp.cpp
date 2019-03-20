#include "LedApp.h"

LedApp::LedApp() {
}

LedApp::~LedApp() {
}

void LedApp::setup() {
  pixels = Adafruit_NeoPixel(NEOPIXEL_COUNT, PIN_NEOPIXEL, NEO_GRB + NEO_KHZ800);

  off = pixels.Color(0,0,0);
  lowStage1 = pixels.Color(0,0,10);
  highStage1 = pixels.Color(0,0,255);
  highStage2 = pixels.Color(255,0,128);
  highStage3 = pixels.Color(255,0,0);

  currentLowColor = 0;
  currentHighColor = 0;

  maxHold = 1000000;

  buttonPressDuration = 0;

  pixels.begin(); 
  pixels.show(); 
}

bool LedApp::update(unsigned long runTime, unsigned long updateDelta) {
  unsigned int maxPixels = (unsigned int)(((float)buttonPressDuration / (float)maxHold) * (NEOPIXEL_COUNT * 3));
  int maxPixel = maxPixels % NEOPIXEL_COUNT;
  int step = maxPixels / NEOPIXEL_COUNT;

  if(buttonPressDuration == 0) {
    for(int i = 0; i < NEOPIXEL_COUNT; i++) {
      pixels.setPixelColor(i, off);
    }
    pixels.show();
    return false;
  }

  if(step >= 3) {
    for(int i = 0; i < NEOPIXEL_COUNT; i++) {
      pixels.setPixelColor(i, highStage3);
    }
    pixels.show();
    return false;
  }

  // fill in the bright pixels
  for(int i = 0; i < maxPixels; i++) {
    int pixel = i % NEOPIXEL_COUNT;
    if(i < NEOPIXEL_COUNT) {
      currentHighColor = highStage1;
    } else if(i < (NEOPIXEL_COUNT*2)) {
      currentHighColor = highStage2;
    } else if(i < (NEOPIXEL_COUNT*3)) {
      currentHighColor = highStage3;
    }
    pixels.setPixelColor(pixel, currentHighColor);
  }

  // fill in the background pixels
  if(step == 0) {
    currentLowColor = lowStage1;
  } else if(step == 1) {
    currentLowColor = highStage1;
  } else if(step == 2) {
    currentLowColor = highStage2;
  }
  for(int i = maxPixel; i < NEOPIXEL_COUNT; i++) {
    pixels.setPixelColor(i, currentLowColor);
  }
  pixels.show();
  return false;
}

void LedApp::setButtonPressDuration(unsigned long duration) {
  buttonPressDuration = duration;
}
