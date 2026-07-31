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
  B00000000
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
  // 初始化串口，方便在串口监视器里查看测试提示信息。
  Serial.begin(9600);
  // 输出示例名称，便于确认当前烧录的是哪一个测试程序。
  Serial.println("YFROBOT 8x8 matrix test");

  // 初始化 8x8 点阵模块，并指定默认 I2C 地址 0x72。
  matrix.begin(DISPLAY_ADDR);
  // 设置点阵亮度，取值范围 0~15，数值越大显示越亮。
  matrix.setBrightness(2);
  // 设置显示方向；当前硬件正方向已确认是 rotation=0。
  matrix.setRotation(ROTATION);
  // 关闭芯片自带闪烁功能，避免影响图案观察。
  matrix.blinkRate(0);
}

void loop() {
  // 逐列扫描，确认第 0 列不会跑到最右侧。
  for (uint8_t x = 0; x < 8; x++) {
    // 清空显示缓冲区，准备绘制下一组测试图案。
    matrix.clear();
    // 绘制一条竖线，用于确认列顺序是否从左到右正常。
    matrix.drawLine(x, 0, x, 7, LED_ON);
    // 把当前缓冲区内容刷新到屏幕上，真正显示出来。
    matrix.writeDisplay();
    delay(220);
  }

  // 调用 fillScreen(LED_ON) 点亮整屏，用于确认全部像素是否都能正常显示。
  matrix.fillScreen(LED_ON);
  // 将整屏点亮效果刷新到点阵模块。
  matrix.writeDisplay();
  delay(500);

  // 调用 fillScreen(LED_OFF) 熄灭整屏，用于确认整屏清空是否正常。
  matrix.fillScreen(LED_OFF);
  // 将整屏熄灭效果刷新到点阵模块。
  matrix.writeDisplay();
  delay(300);

  // 清空显示缓冲区，准备绘制边框与对角线。
  matrix.clear();
  // 绘制 8x8 外边框，用于检查四周边界是否完整。
  matrix.drawRect(0, 0, 8, 8, LED_ON);
  // 绘制左上到右下对角线，用于确认斜线方向。
  matrix.drawLine(0, 0, 7, 7, LED_ON);
  // 绘制右上到左下对角线，用于确认另一条斜线方向。
  matrix.drawLine(7, 0, 0, 7, LED_ON);
  // 将边框与对角线刷新到点阵模块。
  matrix.writeDisplay();
  delay(1000);

  // 清空显示缓冲区，准备显示右箭头位图。
  matrix.clear();
  // 根据位图数组绘制右箭头，便于观察方向感是否正确。
  matrix.drawBitmap(0, 0, arrow_right_bmp, 8, 8, LED_ON);
  // 刷新箭头图案到屏幕。
  matrix.writeDisplay();
  delay(1000);

  // 清空显示缓冲区，准备显示爱心位图。
  matrix.clear();
  // 根据位图数组绘制爱心，便于观察整体轮廓是否完整。
  matrix.drawBitmap(0, 0, heart_bmp, 8, 8, LED_ON);
  // 刷新爱心图案到屏幕。
  matrix.writeDisplay();
  delay(1000);

  // 清空显示缓冲区，准备显示笑脸位图。
  matrix.clear();
  // 根据位图数组绘制笑脸，用于观察是否还有错列或缺列现象。
  matrix.drawBitmap(0, 0, smile_bmp, 8, 8, LED_ON);
  // 刷新笑脸图案到屏幕。
  matrix.writeDisplay();
  delay(1200);

  // 调用库内 scrollMessage() 接口，让字符串自动从右向左滚动显示。
  // 第二个参数为滚动速度，单位毫秒，数值越小滚动越快。
  matrix.scrollMessage("yfrobot", 120);

  // 调用库内 scrollMessage() 接口，让数字自动从右向左滚动显示。
  // 第二个参数为滚动速度，单位毫秒，数值越小滚动越快。
  matrix.scrollMessage((float)125.56, 40);
}
