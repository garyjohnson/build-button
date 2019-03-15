#include "LedApp.h"
#include "BleKeyboardApp.h"
#include "ButtonApp.h"

unsigned long previousRunningTime = 0;
unsigned long runningTime = 0;
unsigned long timeSinceLastUpdate = 0;

BleKeyboardApp bleKeyboard = BleKeyboardApp();
ButtonApp button = ButtonApp();

void setup() {
  runningTime = micros();

  button.setup();
  bleKeyboard.setup();

  button.setReleaseHandler(onButtonRelease);
}

void loop() {
  do {
    previousRunningTime = runningTime;
    runningTime = micros();
    timeSinceLastUpdate = runningTime - previousRunningTime;
  } while(update(runningTime, timeSinceLastUpdate));

  waitForEvent();  
}

bool update(unsigned long runTime, unsigned long updateDelta) {
  return button.update(runTime, updateDelta);
}

void onButtonRelease(unsigned long holdDuration) {
  unsigned long stageLength = 1000000 / 3;
  if(holdDuration < stageLength) {
    bleKeyboard.sendStage1Key();
  } else if(holdDuration < stageLength*2) {
    bleKeyboard.sendStage2Key();
  } else {
    bleKeyboard.sendStage3Key();
  }
}

