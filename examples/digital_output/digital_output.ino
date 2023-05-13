#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 配置E0为输出模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE0, GpioExpansionBoard::kOutput);
}

void loop() {
  // 设置E0的输出高电平
  gpio_expansion_board.SetGpioLevel(GpioExpansionBoard::kGpioPinE0, 1);
  delay(100);

  // 设置E0的输出低电平
  gpio_expansion_board.SetGpioLevel(GpioExpansionBoard::kGpioPinE0, 0);
  delay(100);
}
