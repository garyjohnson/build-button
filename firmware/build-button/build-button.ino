#include "LedApp.h"
#include "BleKeyboardApp.h"
#include "ButtonApp.h"

unsigned long previousRunningTime = 0;
unsigned long runningTime = 0;
unsigned long timeSinceLastUpdate = 0;

BleKeyboardApp bleKeyboard = BleKeyboardApp();
ButtonApp button = ButtonApp();
LedApp led = LedApp();

void setup() {
  runningTime = micros();

  button.setup();
  led.setup();
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
  bool buttonKeepRunning = button.update(runTime, updateDelta);

  led.setButtonPressDuration(button.getHeldDuration());

  bool ledKeepRunning = led.update(runTime, updateDelta);

  return buttonKeepRunning || ledKeepRunning;
}

void onButtonRelease(unsigned long holdDuration) {
  unsigned long stageLength = 1000000 / 3;
  if(holdDuration < stageLength) {
    led.startAnimationForStage(0);
    bleKeyboard.sendStage1Key();
  } else if(holdDuration < stageLength*2) {
    led.startAnimationForStage(1);
    bleKeyboard.sendStage2Key();
  } else {
    led.startAnimationForStage(2);
    bleKeyboard.sendStage3Key();
  }
}

