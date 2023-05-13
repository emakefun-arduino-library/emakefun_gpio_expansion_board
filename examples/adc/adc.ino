#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 配置E0为ADC模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE0, GpioExpansionBoard::kAdc);
}

void loop() {
  Serial.print("adc value:");
  // 读取E0的ADC值并打印
  Serial.println(gpio_expansion_board.GetGpioAdcValue(GpioExpansionBoard::kGpioPinE0));
  delay(100);
}
