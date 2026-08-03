# Yfrobot LED Backpack Library
采购：
https://item.taobao.com/item.htm?id=852903003324
https://item.taobao.com/item.htm?id=850469423617
https://item.taobao.com/item.htm?id=853026121301



## 库简介

`Yfrobot_LED_Backpack_Library` 是 YFROBOT 用于 `16K33` 系列 LED 显示模块的 Arduino 驱动库。
支持的显示模块包括：
- 3位 8段数码管显示
- 3位 温湿度数码管显示(特别定制款)
- 10段条状 LED 显示
- 12列X8行 单色点阵显示(多色可选)
- 4位8段数码管显示(0.28英寸-小数/时钟)
- 8X8 单色点阵显示

### I2C 地址
默认 I2C，不同的模块地址不同，使用前建议先确认模块地址。
- 3位 8段数码管显示 :0X73
- 3位 温湿度数码管显示 :0X77 (特别定制款)
- 10段条状 LED 显示 :0x70
- 12列X8行 单色点阵显示(多色可选) :0x71
- 4位8段数码管显示(0.28英寸-小数/时钟) :0x75
- 8X8 单色点阵显示 :0x72

---

## 基本功能

本库已提供以下常用能力：

- 初始化显示模块
- 设置 I2C 地址
- 设置显示亮度
- 显示整数、浮点数、十六进制数
- 逐位写入数字或字符
- 控制独立辅助点位
- 绘制单色点阵图形与文字

亮度范围：

- `0 ~ 15`
- `0` 为最暗
- `15` 为最亮

---

## 使用示例

库中已提供示例程序，可直接参考：

- `examples/Yfrobot_3bit_sevenseg/`
- `examples/Yfrobot_bargraph10/`
- `examples/Yfrobot_matrix12x8/`
- `examples/Yfrobot_4bit_7segment/`
- `examples/Yfrobot_matrix8x8/`

### API
#### 1. 通用基础 API
以下接口适用于所有继承 `Yfrobot_LEDBackpack` 的显示模块。

- `begin(uint8_t addr = 0x70, TwoWire *theWire = &Wire)`：初始化 I2C 设备，设置模块地址和 I2C 总线，返回 `true / false`。
- `setDisplayState(bool state)`：打开或关闭显示。
- `setBrightness(uint8_t b)`：设置亮度，范围 `0 ~ 15`，`0` 最暗，`15` 最亮。
- `blinkRate(uint8_t b)`：设置闪烁频率，可选 `HT16K33_BLINK_OFF / HT16K33_BLINK_2HZ / HT16K33_BLINK_1HZ / HT16K33_BLINK_HALFHZ`。
- `clear(void)`：清空显示缓冲区，不会自动上屏。
- `writeDisplay(void)`：把当前缓冲内容刷新到硬件。

建议调用顺序：

- 先 `begin()`。
- 再设置 `setBrightness()` 或 `blinkRate()`。
- 修改显示内容后，最后调用 `writeDisplay()`。

#### 2. 10段条状显示模块 API

##### `Yfrobot_10bargraph`

- `setBar(uint8_t bar)`：点亮第 `0 ~ 9` 段。
- `clearBar(uint8_t bar)`：熄灭指定段。
- 设置完成后调用 `writeDisplay()` 刷新。

#### 3. 12列x8行点阵显示模块 API
以下点阵类继承 `Adafruit_GFX`，除了 `drawPixel()` 之外，还可以直接使用 `drawLine()`、`drawRect()`、`fillRect()`、`drawChar()`、`setCursor()`、`print()`、`setTextSize()`、`setTextColor()`、`setRotation()` 等图形接口。

##### `Yfrobot_8x12matrix`

- `drawPixel(int16_t x, int16_t y, uint16_t color)`：设置单个像素。
- 绘图完成后调用 `writeDisplay()` 刷新。

#### 4. 3位数码管显示模块 API

##### `Yfrobot_3bit_7segment`

- `write(char c)`：写入单个 ASCII 字符，按当前光标位置顺序显示。
- `write(const char *buffer, size_t size)`：按字符串缓冲顺序显示。
- `print(char c)`：显示单个字符。
- `print(int / unsigned int / long / unsigned long / double / String / const char[])`：显示整数、浮点数或字符串。
- `writeDigitRaw(uint8_t x, uint8_t bitmask)`：按原始段码写入指定位。
- `writeDigitNum(uint8_t x, uint8_t num, bool dot = false)`：写入数字 `0 ~ 9`，也支持 `A ~ F`。
- `writeDigitAscii(uint8_t x, uint8_t c, bool dot = false)`：写入 ASCII 字符。
- `drawColon(bool state)`：控制中间冒号点。
- `writeColon(void)`：刷新当前冒号状态到屏幕。
- `printNumber(long n, uint8_t base = 2)`：整数格式化辅助函数。
- `printFloat(double n, uint8_t fracDigits = 2, uint8_t base = DEC)`：浮点数格式化辅助函数。
- `printError(void)`：显示错误/溢出状态。

##### `Yfrobot_3bit_7segment_tb`

- `write(char c)`：写入单个 ASCII 字符。
- `write(const char *buffer, size_t size)`：写入字符串缓冲。
- `print(double n, int digits = 1)`：显示浮点数，默认保留 1 位小数。
- `writeDigitRaw(uint8_t x, uint8_t bitmask)`：按原始段码写入指定位。
- `writeDigitNum(uint8_t x, uint8_t num, bool dot = false)`：写入数字 `0 ~ 9`，也支持 `A ~ F`。
- `writeDigitAscii(uint8_t x, uint8_t c, bool dot = false)`：写入 ASCII 字符。
- `drawColon(bool state)`：控制冒号点。
- `writeColon(uint8_t tb)`：刷新冒号/状态显示。
- `printFloat(double n, uint8_t fracDigits = 1, uint8_t base = DEC)`：浮点数格式化辅助函数。
- `printError(void)`：显示错误/溢出状态。

