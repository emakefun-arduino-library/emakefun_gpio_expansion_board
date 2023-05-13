#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 配置扩展板pwm频率为50hz
  gpio_expansion_board.SetPwmFrequency(50);

  // 配置E1为pwm输出模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE1, GpioExpansionBoard::kPwm);
}

void loop() {
  // 设置E1的pwm输出占空比为30
  gpio_expansion_board.SetPwmDuty(GpioExpansionBoard::kGpioPinE1, 30);
  delay(1000);

  // 设置E1的pwm输出占空比为70
  gpio_expansion_board.SetPwmDuty(GpioExpansionBoard::kGpioPinE1, 70);
  delay(1000);
}