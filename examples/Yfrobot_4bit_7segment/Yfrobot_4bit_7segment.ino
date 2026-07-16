/***************************************************
  YFROBOT 4-digit 7-segment module test
  Assumed address: 0x72
  If the display does not respond, run an I2C scan and update DISPLAY_ADDR.
 ****************************************************/

#include "Yfrobot_LEDBackpack.h"

// 数码管模块当前测试使用的 I2C 地址。
const uint8_t DISPLAY_ADDR = 0x73;  // 临时测试地址

// 创建一个 4 位数码管显示对象，后续所有显示操作都通过它完成。
Yfrobot_4bit_7segment display = Yfrobot_4bit_7segment();

void setup() {
  Serial.begin(9600);                                // 初始化串口，方便在串口监视器中查看调试信息。
  Serial.println("YFROBOT 4-digit 7-segment test");  // 输出当前示例启动提示。

  display.begin(DISPLAY_ADDR);  // 初始化数码管模块，并绑定对应的 I2C 地址。
  display.setBrightness(15);    // 设置亮度，范围 0~15，15 为最亮。
}

void loop() {
  display.clear();  // 清空显示缓冲区中的所有数字和点位。
  // display.writeDisplay();  // 把缓冲区内容真正刷新到数码管上。
  delay(300);

  display.print(8888);     // 以十进制方式显示整数 8888。
  display.writeDisplay();  // 刷新显示，让新亮度和新内容生效。
  for (uint8_t n = 0; n < 3; n++) {
    // 亮度渐变测试：从最暗逐步调到最亮。
    for (uint8_t i = 0; i < 16; i++) {
      display.setBrightness(i);  // 动态设置当前亮度等级。
      delay(30);
    }
    // 亮度渐变测试：从最亮逐步调到亮度2。
    for (uint8_t i = 16; i >= 2; i--) {
      display.setBrightness(i);  // 动态设置当前亮度等级。
      delay(30);
    }
  }

  display.print(1234);     // 直接显示一个 4 位整数。
  display.writeDisplay();  // 将整数内容刷新到数码管。
  delay(1200);

  display.print(12.34, 2);  // 显示浮点数，并保留 2 位小数。
  display.writeDisplay();   // 刷新显示浮点结果。
  delay(1200);

  display.print(-5.6, 1);  // 显示负数，并保留 1 位小数。
  display.writeDisplay();  // 刷新显示负数结果。
  delay(1200);

  display.print(0x1A2B, HEX);  // 按十六进制方式显示 1A2B。
  display.writeDisplay();      // 刷新显示十六进制结果。
  delay(1200);

  // 逐位写入测试：手动控制每一位数字和指定位置的小数点。
  display.clear();                    // 先清空缓冲区，避免前一段内容残留。
  display.writeDigitNum(0, 1);        // 在第 1 位写入数字 1。
  display.writeDigitNum(1, 2, true);  // 在第 2 位写入数字 2，并点亮该位附带的小数点位。
  display.writeDigitNum(3, 3);        // 在第 3 位写入数字 3。
  display.writeDigitNum(4, 4);        // 在第 4 位写入数字 4。
  display.writeDisplay();             // 刷新显示逐位写入结果。
  delay(1500);

  display.print("AbCd");   // 直接显示字符串，用于测试字母段码。
  display.writeDisplay();  // 刷新显示字符串结果。
  delay(1500);

  // 点位测试：单独点亮时钟点和 D3/D4/D5。
  display.clear();          // 清空主显示区内容。
  display.clearDots();      // 清除所有辅助点位，确保本次测试从全灭开始。
  display.drawColon(true);  // 点亮中间时钟点 D1+D2。
  display.drawDotD3(true);  // 点亮 D3 点位。
  display.drawDotD4(true);  // 点亮 D4 点位。
  display.drawDotD5(true);  // 点亮 D5 点位。
  display.writeDisplay();   // 刷新显示点位测试结果。
  delay(1500);

  // 时钟风格测试：保留中间时钟点，再显示右侧数字。
  display.clear();              // 清空数字显示内容。
  display.clearDots();          // 先关闭所有辅助点位。
  display.drawColon(true);      // 重新点亮中间时钟点。
  display.writeDigitNum(1, 2);  // 在第 2 位显示数字 2。
  display.writeDigitNum(3, 3);  // 在第 3 位显示数字 3。
  display.writeDigitNum(4, 4);  // 在第 4 位显示数字 4。
  display.writeDisplay();       // 刷新显示，观察“时钟点 + 数字”的组合效果。
  delay(1500);

  // 计数测试：循环显示多个整数，观察动态刷新是否稳定。
  for (uint16_t counter = 0; counter <= 9999; counter += 1111) {
    display.print(counter);  // 显示当前计数值。
    display.writeDisplay();  // 刷新数码管。
    delay(800);
  }
}
