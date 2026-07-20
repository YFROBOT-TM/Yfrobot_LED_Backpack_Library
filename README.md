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
- 4位8段数码管显示(0.28英寸-小数/时钟) :0x74
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

其中 `Yfrobot_4bit_7segment` 示例已经包含：

- 亮度渐变测试
- 整数显示测试
- 浮点数显示测试
- 十六进制显示测试
- 独立点位测试
- 时钟风格显示测试

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