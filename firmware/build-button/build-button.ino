#include "LedApp.h"
#include "BleKeyboardApp.h"
#include "ButtonApp.h"

uint32_t previousRunningTime = 0;
uint32_t runningTime = 0;
uint32_t timeSinceLastUpdate = 0;

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

bool update(uint32_t runTime, uint32_t updateDelta) {
  bool buttonKeepRunning = button.update(runTime, updateDelta);

  led.setButtonPressDuration(button.getHeldDuration());

  bool ledKeepRunning = led.update(runTime, updateDelta);

  return buttonKeepRunning || ledKeepRunning;
}

void onButtonRelease(uint32_t holdDuration) {
  uint32_t stageLength = 1000000 / 3;
  uint8_t stage = min(holdDuration / stageLength, 2);
  led.startAnimationForStage(stage);
  bleKeyboard.sendKeyForStage(stage);
}

