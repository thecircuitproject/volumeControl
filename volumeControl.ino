/*
HID-Project must be version 2.8.2
*/

#include "HID-Project.h"

#define CLK 0
#define DT 5
#define SW 6
const int tab = 7;
const int prev = 3;
const int close = 2;
unsigned long lastButtonPress = 0;
unsigned long lastRun = 0;

void setup() {
  pinMode(CLK, INPUT);
  pinMode(DT, INPUT);
  pinMode(SW, INPUT_PULLUP);
  pinMode(tab, INPUT);
  pinMode(prev, INPUT);
  pinMode(close, INPUT);

  attachInterrupt(digitalPinToInterrupt(tab), newTab, RISING);
  attachInterrupt(digitalPinToInterrupt(prev), prevTab, RISING);
  attachInterrupt(digitalPinToInterrupt(close), closeTab, RISING);
  attachInterrupt(digitalPinToInterrupt(CLK), volumeControl, LOW);

  Serial.begin(9600);
  Keyboard.begin();
}

void loop() {
  int btnState = digitalRead(SW);  // Button Value

  if (btnState == LOW) {  // Switch pushed

    if (millis() - lastButtonPress > 50) {  // Over 50ms
      Consumer.write(MEDIA_VOLUME_MUTE);
    }
    lastButtonPress = millis();
  }

  delay(1);  // Push swithc delay
}

void newTab() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(0b01110100);
  //delay(200)
  Keyboard.releaseAll();
}

void prevTab() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(0b01010100);
  //delay(200);
  Keyboard.releaseAll();
}

void closeTab() {
  Keyboard.press(KEY_LEFT_CTRL);
  Keyboard.press(0b01110111);
  //delay(200);
  Keyboard.releaseAll();
}

void volumeControl() {
  if (millis() - lastRun > 5) {
    if (digitalRead(DT) == 1) {         
      Consumer.write(MEDIA_VOLUME_DOWN); 
      delay(2);

    } else {                         
      Consumer.write(MEDIA_VOLUME_UP); 
      delay(2);
    }
  }
  lastRun = millis();
}
