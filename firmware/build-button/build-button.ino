
#include <bluefruit.h>

BLEDis bledis;
BLEHidAdafruit blehid;

bool hasKeyPressed = false;

#define PIN_BUTTON   A1

void setup() {
  pinMode(PIN_BUTTON, INPUT_PULLUP);

  Bluefruit.begin();
  Bluefruit.setTxPower(4);
  Bluefruit.setName("Build Button");
  bledis.setManufacturer("Gary Johnson");
  bledis.setModel("Build Button");
  bledis.begin();
  blehid.begin();
  blehid.setKeyboardLedCallback(setKeyboardLed);
  startAdvertising();
}

void loop() {
  if ( hasKeyPressed ) {
    hasKeyPressed = false;
    blehid.keyRelease();
    delay(5);
  }
    
  if ( digitalRead(PIN_BUTTON) == 1 ) {
    blehid.keyboardReport(KEYBOARD_MODIFIER_LEFTCTRL|KEYBOARD_MODIFIER_LEFTALT, HID_KEY_F12);
    hasKeyPressed = true;
    
    delay(500);
  }

  waitForEvent();  
}

void startAdvertising() {  
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

void setKeyboardLed(uint8_t led_bitmap) { }
