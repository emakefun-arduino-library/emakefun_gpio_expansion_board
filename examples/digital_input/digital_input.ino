#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 配置E0为输入模式，默认拉高电平
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE0, GpioExpansionBoard::kInputPullDown);
}

void loop() {
  Serial.print("digital value:");

  // 读取E0的数字值并打印
  Serial.println(gpio_expansion_board.GetGpioLevel(GpioExpansionBoard::kGpioPinE0));
  delay(100);
}
