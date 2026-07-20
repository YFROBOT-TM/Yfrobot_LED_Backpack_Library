/***************************************************
  YFROBOT 4-digit 7-segment module test
  I2C address: 0x73
  If the display does not respond, run an I2C scan and update DISPLAY_ADDR.
 ****************************************************/

#include "Yfrobot_LEDBackpack.h"

// 当前测试使用的 I2C 地址。
const uint8_t DISPLAY_ADDR = 0x73;  // 临时测试地址

// 创建 4 位数码管对象。
Yfrobot_4bit_7segment display = Yfrobot_4bit_7segment();

void setup() {
  // 初始化串口，方便查看调试信息。
  Serial.begin(9600);

  // 输出启动提示。
  Serial.println("YFROBOT 4-digit 7-segment test");

  // 初始化模块并绑定 I2C 地址。
  display.begin(DISPLAY_ADDR);

  // 设置初始亮度。
  display.setBrightness(15);
}

void loop() {
  // 清空显示内容，刷新到屏幕。
  display.clear();
  display.writeDisplay();
  delay(300);

  // 显示整数。
  display.print(1234);
  display.writeDisplay();
  delay(500);

  // 亮度渐变测试。
  for (uint8_t n = 0; n < 3; n++) {
    for (uint8_t i = 0; i < 16; i++) {
      display.setBrightness(i);
      delay(30);
    }
    for (uint8_t i = 16; i >= 2; i--) {
      display.setBrightness(i);
      delay(30);
    }
  }

  // 显示浮点数12.34，当前会把小数点路由到 D3。
  display.print(12.34, 2);
  display.writeDisplay();
  delay(1200);

  // 显示负数-5.6。
  display.print(-50.6, 1);
  display.writeDisplay();
  delay(1200);

  // 显示十六进制。
  display.print(0x1A2B, HEX);
  display.writeDisplay();
  delay(1200);

  // 逐位写入测试。
  display.clear();
  display.clearDots();
  display.writeDigitNum(0, 4);
  display.writeDigitNum(1, 3);
  display.writeDigitNum(3, 2);
  display.writeDigitNum(4, 1);
  display.drawDotD3(true);
  display.writeDisplay();
  delay(1500);

  // 字符测试。
  display.print("AbCd");
  display.writeDisplay();
  delay(1500);

  // 辅助点位测试。
  display.clear();
  display.clearDots();
  display.drawColon(true);
  display.drawDotD3(true);
  display.drawDotD4(true);
  display.drawDotD5(true);
  display.writeDisplay();
  delay(1500);

  // 时钟风格测试。
  display.clear();
  display.clearDots();
  display.drawColon(true);
  display.writeDigitNum(1, 2);
  display.writeDigitNum(3, 3);
  display.writeDigitNum(4, 4);
  display.writeDisplay();
  delay(1500);

  // 计数测试。
  for (uint16_t counter = 0; counter <= 9999; counter += 1111) {
    display.print(counter);
    display.writeDisplay();
    delay(400);
  }
}
