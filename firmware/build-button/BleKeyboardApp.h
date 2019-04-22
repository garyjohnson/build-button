#ifndef BLEKEYBOARDAPP_H
#define BLEKEYBOARDAPP_H

#include <bluefruit.h>

class BleKeyboardApp {
  private:
    uint8_t keycodes[6] = { 0 };
    BLEDis bledis;
    BLEHidAdafruit blehid;
    void initializeBleService();
    void startAdvertising();

  public:
    BleKeyboardApp();
    ~BleKeyboardApp();
    void setup();
    void sendKeyForStage(uint8_t stage);
};

#endif
