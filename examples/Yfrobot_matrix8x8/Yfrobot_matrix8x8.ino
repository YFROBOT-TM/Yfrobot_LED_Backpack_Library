/***************************************************
  YFROBOT 8x8 matrix module test
  Assumed address: 0x74
  If the image is rotated, change ROTATION to 0, 1, 2 or 3.
 ****************************************************/

#include "Yfrobot_LEDBackpack.h"

const uint8_t DISPLAY_ADDR = 0x74;
const uint8_t ROTATION = 0;

Yfrobot_8x8matrix matrix = Yfrobot_8x8matrix();

static const uint8_t PROGMEM smile_bmp[] = {
  B00111100,
  B01000010,
  B10100101,
  B10000001,
  B10100101,
  B10011001,
  B01000010,
  B00111100
};

static const uint8_t PROGMEM checker_bmp[] = {
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101,
  B10101010,
  B01010101
};

void setup() {
  Serial.begin(9600);
  Serial.println("YFROBOT 8x8 matrix test");

  matrix.begin(DISPLAY_ADDR);
  matrix.setBrightness(8);
  matrix.setRotation(ROTATION);
  matrix.blinkRate(0);
}

void loop() {
  matrix.clear();
  matrix.drawBitmap(0, 0, checker_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();
  matrix.drawRect(0, 0, 8, 8, LED_ON);
  matrix.drawLine(0, 0, 7, 7, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();
  for (uint8_t i = 0; i < 8; i++) {
    matrix.drawPixel(i, i, LED_ON);
    matrix.drawPixel(7 - i, i, LED_ON);
  }
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1200);

  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setTextColor(LED_ON);

  for (int8_t x = 8; x >= -18; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("8x8");
    matrix.writeDisplay();
    delay(120);
  }
}