#### 5. 4位数码管显示模块 API

##### `Yfrobot_4bit_7segment`

- `write(char c)`：写入单个 ASCII 字符，按当前光标位置顺序显示。
- `write(const char *buffer, size_t size)`：按字符串缓冲顺序显示。
- `print(char c)`：显示单个字符。
- `print(int / unsigned int / long / unsigned long / double / String / const char[])`：显示整数、浮点数或字符串。
- `writeDigitRaw(uint8_t x, uint8_t bitmask)`：按原始段码写入指定位。
- `writeDigitNum(uint8_t x, uint8_t num, bool dot = false)`：写入数字 `0 ~ 9`，也支持 `A ~ F`。
- `writeDigitAscii(uint8_t x, uint8_t c, bool dot = false)`：写入 ASCII 字符。
- `drawColon(bool state)`：控制 `D1 + D2` 中间时钟点。
- `drawDotD3(bool state)`：控制 `D3`。
- `drawDotD4(bool state)`：控制 `D4`。
- `drawDotD5(bool state)`：控制 `D5`。
- `clearDots(void)`：清除全部辅助点位。
- `showClock(uint8_t hour, uint8_t minute, uint8_t second = 0, ClockDotMode dotMode = CLOCK_DOTS_ON, bool leadingZero = true)`：RTC 时钟专用接口，用于显示 `HH:MM`。
- `ClockDotMode` 取值为 `CLOCK_DOTS_OFF / CLOCK_DOTS_ON / CLOCK_DOTS_BLINK`。
- `writeColon(void)`：刷新当前时钟点状态到屏幕。
- `printNumber(long n, uint8_t base = 2)`：整数格式化辅助函数，一般直接用 `print()` 即可。
- `printFloat(double n, uint8_t fracDigits = 2, uint8_t base = DEC)`：浮点数格式化辅助函数。
- `printError(void)`：显示错误/溢出状态。

4 位数码管建议写法：

- 显示普通数字时，用 `print()`。
- 需要手动控制点位时，用 `drawColon()`、`drawDotD3()`、`drawDotD4()`、`drawDotD5()`。
- 读取 RTC 的小时和分钟后，优先用 `showClock()`，不要再手动拼 `drawColon()`。

#### 6. 8x8点阵显示模块 API
以下点阵类继承 `Adafruit_GFX`，除了 `drawPixel()` 之外，还可以直接使用 `drawLine()`、`drawRect()`、`fillRect()`、`drawChar()`、`setCursor()`、`print()`、`setTextSize()`、`setTextColor()`、`setRotation()` 等图形接口。

##### `Yfrobot_8x8matrix`

- 这是对 `Adafruit_8x8matrix` 的 YFROBOT 封装，保留 `setRotation(0 / 1 / 2 / 3)` 等图形 API。
- 当前模块默认 I2C 地址为 `0x72`，实测正方向推荐使用 `setRotation(0)`。
- `drawPixel(int16_t x, int16_t y, uint16_t color)`：设置单个像素，`color` 通常用 `0 / 1`。
- `fillScreen(uint16_t color)`：快速点亮或熄灭整屏，适合做整屏测试、清屏测试或全屏提示。
- `scrollMessage(const String &s, int displayScrollSpeed = 300)`：让字符串从右向左自动滚动显示，第二个参数是滚动速度，单位毫秒。
- `scrollMessage(int num, int displayScrollSpeed = 300)`：把整数转成字符串后滚动显示。
- `scrollMessage(float num, int displayScrollSpeed = 300)`：把浮点数转成字符串后滚动显示。
- 绘图完成后调用 `writeDisplay()` 刷新。

### 说明与建议

- 当前 4 位数码管模块的辅助点位为非标准布局
- `D1 + D2` 为中间时钟点
- `D3 / D4 / D5` 为独立辅助点位(小数点)
- 因此在该模块上，建议优先使用显式点位接口进行控制：
  - `drawColon()`
  - `drawDotD3()`
  - `drawDotD4()`
  - `drawDotD5()`
  - `clearDots()`

---

## 测试
| 测试主控 | 测试结果 |
|----------|----------|
| arduino UNO R3 | 成功 |
| ESP32 | 成功 |

---
## 更新日志
- V0.0.6: 修改4位数码管显示模块默认地址为0x75（0x74与超声波09默认地址冲突）
- V0.0.5: 新增8X8单色点阵显示 滚动显示API；
- V0.0.4: 修复8X8单色点阵显示驱动程序；
- V0.0.3: 新增4位8段数码管显示模块 时钟模式下显示功能；
- V0.0.2: 更新支持4位8段数码管显示模块、8X8 单色点阵显示模块；
- V0.0.1: 初始版本，支持3位7段数码管显示模块、10位条状显示模块、8x12（8行12列）LED Matrix 显示模块、3位7段温湿度数码管显示模块。

---
## 许可
本库采用 MIT 许可协议。详情请参阅 LICENSE 文件。

---
## 支持

如有任何问题或建议，请联系 YFROBOT 技术支持：
- 官方网站: [https://www.yfrobot.com/](https://www.yfrobot.com/)
- 淘宝店铺: [https://yfrobot.taobao.com/](https://yfrobot.taobao.com/)

---
## 致谢
本库基于 Adafruit 相关开源项目进行适配与扩展，感谢 Adafruit 社区提供的优秀基础实现。
参考项目：- [Adafruit LED Backpack Library](https://github.com/adafruit/Adafruit_LED_Backpack)

---
**YFROBOT** - 让创新更简单
