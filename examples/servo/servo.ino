#include <Arduino.h>

#include "gpio_expansion_board.h"

// 创建 GpioExpansionBoard 实例
GpioExpansionBoard gpio_expansion_board;

void setup() {
  // 初始化串口通信
  Serial.begin(115200);
  Serial.println("setup");

  // 使用舵机需要把gpio口设置为pwm模式，这里将E1口设置为pwm模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE1, GpioExpansionBoard::kPwm);

  // 使用舵机需要把gpio口设置为pwm模式，这里将E2口设置为pwm模式
  gpio_expansion_board.SetGpioMode(GpioExpansionBoard::kGpioPinE2, GpioExpansionBoard::kPwm);
}

// 注意，舵机控制只支持E1 ~ E2
void loop() {
  // 设置E1舵机转动到0度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE1, 0);
  delay(500);

  // 设置E2舵机转动到0度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE2, 0);
  delay(500);

  // 设置E1舵机转动到90度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE1, 90);
  delay(500);

  // 设置E2舵机转动到90度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE2, 90);
  delay(500);

  // 设置E1舵机转动到180度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE1, 180);
  delay(500);

  // 设置E2舵机转动到180度位置
  gpio_expansion_board.SetServoAngle(GpioExpansionBoard::kGpioPinE2, 180);
  delay(500);
}
