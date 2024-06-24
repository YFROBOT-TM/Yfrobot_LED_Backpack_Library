/*************************************************** 
  YFROBOT 12x8 点阵显示模块
    8行 12列点阵
 ****************************************************/

#include "Yfrobot_LEDBackpack.h"

Yfrobot_8x12matrix matrix = Yfrobot_8x12matrix();

int smileyFace[8][12] = {
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0 },
  { 0, 0, 1, 0, 1, 0, 0, 1, 0, 1, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 1, 1, 0, 0, 0, 0, 0 },
  { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 },
};

void setup() {
  Serial.begin(9600);
  Serial.println("16x8 LED Matrix Test");

  matrix.begin(0x70);       // pass in the address
  matrix.setBrightness(1);  // level 0-15
}

static const uint8_t PROGMEM smile_bmp[] = { B00111100,
                                             B01000010,
                                             B10100101,
                                             B10000001,
                                             B10100101,
                                             B10011001,
                                             B01000010,
                                             B00111100 };
static const uint8_t PROGMEM neutral_bmp[] = { B00111100,
                                               B01000010,
                                               B10100101,
                                               B10000001,
                                               B10111101,
                                               B10000001,
                                               B01000010,
                                               B00111100 };
static const uint8_t PROGMEM frown_bmp[] = { B00111100,
                                             B01000010,
                                             B10100101,
                                             B10000001,
                                             B10011001,
                                             B10100101,
                                             B01000010,
                                             B00111100 };

void loop() {

  matrix.clear();
  matrix.setRotation(0);
  matrix.blinkRate(0);
  for (int x = 0; x < 3; x++) {
    for (int i = 0; i <= 15; i++) {
      matrix.setBrightness(i);  // level 0-15
      draw8x12Matrix(0, 0, smileyFace);
      //   draw8x12Matrix(2, 5, smileyFace);
      matrix.writeDisplay();
      delay(30);
    }

    for (int i = 15; i >= 0; i--) {
      matrix.setBrightness(i);  // level 0-15
      draw8x12Matrix(0, 0, smileyFace);
      //   draw8x12Matrix(2, 5, smileyFace);
      matrix.writeDisplay();
      delay(30);
    }
  }


  matrix.setRotation(1);
  matrix.blinkRate(1);
  matrix.clear();
  matrix.drawBitmap(4, 2, smile_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);
  matrix.clear();
  matrix.drawBitmap(8, 0, neutral_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);
  matrix.clear();
  matrix.drawBitmap(2, 1, frown_bmp, 8, 8, LED_ON);
  matrix.writeDisplay();
  delay(1000);

  matrix.clear();  // clear display
  matrix.setRotation(0);
  matrix.blinkRate(0);
  matrix.drawPixel(0, 15, LED_ON);
  matrix.drawPixel(1, 14, LED_ON);
  matrix.drawPixel(2, 13, LED_ON);
  matrix.drawPixel(3, 12, LED_ON);
  matrix.drawPixel(4, 11, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(1500);

  matrix.clear();
  matrix.drawLine(0, 0, 7, 15, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawRect(0, 0, 8, 16, LED_ON);
  matrix.fillRect(2, 2, 4, 12, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawCircle(3, 8, 3, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.fillCircle(3, 8, 3, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawTriangle(0, 0, 6, 1, 4, 14, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);
  matrix.clear();
  matrix.fillTriangle(0, 0, 6, 1, 4, 14, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.clear();
  matrix.drawRoundRect(0, 0, 8, 16, 2, LED_ON);
  matrix.fillRoundRect(2, 2, 4, 12, 2, LED_ON);
  matrix.writeDisplay();  // write the changes we just made to the display
  delay(500);

  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);

  int inttext = 100;
  for (int y = 0; y < 3; y++) {
    String str_text = String(inttext);
    int l = str_text.length() * 5 + 5;
    for (int8_t x = 7; x >= -l; x--) {
      matrix.clear();
      matrix.setCursor(x, 0);
      matrix.print(str_text);
      matrix.writeDisplay();
      delay(50);
    }
    inttext--;
  }

  matrix.setTextSize(1);
  matrix.setTextWrap(false);  // we dont want text to wrap so it scrolls nicely
  matrix.setTextColor(LED_ON);
  matrix.setRotation(1);
  for (int8_t x = 7; x >= -60; x--) {
    matrix.clear();
    matrix.setCursor(x, 0);
    matrix.print("Hello World!");
    // matrix.print("Hello 8x16 matrix");
    matrix.writeDisplay();
    delay(100);
  }
}

/**
 * 在点阵屏幕上绘制一个8x12 8行12列像素的图案。
 * 
 * @param x 图案左上角在点阵屏幕上的x坐标。
 * @param y 图案左上角在点阵屏幕上的y坐标。
 * @param yf_bitmap 一个二维数组，包含笑脸图案的像素数据。
 * 
 * 该函数通过遍历笑脸图案的二维数组，将每个非零像素绘制到点阵屏幕上。
 * 通过调整x和y参数，可以在点阵屏幕上的任意位置显示图案。
 */
void draw8x12Matrix(int16_t x, int16_t y, const int yf_bitmap[8][12]) {
  matrix.startWrite();  // 开始点阵屏幕的批量写操作，可以提高绘制效率。

  for (int16_t row = 7; row >= 0 + x; row--) {           // 从数组的顶部开始遍历每一行，直到达到显示区域的顶部。
    for (int16_t col = 0; col < 12 - y; col++) {         // 从数组的左侧开始遍历每一列，直到达到显示区域的右侧。
      if (yf_bitmap[row][col] != 0) {                    // 如果当前像素的值不为0，则表示该像素应被点亮。
        matrix.drawPixel(7 - row + x, col + y, LED_ON);  // 计算像素在点阵屏幕上的实际位置，并点亮该像素。
      }
    }
  }
  matrix.endWrite();  // 结束点阵屏幕的批量写操作。
}