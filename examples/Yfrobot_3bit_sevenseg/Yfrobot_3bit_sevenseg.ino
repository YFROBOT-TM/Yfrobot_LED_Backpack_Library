/*************************************************** 
YFROBOT 3位7段数码管显示模块
 ****************************************************/

#include "Yfrobot_LEDBackpack.h"

Yfrobot_3bit_7segment matrix = Yfrobot_3bit_7segment();

void setup() {
  Serial.begin(9600);
  Serial.println("3BIT 7 Segment Backpack Test");
  matrix.begin(0x70);
  matrix.setBrightness(1);  // level 0-15
}

void loop() {
  // try to print a number thats too long
  matrix.print(121, DEC);
  matrix.writeDisplay();
  delay(1500);

  // print a hex number
  matrix.print(0x4AE, HEX);
  matrix.writeDisplay();
  delay(1500);

  // print a floating point
  matrix.print(13.1);
  matrix.writeDisplay();
  delay(1500);
  // print a floating point
  matrix.print(3.1);
  matrix.writeDisplay();
  delay(1500);
  // print a floating point
  matrix.print(131.2);
  matrix.writeDisplay();
  delay(1500);

  // print a string message
  matrix.print("SEG");
  matrix.writeDisplay();
  delay(1000);

  // print
  for (uint16_t counter = 0; counter < 999; counter+=111) {
    matrix.print(counter);
    matrix.writeDisplay();
    delay(500);
  }

  // method #2 - draw each digit
  uint16_t blinkcounter = 0;
  boolean drawDots = false;
  for (uint16_t counter = 0; counter < 999; counter+=111) {
    matrix.writeDigitNum(0, (counter / 100), drawDots);
    matrix.writeDigitNum(1, (counter / 10) % 10, drawDots);
    matrix.writeDigitNum(3, counter  % 10, drawDots);

    blinkcounter+=50;
    if (blinkcounter < 500) {
      drawDots = false;
    } else if (blinkcounter < 1000) {
      drawDots = true;
    } else {
      blinkcounter = 0;
    }
    matrix.writeDisplay();
    delay(500);
  }
}
