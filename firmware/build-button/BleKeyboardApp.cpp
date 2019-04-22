#include "BleKeyboardApp.h"

BleKeyboardApp::BleKeyboardApp() {
}

BleKeyboardApp::~BleKeyboardApp() {
}

void BleKeyboardApp::setup() {
  initializeBleService();
  startAdvertising();
}

void BleKeyboardApp::sendKeyForStage(uint8_t stage) {
  if(stage > 2) {
    return;
  }

  uint8_t keysForStage[3] = { HID_KEY_6, HID_KEY_7, HID_KEY_8 };
  keycodes[0] = keysForStage[stage];
  blehid.keyboardReport((uint8_t)KEYBOARD_MODIFIER_LEFTALT|KEYBOARD_MODIFIER_LEFTCTRL, keycodes);
  blehid.keyRelease();
}

void BleKeyboardApp::initializeBleService() {
  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Build Button");
  bledis.setManufacturer("Gary Johnson");
  bledis.setModel("Build Button");
  bledis.begin();
  blehid.begin();
}

void BleKeyboardApp::startAdvertising() {  
  Bluefruit.Advertising.addFlags(BLE_GAP_ADV_FLAGS_LE_ONLY_GENERAL_DISC_MODE);
  Bluefruit.Advertising.addTxPower();
  Bluefruit.Advertising.addAppearance(BLE_APPEARANCE_HID_KEYBOARD);
  Bluefruit.Advertising.addService(blehid);
  Bluefruit.Advertising.addName();
  Bluefruit.Advertising.restartOnDisconnect(true);
  Bluefruit.Advertising.setInterval(32, 244);    // in unit of 0.625 ms
  Bluefruit.Advertising.setFastTimeout(30);      // number of seconds in fast mode
  Bluefruit.Advertising.start(0);                // 0 = Don't stop advertising after n seconds
}
