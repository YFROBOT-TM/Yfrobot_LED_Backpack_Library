/*************************************************** 
YFROBOT 10位 条状显示模块
 ****************************************************/

#include "Yfrobot_LEDBackpack.h"

Yfrobot_10bargraph bar = Yfrobot_10bargraph();

void setup() {
  Serial.begin(9600);
  Serial.println("HT16K33 Bi-Color Bargraph test");
  bar.begin(0x70);  // pass in the address
}


void loop() {
  bar.setBrightness(15);  // level 0-15

  for (int8_t b = 0; b < 10; b++) {
    bar.setBar(b);
    bar.writeDisplay();
    delay(100);
  }

  for (int x = 0; x < 5; x++) {
    bar.setBrightness(15);  // level 0-15
    delay(200);
    bar.setBrightness(0);  // level 0-15
    delay(200);
  }

  for (int8_t k = 9; k >= 0; k--) {
    bar.clearBar(k);
    bar.writeDisplay();
    delay(100);
  }
}