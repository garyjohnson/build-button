#ifndef BLEKEYBOARDAPP_H
#define BLEKEYBOARDAPP_H

#include <bluefruit.h>

class BleKeyboardApp {
  private:
    BLEDis bledis;
    BLEHidAdafruit blehid;
    void initializeBleService();
    void startAdvertising();

  public:
    BleKeyboardApp();
    ~BleKeyboardApp();
    void setup();
    void sendStage1Key();
    void sendStage2Key();
    void sendStage3Key();
};

#endif