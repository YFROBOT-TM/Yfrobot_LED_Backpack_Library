/***************************************************
  YFROBOT 8x8 matrix module test
  I2C address: 0x72
  Confirmed forward rotation: 0
  If the image is rotated, change ROTATION to 0, 1, 2 or 3.
 ****************************************************/

#include "Yfrobot_LEDBackpack.h"

const uint8_t DISPLAY_ADDR = 0x72;
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

static const uint8_t PROGMEM arrow_right_bmp[] = {
  B00011000,
  B00011100,
  B11111110,
  B11111111,
  B11111110,
  B00011100,
  B00011000,
  B00010000
};

static const uint8_t PROGMEM heart_bmp[] = {
  B01100110,
  B11111111,
  B11111111,
  B11111111,
  B01111110,
  B00111100,
  B00011000,
  B00000000
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
  // 逐列扫描，确认第 0 列不会跑到最右侧。
  for (uint8_t x = 0; x < 8; x++) {
    matrix.clear();
    matrix.drawLine(x, 0, x, 7, LED_ON);
    matrix.writeDisplay();
    delay(220);
  }

  matrix.clear();
  matrix.drawRect(0, 0, 8, 8, LED_ON);
  matrix.drawLine(0, 0, 7, 7, LED_ON);
  matrix.drawLine(7, 0, 0, 7, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();
  matrix.drawBitmap(0, 0, arrow_right_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();
  matrix.drawBitmap(0, 0, heart_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1200);

  matrix.setTextSize(1);
  matrix.setTextWrap(false);
  matrix.setTextColor(LED_ON);

  for (int8_t x = 8; x >= -12; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("yfrobot");
    matrix.writeDisplay();
    delay(120);
  }
}
